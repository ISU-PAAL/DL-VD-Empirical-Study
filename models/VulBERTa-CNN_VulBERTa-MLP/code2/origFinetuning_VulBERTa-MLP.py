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
    train_index=set()
    valid_index=set()

    with open('data/finetune/devign/train.txt') as f:
        for line in f:
            line=line.strip()
            train_index.add(int(line))

    with open('data/finetune/devign/valid.txt') as f:
        for line in f:
            line=line.strip()
            valid_index.add(int(line))
    mydata = pd.read_json('data/finetune/devign/Devign.json')
    m1=mydata.iloc[list(train_index)]
    m2=mydata.iloc[list(valid_index)]

    mydata = None
    del(mydata)
    m1.func = m1.func.apply(cleaner)
    m2.func = m2.func.apply(cleaner)
    
    train_encodings = my_tokenizer.encode_batch(m1.func)
    train_encodings = process_encodings(train_encodings)
    
    val_encodings = my_tokenizer.encode_batch(m2.func)
    val_encodings = process_encodings(val_encodings)
    
elif mydataset == 'combined':

    m1 = pd.read_json('data/finetune/combined/train.jsonl', lines=True)
    m2 = pd.read_json('data/finetune/combined/valid.jsonl', lines=True)
    m3 = pd.read_json('data/finetune/combined/test.jsonl', lines=True)

    train_encodings = my_tokenizer.encode_batch(m1.func)
    train_encodings = process_encodings(train_encodings)
    
    val_encodings = my_tokenizer.encode_batch(m2.func)
    val_encodings = process_encodings(val_encodings)

    test_encodings = my_tokenizer.encode_batch(m3.func)
    test_encodings = process_encodings(test_encodings)

elif mydataset == 'msr':
    train_index = set()
    valid_index = set()
    test_index = set()

    with open('data/finetune/msr/train.txt') as f:
        for line in f:
            line = line.strip()
            train_index.add(int(line))

    with open('data/finetune/msr/valid.txt') as f:
        for line in f:
            line = line.strip()
            valid_index.add(int(line))

    with open('data/finetune/msr/test.txt') as f:
        for line in f:
            line = line.strip()
            test_index.add(int(line))

    generate_jsons = False
    if generate_jsons == True:
        import json
        mydata = pd.read_json('data/finetune/msr/MSR_data_cleaned.json')
        m1 = mydata.T.iloc[list(train_index)]
        m2 = mydata.T.iloc[list(valid_index)]
        m3 = mydata.T.iloc[list(test_index)]
        m1['id'] = m1.index
        m2['id'] = m2.index
        m3['id'] = m3.index
        m1 = m1.drop(m1.columns[0], axis=1)
        m2 = m2.drop(m2.columns[0], axis=1)
        m3 = m3.drop(m3.columns[0], axis=1)
        m1.to_json(r'data/finetune/msr/train.json', orient='split')
        m2.to_json(r'data/finetune/msr/valid.json', orient='split')
        m3.to_json(r'data/finetune/msr/test.json', orient='split')



    m1 = pd.read_json('data/finetune/msr/train.json', orient='split')
    m2 = pd.read_json('data/finetune/msr/valid.json', orient='split')
    m3 = pd.read_json('data/finetune/msr/test.json', orient='split')



    mydata = None
    del (mydata)

    m1.func_before = m1.func_before.apply(cleaner)
    train_encodings_vuln = my_tokenizer.encode_batch(m1.func_before)

    m1.func_after = m1.func_after.apply(cleaner)
    train_encodings_not_vuln = my_tokenizer.encode_batch(m1.func_after)

    try:
        train_encodings_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 0} for enc in train_encodings_vuln]
        train_encodings_not_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 1} for enc in train_encodings_not_vuln]
    except:
        train_encodings_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 0} for enc in train_encodings_vuln]
        train_encodings_not_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 1} for enc in train_encodings_not_vuln]

    m2.func_before = m2.func_before.apply(cleaner)
    val_encodings_vuln = my_tokenizer.encode_batch(m2.func_before)

    m2.func_after = m2.func_after.apply(cleaner)
    val_encodings_not_vuln = my_tokenizer.encode_batch(m2.func_after)

    try:
        val_encodings_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 0} for enc in val_encodings_vuln]
        val_encodings_not_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 1} for enc in val_encodings_not_vuln]
    except:
        val_encodings_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 0} for enc in val_encodings_vuln]
        val_encodings_not_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 1} for enc in val_encodings_not_vuln]

    m3.func_before = m3.func_before.apply(cleaner)
    test_encodings_vuln = my_tokenizer.encode_batch(m3.func_before)

    m3.func_after = m3.func_after.apply(cleaner)
    test_encodings_not_vuln = my_tokenizer.encode_batch(m3.func_after)

    try:
        test_encodings_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 0} for enc in test_encodings_vuln]
        test_encodings_not_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 1} for enc in test_encodings_not_vuln]
    except:
        test_encodings_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 0} for enc in test_encodings_vuln]
        test_encodings_not_vuln = [{'func': enc.ids, 'attention_mask': enc.attention_mask, 'target': 1} for enc in test_encodings_not_vuln]

    lists = [train_encodings_vuln, train_encodings_not_vuln]
    train_encodings = [val for tup in zip(*lists) for val in tup]
    #train_encodings = process_encodings(train_encodings)

    lists = [val_encodings_vuln, val_encodings_not_vuln]
    val_encodings = [val for tup in zip(*lists) for val in tup]
    #val_encodings = process_encodings(val_encodings)

    lists = [test_encodings_vuln, test_encodings_not_vuln]
    test_encodings = [val for tup in zip(*lists) for val in tup]
    #test_encodings = process_encodings(test_encodings)
    
else:
    m1 = pd.read_pickle('data/finetune/%s/%s_train.pkl'%(mydataset,mydataset))
    m2 = pd.read_pickle('data/finetune/%s/%s_val.pkl'%(mydataset,mydataset))
    
    try:
        m1.functionSource = m1.functionSource.apply(cleaner)
        m2.functionSource = m2.functionSource.apply(cleaner)
        
        if mydataset =='draper':
            m1['target'] = m1['combine']*1
            m2['target'] = m2['combine']*1
        
        train_encodings = my_tokenizer.encode_batch(m1.functionSource)
        train_encodings = process_encodings(train_encodings)

        val_encodings = my_tokenizer.encode_batch(m2.functionSource)
        val_encodings = process_encodings(val_encodings)
        
    except:
        m1.func = m1.func.apply(cleaner)
        m2.func = m2.func.apply(cleaner)
        
        train_encodings = my_tokenizer.encode_batch(m1.func)
        train_encodings = process_encodings(train_encodings)

        val_encodings = my_tokenizer.encode_batch(m2.func)
        val_encodings = process_encodings(val_encodings)


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


# In[13]:


########################################################## D2A dataset ONLY
#
#task = 'function'
#
#m1 = pd.read_csv('data/finetune/%s/%s/d2a_lbv1_%s_train.csv'%(mydataset,task,task))
#m1.code = m1.code.apply(cleaner)
#train_encodings = my_tokenizer.encode_batch(m1.code)
#train_encodings = process_encodings(train_encodings)
#train_dataset = MyCustomDataset(train_encodings, m1.label.tolist())

#m2 = pd.read_csv('data/finetune/%s/%s/d2a_lbv1_%s_dev.csv'%(mydataset,task,task))
#m2.code = m2.code.apply(cleaner)
#val_encodings = my_tokenizer.encode_batch(m2.code)
#val_encodings = process_encodings(val_encodings)
#val_dataset = MyCustomDataset(val_encodings, m2.label.tolist())


# ### streaming dataset ONLY! 

# In[14]:


################################## STREAMING DATASET #############################
# import pickle  


# m1 = pd.read_pickle('data/finetune/%s/%s_train.pkl'%(mydataset,mydataset))
# m1.functionSource = m1.functionSource.apply(cleaner)
# m1['target'] = m1['combine']*1
# m1 = np.array_split(m1, 5)

# split = 'train'
# with open('data/finetune/draper/draper_stream_%s.pkl'%split, 'wb') as f:
#     for m in m1:
#         encodings = my_tokenizer.encode_batch(m.functionSource)
#         labels = m.target.tolist()
#         for enc,label in zip(encodings,labels):
#             pickle.dump({'input_ids':enc.ids, 'attention_mask':enc.attention_mask, 'labels':label},f)

            
# m2 = pd.read_pickle('data/finetune/%s/%s_val.pkl'%(mydataset,mydataset))
# m2.functionSource = m2.functionSource.apply(cleaner)
# m2['target'] = m2['combine']*1
# m2 = np.array_split(m2, 5)

# split = 'val'
# with open('data/finetune/draper/draper_stream_%s.pkl'%split, 'wb') as f:
#     for m in m2:
#         encodings = my_tokenizer.encode_batch(m.functionSource)
#         labels = m.target.tolist()
#         for enc,label in zip(encodings,labels):
#             pickle.dump({'input_ids':enc.ids, 'attention_mask':enc.attention_mask, 'labels':label},f)

            
# m3 = pd.read_pickle('data/finetune/%s/%s_test.pkl'%(mydataset,mydataset))
# m3.functionSource = m3.functionSource.apply(cleaner)
# m3['target'] = m3['combine']*1
# m3 = np.array_split(m3, 5)

# split = 'test'
# with open('data/finetune/draper/draper_stream_%s.pkl'%split, 'wb') as f:
#     for m in m3:
#         encodings = my_tokenizer.encode_batch(m.functionSource)
#         labels = m.target.tolist()
#         for enc,label in zip(encodings,labels):
#             pickle.dump({'input_ids':enc.ids, 'attention_mask':enc.attention_mask, 'labels':label},f)


# In[15]:


# class MyDataset(IterableDataset):

#     def __init__(self,filename,rcount):
     
#         self.filename=filename
#         self.len_labels=rcount
#         super().__init__()
                    
#     def process(self,filename):
#         with open(filename, "rb") as f:
#             while True:
#                 try:
#                     item = pickle.load(f)
#                     yield {'input_ids': torch.tensor(item['input_ids']), 'attention_mask':torch.tensor(item['attention_mask']), 'labels':torch.tensor(item['labels'])}
#                 except EOFError:
#                     break
                    
#     def __len__(self):
#         return self.len_labels

#     def __iter__(self):
#         dataset=self.process(self.filename)          
#         return dataset


# In[ ]:





# In[16]:


# train_rcount = len(pd.read_pickle('data/finetune/draper/draper_train.pkl'))
# train_dataset = MyDataset('data/finetune/draper/draper_stream_train.pkl', train_rcount)


# In[17]:


# val_rcount = len(pd.read_pickle('data/finetune/draper/draper_val.pkl'))
# val_dataset = MyDataset('data/finetune/draper/draper_stream_val.pkl', val_rcount)


# In[18]:


# import pickle
# pickle.dump( train_dataset, open( "td.pkl", "wb" ))
# pickle.dump( val_dataset, open( "vd.pkl", "wb" ))


# In[19]:


# import pickle
# train_dataset = pickle.load(open( "td.pkl", "rb" ))
# val_dataset = pickle.load(open( "vd.pkl", "rb" ))


# ### Load pretrained model

# In[20]:


## Pre-trained RoBERTa

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


training_args = TrainingArguments(
        output_dir="models/VB-MLP_%s" % mydataset + str(args.seed_input),
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

