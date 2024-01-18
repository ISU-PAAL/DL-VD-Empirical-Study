import pandas as pd
import numpy as np
import csv
import pickle
import re
import torch
import sklearn
import os
import random
import custom
import models
import clang
from clang import *
from clang import cindex
from pathlib import Path
from tokenizers import ByteLevelBPETokenizer
from tokenizers.implementations import ByteLevelBPETokenizer
from tokenizers.processors import BertProcessing
from torch.utils.data import Dataset, DataLoader, IterableDataset
from transformers import RobertaConfig
from transformers import RobertaForMaskedLM, RobertaForSequenceClassification
from transformers import RobertaTokenizerFast
from transformers import DataCollatorForLanguageModeling
from transformers import Trainer, TrainingArguments
from transformers import LineByLineTextDataset
from transformers.modeling_outputs import SequenceClassifierOutput
from custom import CustomDataCollatorForLanguageModeling


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

## Tokenizer
from tokenizers import Tokenizer
from tokenizers import normalizers,decoders
from tokenizers.normalizers import StripAccents, unicode_normalizer_from_str, Replace
from tokenizers.processors import TemplateProcessing
from tokenizers import processors,pre_tokenizers
from tokenizers.models import BPE

from tokenizers.pre_tokenizers import PreTokenizer
from tokenizers.pre_tokenizers import Whitespace
from tokenizers import NormalizedString,PreTokenizedString
from typing import List 

class MyTokenizer:
    
    cidx = cindex.Index.create()
        

    def clang_split(self, i: int, normalized_string: NormalizedString) -> List[NormalizedString]:
        ## Tokkenize using clang
        tok = []
        tu = self.cidx.parse('tmp.c',
                       args=[''],  
                       unsaved_files=[('tmp.c', str(normalized_string.original))],  
                       options=0)
        for t in tu.get_tokens(extent=tu.cursor.extent):
            spelling = t.spelling.strip()
            
            if spelling == '':
                continue

            tok.append(NormalizedString(spelling))

        return(tok)
    
    def pre_tokenize(self, pretok: PreTokenizedString):
        pretok.split(self.clang_split)



class VulbertaModel(lit_model.Model):
    """Simple sentiment analysis model."""

    LABELS = [0, 1]  # negative, positive
    compute_grads: bool = True  # if True, compute and return gradients.

    def __init__(self, arg):
        self.arg = arg
        self.model = RobertaForSequenceClassification.from_pretrained(
          '<ANONYMOUS>/<ANONYMOUS>/saved_models/vulberta/mlp/VB-MLP_devign/',
          output_hidden_states=True,
          output_attentions=True
        )
        self.model.to(arg.device)
        self.tokenizer = self.get_tokenizer()

    def get_tokenizer(self):
        ## Load pre-trained tokenizers
        vocab, merges = BPE.read_file(vocab="./tokenizer/drapgh-vocab.json", merges="./tokenizer/drapgh-merges.txt")
        my_tokenizer = Tokenizer(BPE(vocab, merges, unk_token="<unk>"))

        my_tokenizer.normalizer = normalizers.Sequence([StripAccents(), Replace(" ", "Ä")])
        my_tokenizer.pre_tokenizer = PreTokenizer.custom(MyTokenizer())
        my_tokenizer.post_processor = processors.ByteLevel(trim_offsets=False)
        my_tokenizer.post_processor = TemplateProcessing(
            single="<s> $A </s>",
            special_tokens=[
            ("<s>",0),
            ("<pad>",1),
            ("</s>",2),
            ("<unk>",3),
            ("<mask>",4)
            ]
        )
        my_tokenizer.enable_truncation(max_length=1024) 
        my_tokenizer.enable_padding(direction='right', pad_id=1, pad_type_id=0, pad_token='<pad>', length=None, pad_to_multiple_of=None)
        return my_tokenizer

    def activate_evaluation(self):
        self.model.eval()

    def process_encodings(self, encodings):
        input_ids=[]
        attention_mask=[]
        tokens = []
        for enc in encodings:
            input_ids.append(enc.ids)
            attention_mask.append(enc.attention_mask)
            tokens.append(enc.tokens)
        return {'input_ids': torch.tensor(input_ids), 'attention_mask': torch.tensor(attention_mask), 'tokens': np.array(tokens)}

    def predict_minibatch(self, inputs):

      # Preprocess to ids and masks, and make the input batch.
      encoded_input_ = self.tokenizer.encode_batch([ex["sentence"] for ex in inputs])
      
      encoded_input = self.process_encodings(encoded_input_)
      # Check and send to cuda (GPU) if available
      if torch.cuda.is_available():
        self.model.cuda()
        for tensor in encoded_input:
          if tensor != 'tokens':
            encoded_input[tensor] = torch.tensor(encoded_input[tensor]).to(self.arg.device)

      # Run a forward pass.
      with torch.set_grad_enabled(self.compute_grads):
        out: transformers.modeling_outputs.SequenceClassifierOutput = \
            self.model(input_ids=encoded_input['input_ids'], attention_mask=encoded_input['attention_mask'])

      # print("Output: ", out)
      # Post-process outputs.


      batched_outputs = {
          "probas": torch.nn.functional.softmax(out.logits,dim=-1),
        #   "probas": out[0],
          "input_ids": encoded_input["input_ids"],
          "tokens": encoded_input["tokens"],
          "ntok": torch.sum(encoded_input["attention_mask"], dim=1),
          "cls_emb": out.hidden_states[-1][:, 0],  # last layer, first token
      }
      
      arg_max = torch.argmax(batched_outputs['probas'], dim=-1).cpu().numpy()
    #   print(out[0], batched_outputs['probas'])
    #   print(arg_max)
      labels = [ex.get('label', arg_max[i]) for (i, ex) in enumerate(inputs)]
      batched_outputs['label'] = torch.tensor(labels)
    #   print(labels)
    #   print(batched_outputs['label']==1, type(batched_outputs['label'].cpu().numpy()))
      # Add attention layers to batched_outputs
      # assert len(out[2]) == self.model.config.num_hidden_layers
      for i, layer_attention in enumerate(out.attentions):
        batched_outputs[f"layer_{i}/attention"] = layer_attention

      # Request gradients after the forward pass.
      # Note: hidden_states[0] includes position and segment encodings, as well as
      # subword embeddings.
    #   print(batched_outputs['probas'])
      if self.compute_grads:
        # <torch.float32>[batch_size, num_tokens, emb_dim]
        scalar_pred_for_gradients = torch.max(
            batched_outputs["probas"], dim=1, keepdim=False, out=None)[0]
        # scalar_pred_for_gradients = torch.max(
        #     batched_outputs["probas"], dim=1, keepdim=False, out=None)[0]
        # print(scalar_pred_for_gradients)
        batched_outputs["input_emb_grad"] = torch.autograd.grad(
            scalar_pred_for_gradients,
            out.hidden_states[0],
            grad_outputs=torch.ones_like(scalar_pred_for_gradients),
        )[0]

      # Post-process outputs.
      # Return as NumPy for further processing.
      detached_outputs = {}
      for k, v in batched_outputs.items():
        if k == 'tokens':
          detached_outputs['tokens'] = v
        else:
          detached_outputs[k] = v.cpu().detach().numpy()
      # detached_outputs = {k: v if k == 'tokens' else k: v.cpu().detach().numpy()  for k, v in batched_outputs.items()}

      # Unbatch outputs so we get one record per input example.
      for output in utils.unbatch_preds(detached_outputs):
        ntok = output.pop("ntok")
        output["tokens"] = output['tokens'][:ntok]

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



class Arg:
  def __init__(self):
    self.device=torch.device('cpu')
    self.output_dir='<ANONYMOUS>/<ANONYMOUS>/saved_models/vulberta/mlp/'
    self.mymodel = 'mlp'
    self.dataset = 'devign'
    if torch.cuda.is_available():
        self.device = torch.device('cuda')
