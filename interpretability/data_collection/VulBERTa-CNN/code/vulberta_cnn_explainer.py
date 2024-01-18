#!/usr/bin/env python
# coding: utf-8

#--seed_input=42
#--train_test=test
#--epochs=20
#--batch=4




import argparse
import numpy as np
import copy
import pandas as pd
import random
import re
import os
import time
import torch
import torch.nn as nn
import torch.nn.functional as F
import torchtext.vocab as vocab
import sklearn.metrics
from transformers import RobertaModel
from torch import nn
from torch.optim import Adam
from clang import *
import tqdm

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



import warnings
warnings.filterwarnings("ignore")


## Tokenizer

from tokenizers.pre_tokenizers import PreTokenizer
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
                
            ## Keyword no need

            ## Punctuations no need

            ## Literal all to BPE
            
            #spelling = spelling.replace(' ', '')
            tok.append(NormalizedString(spelling))

        return(tok)
    
    def pre_tokenize(self, pretok: PreTokenizedString):
        pretok.split(self.clang_split)
        
## Custom tokenizer

from tokenizers import Tokenizer
from tokenizers import normalizers
from tokenizers.normalizers import StripAccents, Replace
from tokenizers.processors import TemplateProcessing
from tokenizers import processors
from tokenizers.models import BPE

## Init new tokenizers
#my_tokenizer = Tokenizer(BPE(unk_token="<unk>"))
#my_tokenizer = Tokenizer(BPE())


class myCNN(nn.Module):
    def __init__(self, EMBED_SIZE, EMBED_DIM):
        super(myCNN,self).__init__()
        
        pretrained_weights = RobertaModel.from_pretrained('models/VulBERTa/').embeddings.word_embeddings.weight

        self.embed = nn.Embedding.from_pretrained(pretrained_weights,
                                                  freeze=True,
                                                  padding_idx=1)

        self.conv1 = nn.Conv1d(in_channels=EMBED_DIM, out_channels=200, kernel_size=3)
        self.conv2 = nn.Conv1d(in_channels=EMBED_DIM, out_channels=200, kernel_size=4)
        self.conv3 = nn.Conv1d(in_channels=EMBED_DIM, out_channels=200, kernel_size=5)

        self.dropout = nn.Dropout(0.5)

        self.fc1 = nn.Linear(200*3,256) #500
        self.fc2 = nn.Linear(256,128)
        self.fc3 = nn.Linear(128,2)
    
    def forward(self, x):
        x = self.embed(x)
        x = x.permute(0,2,1)

        x1 = F.relu(self.conv1(x))
        x2 = F.relu(self.conv2(x))
        x3 = F.relu(self.conv3(x))
        
        x1 = F.max_pool1d(x1, x1.shape[2])
        x2 = F.max_pool1d(x2, x2.shape[2])
        x3 = F.max_pool1d(x3, x3.shape[2])
        
        x = torch.cat([x1,x2,x3],dim=1)
        
        # flatten the tensor
        x = x.flatten(1)
        
        # apply mean over the last dimension
        #x = torch.mean(x, -1)

        x = self.dropout(x)

        x = F.relu(self.fc1(x))
        x = F.relu(self.fc2(x))
        x = self.fc3(x)
        return(x)


## Load pre-trained tokenizers
class VulbertaCNNModel(lit_model.Model):
    def __init__(self, args):
        self.model = myCNN(args.EMBED_SIZE, args.EMBED_DIM)
        self.tokenizer = self.get_tokenizer()
        self.args=args
        self.LABELS=[0, 1]

    def get_tokenizer(self):
        vocab, merges = BPE.read_file("./tokenizer/drapgh-vocab.json", "./tokenizer/drapgh-merges.txt")
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
        my_tokenizer.enable_padding(direction='right', pad_id=1, pad_type_id=0, pad_token='<pad>', length=1024, pad_to_multiple_of=None)
        return my_tokenizer
    
    def load_model(self):
        checkpoint = torch.load(os.path.join(self.args.output_dir,  'model_ep_10.tar'), map_location=self.args.device)
        print("loading checkpoint from {}".format(os.path.join(self.args.output_dir,  'model_ep_17.tar')))
        self.model.load_state_dict(checkpoint['model_state_dict'])

    def cleaner(self, code):
        ## Remove code comments
        pat = re.compile(r'(/\*([^*]|(\*+[^*/]))*\*+/)|(//.*)')
        code = re.sub(pat,'',code)
        code = re.sub('\n','',code)
        code = re.sub('\t','',code)
        return(code)
    
    def predict_minibatch(self, inputs):
        self.model.eval()
        batch_input = []
        for input in  inputs:
            ids = self.tokenizer.encode(input['sentence']).ids
            # print(self.tokenizer.decode(ids))
            batch_input.append(ids)
        batch_input = torch.tensor(batch_input)
        with torch.no_grad():
            prediction = self.model(batch_input)
        batched_outputs =  {
            'probas': prediction
        }
        detached_outputs = {
          k: v.cpu().detach().numpy() for k, v in batched_outputs.items()
        }

        for output in utils.unbatch_preds(detached_outputs):
            yield output
        
    def input_spec(self) -> lit_types.Spec:
        ret = {
            "sentence": lit_types.TextSegment()
        }
        return ret
    
    def output_spec(self) -> lit_types.Spec:
        ret = {
            "probas": lit_types.MulticlassPreds(parent="label", vocab=self.LABELS,
                                                null_idx=0)
        }
        return ret
    
    def enable_gpu(self):
        seed = self.args.seed
        os.environ['PYTHONHASHSEED'] = str(seed)
        torch.manual_seed(seed)
        torch.cuda.manual_seed(seed)
        torch.cuda.manual_seed_all(seed)
        np.random.seed(seed)
        random.seed(seed)
        torch.backends.cudnn.enabled = True
        torch.backends.cudnn.deterministic = True
        torch.backends.cudnn.benchmark = False



class Arg:
    def __init__(self):
        self.seed = 42
        self.VOCAB_SIZE = 50000
        self.BATCH_SIZE = 512
        self.EMBED_SIZE = self.VOCAB_SIZE + 2
        self.EMBED_DIM = 768 #768
        self.output_dir = '../saved_models/vulberta/devign/'
        self.device=torch.device("cuda")