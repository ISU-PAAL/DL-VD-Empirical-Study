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
    pass
elif mydataset == 'combined':



    m3 = pd.read_json('data/finetune/combined/' + args.data_folder + '/test.jsonl', lines=True)

    test_encodings = my_tokenizer.encode_batch(m3.func)
    test_encodings = process_encodings(test_encodings)

    try:
        test_dataset = MyCustomDataset(test_encodings, m3.target.tolist())

    except:
        try:

            test_dataset = MyCustomDataset(test_encodings, m3.target.tolist())
        except:
            y_test = []
            for i in range(0, len(test_encodings)):
                y_test.append(test_encodings[i]['target'])

            test_dataset = MyCustomDataset(test_encodings, y_test)

            test_labels = y_test

elif mydataset == 'msr':
    pass

else:
    pass




mymodel=mydataset



tmp = os.listdir("models/" + args.save_folder)
tmp.sort()

print(tmp)
print("models/" + args.save_folder + '/' +  tmp[len(tmp)-1])
model = RobertaForSequenceClassification.from_pretrained("models/"  + args.save_folder + '/' +  tmp[len(tmp)-1])
#model = RobertaForSequenceClassification.from_pretrained("/home/<ANONYMOUS>/VulBERTa/models/fine_tuned/VB-MLP_devign")
print(model.num_parameters())





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





test_loader = DataLoader(test_dataset, batch_size=args.batch)


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

