#!/usr/bin/env python
# coding: utf-8

# In[1]:

import argparse
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
import regex
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


# ## Pre-requisites stuff

# In[2]:


## Set default device (GPU or CPU)


parser = argparse.ArgumentParser()

## Required parameters
parser.add_argument("--train_test", default=None, type=str, required=True,
                    help="The input training data file (a text file).")
parser.add_argument("--data_folder", default=None, type=str, required=True,
                    help="The input training data file (a text file).")
parser.add_argument("--save_folder", default=None, type=str, required=True,
                    help="The input training data file (a text file).")
parser.add_argument("--seed_input", default=None, type=int, required=True,
                    help="The input training data file (a text file).")
parser.add_argument("--batch", default=4, type=int, required=False,
                    help="The input training data file (a text file).")
parser.add_argument("--epochs", default=10, type=int, required=False,
                    help="The input training data file (a text file).")
parser.add_argument("--dataset", default=None, type=str, required=True,
                    help="dataset")


args = parser.parse_args()



device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(device)


# In[3]:


## Deterministic/reproducible flags

seed = args.seed_input
os.environ['PYTHONHASHSEED'] = str(seed)
torch.manual_seed(seed)
torch.cuda.manual_seed(seed)
torch.cuda.manual_seed_all(seed)
np.random.seed(seed)
random.seed(seed)
torch.backends.cudnn.enabled = True
torch.backends.cudnn.deterministic = True
torch.backends.cudnn.benchmark = False


# In[4]:


## Weights and Biases flags

os.environ['WANDB_DISABLED'] = 'true'
os.environ['WANDB_MODE'] = 'dryrun'
# os.environ["CUDA_VISIBLE_DEVICES"]=""
#os.environ['WANDB_NOTEBOOK_NAME'] = 'Pretrain word-level VulBERTa on Draper'
#os.environ['WANDB_NAME'] = 'linux'
#os.environ['WANDB_PROJECT'] = 'projectName'


# ## Load/initialise custom tokenizer

# In[5]:


## Tokenizer

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
from tokenizers import normalizers,decoders
from tokenizers.normalizers import StripAccents, unicode_normalizer_from_str, Replace
from tokenizers.processors import TemplateProcessing
from tokenizers import processors,pre_tokenizers
from tokenizers.models import BPE

## Init new tokenizers
#my_tokenizer = Tokenizer(BPE(unk_token="<unk>"))
#my_tokenizer = Tokenizer(BPE())


## Load pre-trained tokenizers
vocab, merges = BPE.read_file(vocab_filename="./tokenizer/drapgh-vocab.json", merges_filename="./tokenizer/drapgh-merges.txt")
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


# ## Choose dataset

# In[6]:


mydataset = args.dataset


# ### Tokenize dataset

# In[7]:


my_tokenizer.enable_truncation(max_length=1024)
my_tokenizer.enable_padding(direction='right', pad_id=1, pad_type_id=0, pad_token='<pad>', length=None, pad_to_multiple_of=None)


# In[8]:


def process_encodings(encodings):
    input_ids=[]
    attention_mask=[]
    for enc in encodings:
        try:
            input_ids.append(enc.ids)
            attention_mask.append(enc.attention_mask)
        except:
            input_ids.append(enc['func'])
            attention_mask.append(enc['attention_mask'])

    return {'input_ids':input_ids, 'attention_mask':attention_mask}


# In[9]:


def cleaner(code):
    ## Remove code comments
    pat = re.compile(r'(/\*([^*]|(\*+[^*/]))*\*+/)|(//.*)')
    code = re.sub(pat,'',code)
    code = re.sub('\n','',code)
    code = re.sub('\t','',code)
    return(code)


# In[10]:


if mydataset =='devign':
    pass
    
elif mydataset == 'combined':

    print('data/finetune/combined/' + args.data_folder + '/train.jsonl')
    file_loc = 'data/finetune/combined/' + args.data_folder + '/train.jsonl'
    print(file_loc)
    m1 = pd.read_json(file_loc, lines=True)

    file_loc = 'data/finetune/combined/' + args.data_folder + '/valid.jsonl'
    print(file_loc)
    m2 = pd.read_json(file_loc, lines=True)

    train_encodings = my_tokenizer.encode_batch(m1.func)
    train_encodings = process_encodings(train_encodings)
    
    val_encodings = my_tokenizer.encode_batch(m2.func)
    val_encodings = process_encodings(val_encodings)



elif mydataset == 'msr':
    pass
    
else:
    pass

# ### Prepare dataset

# In[11]:


class MyCustomDataset(Dataset):
    def __init__(self, encodings, labels):
        self.encodings = encodings
        self.labels = labels
        try:
            assert len(self.encodings['input_ids']) == len(self.encodings['attention_mask']) ==  len(self.labels)
        except:
            dictionary_of_list = dict(input_ids=[[None]]*len(self.encodings))

            # for loop to convert list of dict
            # to dict of list
            i = 0
            for item in encodings:
                name = item['func']
                dictionary_of_list['input_ids'][i] = name
                i+=1


            # display
            dictionary_of_list
            self.encodings = dictionary_of_list
            assert len(self.encodings['input_ids']) == len(self.encodings['input_ids']) == len(self.labels)

    def __getitem__(self, idx):
        item = {key: torch.tensor(val[idx]) for key, val in self.encodings.items()}
        item['labels'] = torch.tensor(self.labels[idx])
        return item

    def __len__(self):
        return len(self.labels)


# In[12]:


try:
    train_dataset = MyCustomDataset(train_encodings, m1.target.tolist())
    val_dataset = MyCustomDataset(val_encodings, m2.target.tolist())
    train_labels = m1.target.tolist()
except:
    try:
        train_dataset = MyCustomDataset(train_encodings, m1.label.tolist())
        val_dataset = MyCustomDataset(val_encodings, m2.label.tolist())
        train_labels = m1.label.tolist()
    except:
        y_ = []
        for i in range(0, len(train_encodings)):
            y_.append(train_encodings[i]['target'])
        y_val = []
        for i in range(0, len(val_encodings)):
            y_val.append(val_encodings[i]['target'])
        train_dataset = MyCustomDataset(train_encodings, y_)
        val_dataset = MyCustomDataset(val_encodings, y_val)
        train_labels = y_



model = RobertaForSequenceClassification.from_pretrained('models/pre_trained/')
print(model.num_parameters())


# ### Custom loss function with class weights

# In[21]:


try:
    cw = sklearn.utils.class_weight.compute_class_weight(class_weight='balanced',classes=[0,1],y=m1.label.tolist())
except:
    try:
        cw = sklearn.utils.class_weight.compute_class_weight(class_weight='balanced',classes=[0,1],y=m1.target.tolist())
    except:
        y_ = []
        for i in range(0, len(train_encodings)):
            y_.append(train_encodings[i]['target'])
        cw = sklearn.utils.class_weight.compute_class_weight(class_weight='balanced', classes=[0, 1], y=y_)

    
c_weights = torch.FloatTensor([cw[0], cw[1]])


# In[22]:


#criterion = torch.nn.CrossEntropyLoss() 
criterion = torch.nn.CrossEntropyLoss(weight=c_weights) 
criterion.to(device)

class MyTrainer(Trainer):
    def compute_loss(self, model, inputs, return_outputs=False):
        labels = inputs.pop("labels")
        outputs = model(**inputs)
        logits = outputs["logits"]
        #logits = outputs[0]        #### USE THIS IF CNN OR LSTM VURLBERTA
        loss = criterion(logits,labels)
        return (loss, outputs) if return_outputs else loss


# ## Train the model

# In[23]:

print("models/" + args.save_folder)
training_args = TrainingArguments(
        output_dir="models/" + args.save_folder,
        overwrite_output_dir=False,
        per_device_train_batch_size=args.batch,
        num_train_epochs=args.epochs,
        evaluation_strategy='epoch',
        save_total_limit=20,
        seed=seed,
        learning_rate=3e-05,
        fp16=True,
        load_best_model_at_end=True
)


# In[24]:


trainer = MyTrainer(
        model=model,
        args=training_args,
        train_dataset=train_dataset,
        eval_dataset=val_dataset 
)


# In[ ]:


trainer.train()


# In[ ]:


import mlflow
mlflow.end_run()
