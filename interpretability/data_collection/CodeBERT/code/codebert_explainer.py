# coding=utf-8
# Copyright 2018 The Google AI Language Team Authors and The HuggingFace Inc. team.
# Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
"""
Fine-tuning the library models for language modeling on a text file (GPT, GPT-2, BERT, RoBERTa).
GPT and GPT-2 are fine-tuned using a causal language modeling (CLM) loss while BERT and RoBERTa are fine-tuned
using a masked language modeling (MLM) loss.
"""

from __future__ import absolute_import, division, print_function

import argparse
import glob
import logging
import os
import pickle
import random
import re
import shutil

import numpy as np
import torch
from torch.utils.data import DataLoader, Dataset, SequentialSampler, RandomSampler,TensorDataset
from torch.utils.data.distributed import DistributedSampler
import json
try:
    from torch.utils.tensorboard import SummaryWriter
except:
    from tensorboardX import SummaryWriter

from tqdm import tqdm, trange
import multiprocessing
from model import Model
cpu_cont = multiprocessing.cpu_count()
from transformers import (WEIGHTS_NAME, AdamW, get_linear_schedule_with_warmup,
                          BertConfig, BertForMaskedLM, BertTokenizer,
                          GPT2Config, GPT2LMHeadModel, GPT2Tokenizer,
                          OpenAIGPTConfig, OpenAIGPTLMHeadModel, OpenAIGPTTokenizer,
                          RobertaConfig, RobertaForSequenceClassification, RobertaTokenizer,
                          DistilBertConfig, DistilBertForMaskedLM, DistilBertTokenizer)

logger = logging.getLogger(__name__)


import torch
import torch.nn as nn
import torch
from torch.autograd import Variable
import copy
from torch.nn import CrossEntropyLoss, MSELoss


import re
import sys

from absl import app
from absl import flags
from absl import logging
from lit_nlp import dev_server
from lit_nlp import server_flags
from lit_nlp.api import model as lit_model
from lit_nlp.api import types as lit_types
from lit_nlp.lib import utils
import torch
import transformers
    
    
class Model(nn.Module):   
    def __init__(self, encoder, config, tokenizer):
        super(Model, self).__init__()
        self.encoder = encoder
        self.tokenizer = tokenizer
        self.config = config
    
    def forward(self, input_ids=None,attention_mask=None, labels=None): 
        outputs=self.encoder(input_ids,attention_mask=attention_mask)
        logits=outputs[0]
        prob=torch.sigmoid(logits)
        if labels is not None:
            labels=labels.float()
            loss=torch.log(prob[:,0]+1e-10)*labels+torch.log((1-prob)[:,0]+1e-10)*(1-labels)
            loss=-loss.mean()
            return loss, prob, outputs[1], outputs[2]
        else:
            return prob, outputs[1], outputs[2]

def convert_examples_to_features(code, tokenizer,max_size=400):
    #source
    encoded_dict = tokenizer.encode_plus(
        code,
        add_special_tokens=True,
        max_length=max_size,       # Pad & truncate all sentences.
        pad_to_max_length = True,
        return_attention_mask = True,   # Construct attn. masks.
        return_tensors = 'pt',
    )
    return encoded_dict['input_ids'], encoded_dict['attention_mask']

class TextDataset(Dataset):
    def __init__(self, tokenizer, file_path=None):
        self.tokenizer = tokenizer
        # self.input_ids = []
        # self.attention_masks = []
        # self.labels = []
        self.examples = []
        with open(file_path) as f:
            for line in f:
                js=json.loads(line.strip())
                self.examples.append((' '.join(js['func'].split()), js['target']))
        #         encoded_data = convert_examples_to_features(js, self.tokenizer)
        #         self.input_ids.append(encoded_data[0])
        #         self.attention_masks.append(encoded_data[1])
        #         self.labels.append(encoded_data[2])
        # self.input_ids = torch.cat(self.input_ids, dim=0)
        # self.attention_masks = torch.cat(self.attention_masks, dim=0)

    def __len__(self):
        return len(self.examples)

    def __getitem__(self, i):
        encoded_data = convert_examples_to_features(self.examples[i][0], self.tokenizer)
        return encoded_data[0][0].clone().detach(), encoded_data[1][0].clone().detach(), torch.tensor(self.examples[i][1])


class CodebertModel(lit_model.Model):
    """Simple sentiment analysis model."""

    LABELS = [0, 1]  # negative, positive
    compute_grads: bool = True  # if True, compute and return gradients.
    config_class, model_class, tokenizer_class = RobertaConfig, RobertaForSequenceClassification, RobertaTokenizer

    def __init__(self):
        self.model_name_or_path = 'microsoft/codebert-base'
        self.model_config = self.config_class.from_pretrained(self.model_name_or_path,
                num_labels=1,
                output_hidden_states=True,
                output_attentions=True)
        self.tokenizer = self.tokenizer_class.from_pretrained('microsoft/codebert-base')

        model = self.model_class.from_pretrained(self.model_name_or_path,
                                                from_tf=bool('.ckpt' in self.model_name_or_path),
                                                 config=self.model_config)
        self.model = Model(model, self.model_config,  self.tokenizer)
        self.output_dir="./saved_models"

    def activate_evaluation(self):
        self.model.eval()

    def load_model(self, args):
        checkpoint_prefix = 'checkpoint-best-acc/model.bin'
        output_dir = os.path.join(args.output_dir, '{}'.format(checkpoint_prefix))
        self.model.load_state_dict(torch.load(output_dir, map_location=args.device))
        self.model.to(args.device)

    def predict_minibatch(self, inputs):

      # Preprocess to ids and masks, and make the input batch.
      encoded_input = self.tokenizer.batch_encode_plus(
          [ex["sentence"] for ex in inputs],
          return_tensors="pt",
          add_special_tokens=True,
          max_length=400,
          padding="longest",
          truncation="longest_first")

      # Check and send to cuda (GPU) if available
      if torch.cuda.is_available():
        self.model.cuda()
        for tensor in encoded_input:
          encoded_input[tensor] = encoded_input[tensor].cuda()

      # Run a forward pass.
      with torch.set_grad_enabled(self.compute_grads):
        out: transformers.modeling_outputs.SequenceClassifierOutput = \
            self.model(**encoded_input)

      # print("Output: ", out)
      # Post-process outputs.


      batched_outputs = {
          "probas": torch.tensor([[torch.tensor(1.0)  -  x[0], x[0]] for x in out[0]], requires_grad=True),
        #   "probas": out[0],
          "input_ids": encoded_input["input_ids"],
          "ntok": torch.sum(encoded_input["attention_mask"], dim=1),
          "cls_emb": out[1][-1][:, 0],  # last layer, first token
      }
      
      arg_max = torch.argmax(batched_outputs['probas'], dim=-1).numpy()
    #   print(out[0], batched_outputs['probas'])
    #   print(arg_max)
      labels = [ex.get('label', arg_max[i]) for (i, ex) in enumerate(inputs)]
      batched_outputs['label'] = torch.tensor(labels)
    #   print(labels)
    #   print(batched_outputs['label']==1, type(batched_outputs['label'].cpu().numpy()))
      # Add attention layers to batched_outputs
      assert len(out[2]) == self.model.config.num_hidden_layers
      for i, layer_attention in enumerate(out[2]):
        batched_outputs[f"layer_{i}/attention"] = layer_attention

      # Request gradients after the forward pass.
      # Note: hidden_states[0] includes position and segment encodings, as well as
      # subword embeddings.
    #   print(batched_outputs['probas'])
      if self.compute_grads:
        # <torch.float32>[batch_size, num_tokens, emb_dim]
        scalar_pred_for_gradients = torch.max(
            out[0], dim=1, keepdim=False, out=None)[0]
        # scalar_pred_for_gradients = torch.max(
        #     batched_outputs["probas"], dim=1, keepdim=False, out=None)[0]
        # print(scalar_pred_for_gradients)
        batched_outputs["input_emb_grad"] = torch.autograd.grad(
            scalar_pred_for_gradients,
            out[1][0],
            grad_outputs=torch.ones_like(scalar_pred_for_gradients),
        )[0]

      # Post-process outputs.
      # Return as NumPy for further processing.
      detached_outputs = {
          k: v.cpu().detach().numpy() for k, v in batched_outputs.items()}

      # Unbatch outputs so we get one record per input example.
      for output in utils.unbatch_preds(detached_outputs):
        ntok = output.pop("ntok")
        output["tokens"] = self.tokenizer.convert_ids_to_tokens(
            output.pop("input_ids")[:ntok])

        # set token gradients
        if self.compute_grads:
          output["token_grad_sentence"] = output["input_emb_grad"][:ntok]

        # Process attention.
        for key in output:
          if not re.match(r"layer_(\d+)/attention", key):
            continue
          # Select only real tokens, since most of this matrix is padding.
          # <float32>[num_heads, max_seq_length, max_seq_length]
          # -> <float32>[num_heads, num_tokens, num_tokens]
          output[key] = output[key][:, :ntok, :ntok].transpose((0, 2, 1))
          # Make a copy of this array to avoid memory leaks, since NumPy otherwise
          # keeps a pointer around that prevents the source array from being GCed.
          output[key] = output[key].copy()
        yield output

    def input_spec(self) -> lit_types.Spec:
      ret ={
          "sentence": lit_types.TextSegment(),
          "label": lit_types.CategoryLabel(vocab=self.LABELS, required=False)}
      ret["tokens"] = lit_types.Tokens(
        parent='sentence', required=False,
      )
      ret["input_emb_grad"] = lit_types.TokenEmbeddings(
        align="tokens", required=False)
      return ret

    def output_spec(self) -> lit_types.Spec:
      ret = {
          "tokens": lit_types.Tokens(),
          "probas": lit_types.MulticlassPreds(parent="label", vocab=self.LABELS,
                                              null_idx=0),
          "cls_emb": lit_types.Embeddings()
      }
      # Gradients, if requested.
      ret['input_emb_grad'] = lit_types.TokenEmbeddings(
        align="tokens" )
      if self.compute_grads:
        ret['label'] = lit_types.CategoryLabel(vocab=self.LABELS, required=False)
        ret["token_grad_sentence"] = lit_types.TokenGradients(
            align="tokens",
            grad_for="input_emb_grad",
            grad_target_field_key="label",
        )

      # Attention heads, one field for each layer.
      for i in range(self.model.config.num_hidden_layers):
        ret[f"layer_{i}/attention"] = lit_types.AttentionHeads(
            align_in="tokens", align_out="tokens")
      return ret

    
    # Training the model
    def train(self, args):

        train_dataset = TextDataset(self.tokenizer, args.train_data_file)
        train_sampler = RandomSampler(train_dataset)
        train_dataloader = DataLoader(train_dataset, sampler=train_sampler,
                                batch_size=args.train_batch_size,num_workers=4,pin_memory=True)
        
        args.max_steps=args.epoch*len( train_dataloader)
        args.save_steps=len(train_dataloader)
        args.warmup_steps=len(train_dataloader)
        args.logging_steps=len(train_dataloader)
        args.num_train_epochs=args.epoch
        
        args.start_epoch = 0
        args.start_step = 0

        model = self.model
        model.to(args.device)
        

        no_decay = ['bias', 'LayerNorm.weight']
        optimizer_grouped_parameters = [
            {'params': [p for n, p in self.model.named_parameters() if not any(nd in n for nd in no_decay)],
            'weight_decay': args.weight_decay},
            {'params': [p for n, p in self.model.named_parameters() if any(nd in n for nd in no_decay)], 'weight_decay': 0.0}
        ]

        optimizer = AdamW(optimizer_grouped_parameters, lr=args.learning_rate, eps=args.adam_epsilon)
        scheduler = get_linear_schedule_with_warmup(optimizer, num_warmup_steps=args.max_steps*0.1,
                                            num_training_steps=args.max_steps)


        global_step = args.start_step
        tr_loss, logging_loss,avg_loss,tr_nb,tr_num,train_loss = 0.0, 0.0,0.0,0,0,0
        best_mrr=0.0
        best_acc=0.0
        # model.resize_token_embeddings(len(tokenizer))

        model.zero_grad()
        for idx in range(args.start_epoch, int(args.num_train_epochs)):
            bar = tqdm(train_dataloader,total=len(train_dataloader))
            tr_num=0
            train_loss=0
            for step, batch in enumerate(bar):
                #print(batch)
                input_ids = batch[0].to(args.device)
                attention_masks = batch[1].to(args.device)
                labels = batch[2].to(args.device)
                #print(inputs)
                #print(labels)
                model.train()
                result = model(input_ids, attention_mask=attention_masks, labels=labels)
                loss = result[0]
                logits = result[1]
                print(logits.shape)

                # if args.n_gpu > 1:
                #     loss = loss.mean()  # mean() to average on multi-gpu parallel training
                loss.backward()
                torch.nn.utils.clip_grad_norm_(model.parameters(), args.max_grad_norm)

                tr_loss += loss.item()
                tr_num+=1
                train_loss+=loss.item()
                if avg_loss==0:
                    avg_loss=tr_loss
                avg_loss=round(train_loss/tr_num,5)
                bar.set_description("epoch {} loss {}".format(idx,avg_loss))

                if (step + 1) % args.gradient_accumulation_steps == 0:
                    optimizer.step()
                    optimizer.zero_grad()
                    scheduler.step()
                    global_step += 1
                    output_flag=True
                    avg_loss=round(np.exp((tr_loss - logging_loss) /(global_step- tr_nb)),4)
                    if args.local_rank in [-1, 0] and args.logging_steps > 0 and global_step % args.logging_steps == 0:
                        logging_loss = tr_loss
                        tr_nb=global_step

                    if args.local_rank in [-1, 0] and args.save_steps > 0 and global_step % args.save_steps == 0:

                        if args.local_rank == -1 and args.evaluate_during_training:  # Only evaluate when single GPU otherwise metrics may not average well
                            results = self.evaluate(args, model, self.tokenizer, eval_when_training=True)
                            for key, value in results.items():
                                print("  %s = %s", key, round(value,4))
                            # Save model checkpoint

                        if results['eval_acc'] > best_acc:
                            best_acc=results['eval_acc']
                            print("  "+"*"*20)
                            print("  Best acc:%s",round(best_acc,4))
                            print("  "+"*"*20)
                            print(results)

                            checkpoint_prefix = 'checkpoint-best-acc'
                            output_dir = os.path.join(args.output_dir, '{}'.format(checkpoint_prefix))
                            if not os.path.exists(output_dir):
                                os.makedirs(output_dir)
                            model_to_save = model.module if hasattr(model,'module') else model
                            output_dir = os.path.join(output_dir, '{}'.format('model.bin'))
                            torch.save(model_to_save.state_dict(), output_dir)
                            print("Saving model checkpoint to %s", output_dir)


    def evaluate(self, args, model, tokenizer, eval_when_training=False):
        # Loop to handle MNLI double evaluation (matched, mis-matched)
        eval_output_dir = args.output_dir

        eval_dataset = TextDataset(tokenizer, args.eval_data_file)

        if not os.path.exists(eval_output_dir) and args.local_rank in [-1, 0]:
            os.makedirs(eval_output_dir)

        # Note that DistributedSampler samples randomly
        eval_sampler = SequentialSampler(eval_dataset)
        eval_dataloader = DataLoader(eval_dataset, sampler=eval_sampler, batch_size=args.eval_batch_size,num_workers=4,pin_memory=True)

        # Eval!
        logger.info("***** Running evaluation *****")
        logger.info("  Num examples = %d", len(eval_dataset))
        logger.info("  Batch size = %d", args.eval_batch_size)
        eval_loss = 0.0
        nb_eval_steps = 0
        model.eval()
        logits=[]
        labels=[]
        for batch in eval_dataloader:
            input_ids = batch[0].to(args.device)
            attention_masks = batch[1].to(args.device)
            label = batch[2].to(args.device)
            with torch.no_grad():
                result = model(input_ids, attention_mask=attention_masks, labels=label)
                lm_loss = result[0]
                logit = result[1]
                # logit=torch.nn.functional.softmax(torch.tensor(logit), dim=-1)
                eval_loss += lm_loss.mean().item()
                logits.append(logit.cpu().numpy())
                labels.append(label.cpu().numpy())
            nb_eval_steps += 1
        logits=np.concatenate(logits,0)
        labels=np.concatenate(labels,0)
        preds=logits[:,0]>0.5
        eval_acc=np.mean(labels==preds)
        eval_loss = eval_loss / nb_eval_steps
        perplexity = torch.tensor(eval_loss)

        result = {
            "eval_loss": float(perplexity),
            "eval_acc":round(eval_acc,4),
        }
        return result

    def test(self, args):
      # Loop to handle MNLI double evaluation (matched, mis-matched)
      eval_dataset = TextDataset(self.tokenizer, args.test_data_file)

      # Note that DistributedSampler samples randomly
      eval_sampler = SequentialSampler(eval_dataset)
      eval_dataloader = DataLoader(eval_dataset, sampler=eval_sampler, batch_size=args.eval_batch_size)

      # Eval!
      print("***** Running Test *****")
      print("  Num examples = %d", len(eval_dataset))
      print("  Batch size = %d", args.eval_batch_size)
      eval_loss = 0.0
      nb_eval_steps = 0
      model = self.model
      model.eval()
      logits=[]
      labels=[]
      for batch in tqdm(eval_dataloader,total=len(eval_dataloader)):
        input_ids = batch[0].to(args.device)
        attention_masks = batch[1].to(args.device)
        label = batch[2].to(args.device)
        with torch.no_grad():
          logit = model(input_ids, attention_mask=attention_masks)[0]
          # logit=torch.nn.functional.softmax(torch.tensor(logit), dim=-1)
          logits.append(logit.cpu().numpy())
          labels.append(label.cpu().numpy())
  
      logits=np.concatenate(logits,0)
      labels=np.concatenate(labels,0)
      print(logits)
      preds=logits[:,0]>0.5
      print(preds)

      eval_acc=np.mean(labels==preds)

      print(eval_acc)

      # import re

      # with open(os.path.join(args.output_dir,"predictions" + ".txt"),'w') as f:
      #     for example,pred,percent, label in zip(eval_dataset.examples,preds,logits[:,0],labels):
      #         if pred:
      #             f.write(example.idx+'\x1f1\x1f' + str(percent) + '\x1f' + str(label) + '\n')

      #         else:
      #             f.write(example.idx+'\x1f0\x1f' + str(percent) + '\x1f' + str(label) + '\n')


class Arg:
    def __init__(self):
        self.train_data_file = '../dataset/train.jsonl'
        self.device = torch.device('cpu')
        self.epoch = 5
        self.train_batch_size = 16
        self.adam_epsilon = 1e-8
        self.learning_rate = 2e-5
        self.max_grad_norm=1.0
        self.weight_decay = 0.0
        self.gradient_accumulation_steps = 1
        self.local_rank = -1
        self.output_dir = '<ANONYMOUS>/<ANONYMOUS>/saved_models/codebert/devign/'
        self.eval_data_file = '../dataset/valid.jsonl'
        self.eval_batch_size = 16
        self.evaluate_during_training = True
        self.test_data_file = '../dataset/test.jsonl'


def main():
    args = Arg()

    model = CodebertModel()
    # model.train(args)
    model.load_model(args)
    model.test(args)
    print("Sucess")



if __name__ == "__main__":
    main()
