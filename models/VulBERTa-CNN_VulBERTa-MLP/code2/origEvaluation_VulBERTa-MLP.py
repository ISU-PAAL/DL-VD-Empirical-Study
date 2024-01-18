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


## Set default device (GPU or CPU)



device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(device)


# In[3]:


## Deterministic/reproducible flags

seedlist = [42, 834, 692, 489, 901, 408, 819, 808, 531, 166]

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


BATCH_SIZE = args.batch

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


# ### Choose and prepare testing dataset

# In[6]:


### Choose the dataset ('draper','vuldeepecker','devign','reveal')
mydataset = args.dataset


# In[7]:


my_tokenizer.enable_truncation(max_length=1024)
my_tokenizer.enable_padding(direction='right', pad_id=1, pad_type_id=0, pad_token='<pad>', length=None, pad_to_multiple_of=None)


# In[8]:


def process_encodings(encodings):
    input_ids=[]
    attention_mask=[]
    for enc in encodings:
        input_ids.append(enc.ids)
        attention_mask.append(enc.attention_mask)
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


class MyCustomDataset(Dataset):
    def __init__(self, encodings, labels):
        self.encodings = encodings
        self.labels = labels
        try:
            assert len(self.encodings['input_ids']) == len(self.encodings['attention_mask']) ==  len(self.labels)
        except:
            dictionary_of_list = dict(input_ids=[[None]]*len(self.encodings), attention_mask=[[None]]*len(self.encodings))

            # for loop to convert list of dict
            # to dict of list
            i = 0
            for item in encodings:
                name = item['func']
                dictionary_of_list['input_ids'][i] = name
                dictionary_of_list['attention_mask'][i] = item['attention_mask']
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


# In[11]:


if mydataset=='devign':
    test_index=set()

    with open('data/finetune/devign/test.txt') as f:
        for line in f:
            line=line.strip()
            test_index.add(int(line))
    mydata = pd.read_json('data/finetune/devign/Devign.json')
    m3=mydata.iloc[list(test_index)]

    mydata = None
    del(mydata)
    m3.func = m3.func.apply(cleaner)

    test_encodings = my_tokenizer.encode_batch(m3.func)
    test_encodings = process_encodings(test_encodings)
    test_dataset = MyCustomDataset(test_encodings, m3.target.tolist())

    train_index = set()
    valid_index = set()

    with open('data/finetune/devign/train.txt') as f:
        for line in f:
            line = line.strip()
            train_index.add(int(line))

    with open('data/finetune/devign/valid.txt') as f:
        for line in f:
            line = line.strip()
            valid_index.add(int(line))
    mydata = pd.read_json('data/finetune/devign/Devign.json')
    m1 = mydata.iloc[list(train_index)]
    m2 = mydata.iloc[list(valid_index)]

    mydata = None
    del (mydata)
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

    try:
        train_dataset = MyCustomDataset(train_encodings, m1.target.tolist())
        val_dataset = MyCustomDataset(val_encodings, m2.target.tolist())
        test_dataset = MyCustomDataset(test_encodings, m3.target.tolist())
        train_labels = m1.target.tolist()
    except:
        try:
            train_dataset = MyCustomDataset(train_encodings, m1.label.tolist())
            val_dataset = MyCustomDataset(val_encodings, m2.label.tolist())
            test_dataset = MyCustomDataset(test_encodings, m3.target.tolist())
            train_labels = m1.label.tolist()
        except:
            y_test = []
            for i in range(0, len(test_encodings)):
                y_test.append(test_encodings[i]['target'])
            y_val = []
            for i in range(0, len(val_encodings)):
                y_val.append(val_encodings[i]['target'])
            y_train = []
            for i in range(0, len(train_encodings)):
                y_train.append(train_encodings[i]['target'])
            test_dataset = MyCustomDataset(test_encodings, y_test)
            val_dataset = MyCustomDataset(val_encodings, y_val)
            train_dataset = MyCustomDataset(train_encodings, y_train)
            test_labels = y_test

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

    lists = [val_encodings_vuln, val_encodings_not_vuln]
    val_encodings = [val for tup in zip(*lists) for val in tup]

    lists = [test_encodings_vuln, test_encodings_not_vuln]
    test_encodings = [val for tup in zip(*lists) for val in tup]

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
            for i in range(0, len(test_encodings)):
                y_.append(test_encodings[i]['target'])
            y_val = []
            for i in range(0, len(val_encodings)):
                y_val.append(val_encodings[i]['target'])
            test_dataset = MyCustomDataset(test_encodings, y_)
            val_dataset = MyCustomDataset(val_encodings, y_val)
            test_labels = y_

else:
    m3 = pd.read_pickle('data/finetune/%s/%s_test.pkl'%(mydataset,mydataset))
    
    
    try:
        m3.functionSource = m3.functionSource.apply(cleaner)
        test_encodings = my_tokenizer.encode_batch(m3.functionSource)
        test_encodings = process_encodings(test_encodings)
        
        if  mydataset =='draper':
            test_dataset = MyCustomDataset(test_encodings, (m3['combine']*1).tolist())
        else:
            test_dataset = MyCustomDataset(test_encodings, m3.label.tolist())
    except:
        m3.func = m3.func.apply(cleaner)
        test_encodings = my_tokenizer.encode_batch(m3.func)
        test_encodings = process_encodings(test_encodings)
        test_dataset = MyCustomDataset(test_encodings, m3.label.tolist())


# In[ ]:


############ D2A ONLY
#task = 'function'
#m3 = pd.read_csv('data/finetune/%s/%s/d2a_lbv1_%s_val.csv'%(mydataset,task,task))
#m3.code = m3.code.apply(cleaner)
#test_encodings = my_tokenizer.encode_batch(m3.code)
#test_encodings = process_encodings(test_encodings)
#test_dataset = MyCustomDataset(test_encodings, m3.label.tolist())
#########test_dataset = MyCustomDataset(test_encodings, [0]*len(m3))


# ## Load fine-tuned VulBERTa-MLP model

# In[12]:


mymodel=mydataset


# In[13]:
#print([name for name in os.listdir("models") if os.path.isdir(name)])

tmp = os.listdir("models/VB-MLP_%s" % mydataset + str(args.seed_input))
tmp.sort()

model = RobertaForSequenceClassification.from_pretrained("models/VB-MLP_%s" % mydataset + str(args.seed_input) + '/' +  tmp[len(tmp)-1])
#model = RobertaForSequenceClassification.from_pretrained("/home/<ANONYMOUS>/VulBERTa/models/fine_tuned/VB-MLP_devign")
print(model.num_parameters())


# In[14]:





# In[24]:


def softmax_accuracy(probs,all_labels):
    #print(probs)
    def getClass(x):
        return(x.index(max(x)))
    
    all_labels = all_labels.tolist()
    probs_list=probs[1].tolist()
    probs = pd.Series(probs[1].tolist())
    #print(probs)
    all_predicted = probs.apply(getClass)
    all_predicted.reset_index(drop=True, inplace=True)
    vc = pd.value_counts(all_predicted == all_labels)
    try:
        acc = vc[1]/len(all_labels)
    except:
        if(vc.index[0]==False):
            acc = 0
        else:
            acc = 1
    
    #print(acc)
    #print(all_predicted)
    #print(probs)
    return(acc,all_predicted, probs)


# In[25]:


#get_ipython().run_cell_magic('capture', '', '\nmultigpu=False\nif multigpu:\n    model = torch.nn.DataParallel(model)\nmodel.to(device)')

#%%capture

multigpu=False
if multigpu:
    model = torch.nn.DataParallel(model)
model.to(device)


# ### Predict

# In[26]:

def evaluate_testing(all_pred, all_labels):
    def getClass(x):
        return(x.index(max(x)))

    probs = pd.Series(all_pred)
    all_predicted = probs.apply(getClass)
    all_predicted.reset_index(drop=True, inplace=True)
    vc = pd.value_counts(all_predicted == all_labels)

    probs2=[]
    for x in probs:
        probs2.append(x[1])

    confusion = sklearn.metrics.confusion_matrix(y_true=all_labels, y_pred=all_predicted)
    print('Confusion matrix: \n',confusion)

    try:
        tn, fp, fn, tp = confusion.ravel()
        print('\nTP:',tp)
        print('FP:',fp)
        print('TN:',tn)
        print('FN:',fn)

        ## Performance measure
        print('\nAccuracy: '+ str(sklearn.metrics.accuracy_score(y_true=all_labels, y_pred=all_predicted)))
        print('Precision: '+ str(sklearn.metrics.precision_score(y_true=all_labels, y_pred=all_predicted)))
        print('F-measure: '+ str(sklearn.metrics.f1_score(y_true=all_labels, y_pred=all_predicted)))
        print('Recall: '+ str(sklearn.metrics.recall_score(y_true=all_labels, y_pred=all_predicted)))
        print('Precision-Recall AUC: '+ str(sklearn.metrics.average_precision_score(y_true=all_labels, y_score=probs2)))
        print('AUC: '+ str(sklearn.metrics.roc_auc_score(y_true=all_labels, y_score=probs2)))
        print('MCC: '+ str(sklearn.metrics.matthews_corrcoef(y_true=all_labels, y_pred=all_predicted)))
    except:
        None
        print('This is multiclass prediction')
    return(all_predicted)

TEST_ONLY = False
import torchtext


# try:
#     train_dataset = MyCustomDataset(train_encodings, m1.target.tolist())
#     val_dataset = MyCustomDataset(val_encodings, m2.target.tolist())
#     train_labels = m1.target.tolist()
# except:
#     try:
#         train_dataset = MyCustomDataset(train_encodings, m1.label.tolist())
#         val_dataset = MyCustomDataset(val_encodings, m2.label.tolist())
#         train_labels = m1.label.tolist()
#     except:
#         y_ = []
#         for i in range(0, len(train_encodings)):
#             y_.append(train_encodings[i]['target'])
#         y_val = []
#         for i in range(0, len(val_encodings)):
#             y_val.append(val_encodings[i]['target'])
#         train_dataset = MyCustomDataset(train_encodings, y_)
#         val_dataset = MyCustomDataset(val_encodings, y_val)
#         train_labels = y_


test_loader = DataLoader(test_dataset, batch_size=args.batch)
train_loader = DataLoader(train_dataset, batch_size=args.batch)
val_loader = DataLoader(val_dataset, batch_size=args.batch)

with torch.no_grad():
    running_acc_test = 0
    running_loss_test = 0
    all_pred =[]
    all_pred2 = []
    all_pred3 = []
    all_labels=[]
    all_predictions = []
    for batch in test_loader:
        input_ids = batch['input_ids'].to(device)
        attention_mask = batch['attention_mask'].to(device)
        labels = batch['labels'].to(device)
        output_test = model(input_ids, attention_mask=attention_mask, labels=labels)
        acc_test,pred, predictions = softmax_accuracy(output_test,batch['labels'])
        all_pred += pred.tolist()
        running_acc_test += acc_test
        all_pred2 += output_test[1].tolist()
        all_pred3 += output_test[1].tolist()
        all_labels += batch['labels'].tolist()
        all_predictions += predictions.tolist()

i = 0
for row in all_pred2:
    all_pred2[i] = torch.nn.functional.softmax(torch.tensor(row), dim=0)[1].item()
    i+=1

results_test = pd.DataFrame(all_pred2)
results_test = results_test.rename(columns={0: "prob"})
predicted_labels_df_train = pd.DataFrame(all_pred)
predicted_labels_df_train = predicted_labels_df_train.rename(columns={0: "pred"})
actual_labels_df_train = pd.DataFrame(all_labels)
actual_labels_df_train= actual_labels_df_train.rename(columns={0: "target_"})

m3.reset_index(inplace=True)
results_test = pd.concat([results_test, predicted_labels_df_train, actual_labels_df_train, pd.concat([m3,m3]).sort_index().reset_index(drop=True)], axis="columns")
results_test['seed'] = args.seed_input
results_test['split'] = "test"
#results = results.drop(columns=["dropme"])
ap=evaluate_testing(all_pred3, all_labels)



with torch.no_grad():
    running_acc_test = 0
    running_loss_test = 0
    all_pred =[]
    all_pred2 = []
    all_pred3 = []
    all_labels=[]
    all_predictions = []
    for batch in train_loader:
        input_ids = batch['input_ids'].to(device)
        attention_mask = batch['attention_mask'].to(device)
        labels = batch['labels'].to(device)
        output_test = model(input_ids, attention_mask=attention_mask, labels=labels)
        acc_test, pred, predictions = softmax_accuracy(output_test, batch['labels'])
        all_pred += pred.tolist()
        running_acc_test += acc_test
        all_pred2 += output_test[1].tolist()
        all_pred3 += output_test[1].tolist()
        all_labels += batch['labels'].tolist()
        all_predictions += predictions.tolist()

i = 0
for row in all_pred2:
    all_pred2[i] = torch.nn.functional.softmax(torch.tensor(row), dim=0)[1].item()
    i+=1

results_train = pd.DataFrame(all_pred2)
results_train = results_train.rename(columns={0: "prob"})
predicted_labels_df_train = pd.DataFrame(all_pred)
predicted_labels_df_train = predicted_labels_df_train.rename(columns={0: "pred"})
actual_labels_df_train = pd.DataFrame(all_labels)
actual_labels_df_train = actual_labels_df_train.rename(columns={0: "target_"})

m1.reset_index(inplace=True)
results_train = pd.concat([results_train, predicted_labels_df_train, actual_labels_df_train, pd.concat([m1,m1]).sort_index().reset_index(drop=True)], axis="columns")
results_train['seed'] = args.seed_input
results_train['split'] = "train"
#results = results.drop(columns=["dropme"])
ap=evaluate_testing(all_pred3, all_labels)


with torch.no_grad():
    running_acc_test = 0
    running_loss_test = 0
    all_pred =[]
    all_pred2 = []
    all_pred3 = []
    all_labels=[]
    all_predictions = []
    for batch in val_loader:
        input_ids = batch['input_ids'].to(device)
        attention_mask = batch['attention_mask'].to(device)
        labels = batch['labels'].to(device)
        output_test = model(input_ids, attention_mask=attention_mask, labels=labels)
        acc_test, pred, predictions = softmax_accuracy(output_test, batch['labels'])
        all_pred += pred.tolist()
        running_acc_test += acc_test
        all_pred2 += output_test[1].tolist()
        all_pred3 += output_test[1].tolist()
        all_labels += batch['labels'].tolist()
        all_predictions += predictions.tolist()

i = 0
for row in all_pred2:
    all_pred2[i] = torch.nn.functional.softmax(torch.tensor(row), dim=0)[1].item()
    i+=1

results_valid = pd.DataFrame(all_pred2)
results_valid = results_valid.rename(columns={0: "prob"})
predicted_labels_df_valid = pd.DataFrame(all_pred)
predicted_labels_df_valid = predicted_labels_df_valid.rename(columns={0: "pred"})
actual_labels_df_valid = pd.DataFrame(all_labels)
actual_labels_df_valid = actual_labels_df_valid.rename(columns={0: "target_"})

m2.reset_index(inplace=True)
results_valid = pd.concat([results_valid, predicted_labels_df_valid, actual_labels_df_valid, pd.concat([m2,m2]).sort_index().reset_index(drop=True)], axis="columns")
results_valid['seed'] = args.seed_input
results_valid['split'] = "valid"
#results = results.drop(columns=["dropme"])
ap=evaluate_testing(all_pred3, all_labels)



results = pd.concat([results_train, results_valid, results_test])
output_file_name = "results_for_seed_" + str(args.seed_input) + args.dataset + '_MLP.csv'
results.to_csv(output_file_name)
