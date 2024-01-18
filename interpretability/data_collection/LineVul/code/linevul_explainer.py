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

from __future__ import absolute_import, division, print_function
import argparse
import glob
import logging
import os
import pickle
import random
import re
import numpy as np
import torch
from torch.utils.data import DataLoader, Dataset, SequentialSampler, RandomSampler,TensorDataset
from torch.utils.data.distributed import DistributedSampler
from transformers import (WEIGHTS_NAME, AdamW, get_linear_schedule_with_warmup,
                          RobertaConfig, RobertaForSequenceClassification, RobertaTokenizer)
from tqdm import tqdm
import multiprocessing
import pandas as pd
# metrics
from sklearn.metrics import accuracy_score, recall_score, precision_score, f1_score
from sklearn.metrics import auc
# model reasoning

from tokenizers import Tokenizer

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

import torch
import torch.nn as nn
import transformers
from torch.nn import CrossEntropyLoss

import re
import sys

from absl import logging
from lit_nlp.api import model as lit_model
from lit_nlp.api import types as lit_types
from lit_nlp.lib import utils
import torch
import transformers

from transformers import RobertaForSequenceClassification

class RobertaClassificationHead(nn.Module):
    """Head for sentence-level classification tasks."""
    def __init__(self, config):
        super().__init__()
        self.dense = nn.Linear(config.hidden_size, config.hidden_size)
        self.dropout = nn.Dropout(config.hidden_dropout_prob)
        self.out_proj = nn.Linear(config.hidden_size, 2)

    def forward(self, features, **kwargs):
        x = features[:, 0, :]  # take <s> token (equiv. to [CLS])
        x = self.dropout(x)
        x = self.dense(x)
        x = torch.tanh(x)
        x = self.dropout(x)
        x = self.out_proj(x)
        return x
        
class Model(RobertaForSequenceClassification):   
    def __init__(self, encoder, config, tokenizer, args):
        super(Model, self).__init__(config=config)
        self.encoder = encoder
        self.tokenizer = tokenizer
        self.classifier = RobertaClassificationHead(config)
        self.args = args
    
        
    def forward(self, input_embed=None, attention_mask=None, labels=None, output_attentions=False, input_ids=None, output_hidden_states=False):
        
        output = transformers.modeling_outputs.SequenceClassifierOutput()
        
        if attention_mask == None:
            attention_mask = input_ids.ne(1)
        
        if output_attentions:
            if input_ids is not None:
                outputs = self.encoder.roberta(input_ids, attention_mask=attention_mask, output_attentions=output_attentions, output_hidden_states=output_hidden_states)
            else:
                outputs = self.encoder.roberta(inputs_embeds=input_embed, output_attentions=output_attentions, output_hidden_states=output_hidden_states)
            attentions = outputs.attentions
            last_hidden_state = outputs.last_hidden_state
            logits = self.classifier(last_hidden_state)
            prob = torch.softmax(logits, dim=-1)
            if labels is not None:
                loss_fct = CrossEntropyLoss()
                loss = loss_fct(logits, labels)
                output = transformers.modeling_outputs.SequenceClassifierOutput(loss=loss, logits=prob, attentions=attentions)
                if output_hidden_states:
                    output.hidden_states = outputs.hidden_states
                return output
            else:
                output = transformers.modeling_outputs.SequenceClassifierOutput(logits=prob, attentions=attentions)
                if output_hidden_states:
                    output.hidden_states = outputs.hidden_states
                return output
        else:
            if input_ids is not None:
                outputs = self.encoder.roberta(input_ids, attention_mask=attention_mask, output_attentions=output_attentions, output_hidden_states=output_hidden_states)[0]
            else:
                outputs = self.encoder.roberta(inputs_embeds=input_embed, output_attentions=output_attentions, output_hidden_states=output_hidden_states)[0]
            logits = self.classifier(outputs)
            prob = torch.softmax(logits, dim=-1)
            if labels is not None:
                loss_fct = CrossEntropyLoss()
                loss = loss_fct(logits, labels)
                output = transformers.modeling_outputs.SequenceClassifierOutput(loss=loss, logits=prob)
                if output_hidden_states:
                    output.hidden_states = outputs.hidden_states
                return output
            else:
                output = transformers.modeling_outputs.SequenceClassifierOutput(logits=prob)
                if output_hidden_states:
                    output.hidden_states = outputs.hidden_states
                return output


class InputFeatures(object):
    """A single training/test features for a example."""
    def __init__(self,
                 input_tokens,
                 input_ids,
                 label):
        self.input_tokens = input_tokens
        self.input_ids = input_ids
        self.label=label
        

class TextDataset(Dataset):
    def __init__(self, tokenizer, args, file_type="train"):
        self.tokenizer = tokenizer
        if file_type == "train":
            file_path = args.train_data_file
        elif file_type == "eval":
            file_path = args.eval_data_file
        elif file_type == "test":
            file_path = args.test_data_file
        self.args = args
        df = pd.read_csv(file_path)
        self.funcs = df["processed_func"].tolist()
        self.labels = df["target"].tolist()
        # for i in tqdm(range(len(funcs))):
        #     self.examples.append(convert_examples_to_features(funcs[i], labels[i], tokenizer, args))
        # if file_type == "train":
        #     for example in self.examples[:3]:
        #             logger.info("*** Example ***")
        #             logger.info("label: {}".format(example.label))
        #             logger.info("input_tokens: {}".format([x.replace('\u0120','_') for x in example.input_tokens]))
        #             logger.info("input_ids: {}".format(' '.join(map(str, example.input_ids))))

    def __len__(self):
        return len(self.funcs)

    def __getitem__(self, i):
        encoded_data = convert_examples_to_features(self.funcs[i], self.tokenizer, max_size=self.args.block_size)
        return encoded_data[0][0].clone().detach(), encoded_data[1][0].clone().detach(), torch.tensor(self.labels[i])



def convert_examples_to_features(code, tokenizer, max_size=400):
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

def set_seed(args):
    random.seed(args.seed)
    np.random.seed(args.seed)
    torch.manual_seed(args.seed)
    if args.n_gpu > 0:
        torch.cuda.manual_seed_all(args.seed)

class LineVulModelExplainer(lit_model.Model):

    LABELS = [0, 1]  # negative, positive
    compute_grads: bool = True  # if True, compute and return gradients.
    config_class, model_class, tokenizer_class = RobertaConfig, RobertaForSequenceClassification, RobertaTokenizer

    def __init__(self, args):
        self.args = args
        self.LABELS = [0, 1]
        self.compute_grads = True
        self.model_config = self.config_class.from_pretrained(args.model_name_or_path)
        self.model_config.num_labels = 1
        self.model_config.num_attention_heads = args.num_attention_heads
        self.tokenizer = self.tokenizer_class.from_pretrained(args.model_name_or_path)

        model = self.model_class.from_pretrained(args.model_name_or_path,
                                                from_tf=bool('.ckpt' in self.args.model_name_or_path),
                                                 config=self.model_config)
        self.model = Model(model, self.model_config,  self.tokenizer, self.args)
        self.output_dir= args.output_dir
    
    def load_model(self):
        checkpoint_prefix = 'checkpoint-best-f1/model.bin'
        output_dir = os.path.join(self.args.output_dir, '{}'.format(checkpoint_prefix))
        print("Starte loading")
        self.model.load_state_dict(torch.load(output_dir, map_location=self.args.device))
        self.model.to(self.args.device)
        print("Finished loading")
    

    def predict_minibatch(self, inputs):
        # Preprocess to ids and masks, and make the input batch.
        encoded_input = self.tokenizer.batch_encode_plus(
            [ex["sentence"] for ex in inputs],
            return_tensors="pt",
            add_special_tokens=True,
            max_length=self.args.block_size,
            padding="longest",
            truncation="longest_first"
        )


        # Check and send to cuda (GPU) if available
        if torch.cuda.is_available():
            self.model.cuda()
            for tensor in encoded_input:
                encoded_input[tensor] = encoded_input[tensor].cuda()

        # Run a forward pass.
        with torch.set_grad_enabled(self.compute_grads):
            out: transformers.modeling_outputs.SequenceClassifierOutput = self.model(**encoded_input, 
            output_attentions=True,
            output_hidden_states=True)

        # print("Output: ", out)
        # Post-process outputs.
        # print(out)
        # print(out.logits)
        # print(out.hidden_states)
        # print("What is out?")
        # print("helloooo")
        # return torch.tensor([[0.34, 0.56]])
        batched_outputs = {
            "probas": out.logits,
            "input_ids": encoded_input["input_ids"],
            "ntok": torch.sum(encoded_input["attention_mask"], dim=1),
            "cls_emb": out.hidden_states[-1][:, 0],  # last layer, first token
        }
      
        arg_max = torch.argmax(batched_outputs['probas'], dim=-1).numpy()
        # print(arg_max)
        #   print(out[0], batched_outputs['probas'])
        #   print(arg_max)
        labels = [ex.get('label', arg_max[i]) for (i, ex) in enumerate(inputs)]
        batched_outputs['label'] = torch.tensor(labels)
        #   print(labels)
        #   print(batched_outputs['label']==1, type(batched_outputs['label'].cpu().numpy()))
        # Add attention layers to batched_outputs
        assert len(out.attentions) == self.model.config.num_hidden_layers
        for i, layer_attention in enumerate(out.attentions):
            batched_outputs[f"layer_{i}/attention"] = layer_attention

        # Request gradients after the forward pass.
        # Note: hidden_states[0] includes position and segment encodings, as well as
        # subword embeddings.
        #   print(batched_outputs['probas'])
        if self.compute_grads:
            # <torch.float32>[batch_size, num_tokens, emb_dim]
            # scalar_pred_for_gradients = torch.max(
            #     out[0], dim=1, keepdim=False, out=None)[0]
            scalar_pred_for_gradients = torch.max(
                batched_outputs["probas"], dim=1, keepdim=False, out=None)[0]
            # print(scalar_pred_for_gradients)
            batched_outputs["input_emb_grad"] = torch.autograd.grad(
                scalar_pred_for_gradients,
                out.hidden_states[0],
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
        ret["input_emb_grad"] = lit_types.TokenEmbeddings(align="tokens", required=False)
        return ret

    def output_spec(self) -> lit_types.Spec:
        ret = {
            "tokens": lit_types.Tokens(),
            "probas": lit_types.MulticlassPreds(parent="label", vocab=self.LABELS, null_idx=0),
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


    def train(self):
        args = self.args
        train_dataset = TextDataset(self.tokenizer, args, file_type='train')
        eval_dataset = TextDataset(self.tokenizer, args, file_type='eval')
        pass

    def test(self):
        # build dataloader
        args = self.args
        test_dataset = TextDataset(self.tokenizer, args, file_type='test')
        test_sampler = SequentialSampler(test_dataset)
        test_dataloader = DataLoader(test_dataset, sampler=test_sampler, batch_size=args.eval_batch_size, num_workers=0)

        # multi-gpu evaluate
        if args.n_gpu > 1:
            model = torch.nn.DataParallel(model)

        # Eval!
        print("Start Runner? huh?")
        logger.info("***** Running Test *****")
        logger.info("  Num examples = %d", len(test_dataset))
        logger.info("  Batch size = %d", args.eval_batch_size)
        eval_loss = 0.0
        nb_eval_steps = 0
        model = self.model
        model.eval()
        logits=[]  
        y_trues=[]
        for batch in test_dataloader:
            input_ids = batch[0].to(args.device)
            attention_masks = batch[1].to(args.device)
            labels = batch[2].to(args.device)
            with torch.no_grad():
                output = model(input_ids=input_ids, labels=labels)
                eval_loss += output.loss.mean().item()
                logits.append(output.logits.cpu().numpy())
                y_trues.append(labels.cpu().numpy())
            nb_eval_steps += 1
        # calculate scores
        logits = np.concatenate(logits, 0)
        y_trues = np.concatenate(y_trues, 0)
        y_preds = logits[:, 1] > 0.5
        acc = accuracy_score(y_trues, y_preds)
        recall = recall_score(y_trues, y_preds)
        precision = precision_score(y_trues, y_preds)   
        f1 = f1_score(y_trues, y_preds)             
        result = {
            "test_accuracy": float(acc),
            "test_recall": float(recall),
            "test_precision": float(precision),
            "test_f1": float(f1),
            "test_threshold": 0.5,
        }
        return result

class Args:
    def __init__(self):
        self.output_dir ='<ANONYMOUS>/<ANONYMOUS>/saved_models/linevul/devign/'
        self.num_attention_heads = 12
        self.device = torch.device('cpu')
        self.model_name_or_path = 'microsoft/codebert-base'
        self.epoch = 5
        self.train_batch_size = 16
        self.adam_epsilon = 1e-8
        self.learning_rate = 2e-5
        self.max_grad_norm=1.0
        self.weight_decay = 0.0
        self.gradient_accumulation_steps = 1
        self.local_rank = -1
        self.block_size = 512
        self.eval_batch_size = 16
        self.n_gpu = 1
        self.evaluate_during_training = True
        self.output_dir = './saved_models'
        self.train_data_file = '../data/big-vul_dataset/train.csv'
        self.eval_data_file = '../data/big-vul_dataset/valid.csv'
        self.test_data_file = '../data/big-vul_dataset/test.csv'

# arg = Args()
# model = LineVulModelExplainer(args=arg)
# model.load_model()
# model.test()
# print("success")
