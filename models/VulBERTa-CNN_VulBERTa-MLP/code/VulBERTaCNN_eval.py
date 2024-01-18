#!/usr/bin/env python
# coding: utf-8

#--seed_input=42
#--train_test=test
#--epochs=20
#--batch=4


# In[1]:


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
import torchtext.legacy.data as data
import torchtext.vocab as vocab
import sklearn.metrics
from transformers import RobertaModel
from torch import nn
from torch.optim import Adam
from clang import *
import tqdm


parser = argparse.ArgumentParser()

## Required parameters
parser.add_argument("--seed_input", default=None, type=int, required=True,
                    help="The input training data file (a text file).")
parser.add_argument("--batch", default=4, type=int, required=False,
                    help="The input training data file (a text file).")
parser.add_argument("--generate_json", default=None, type=bool, required=True,
                    help="determines whether to generate jsons or simply read them from previous run")    
parser.add_argument("--data_path")
parser.add_argument("--model_path")
parser.add_argument("--epoch_load", default=10)
parser.add_argument("--eval_export", action="store_true")
parser.add_argument("--sample", action="store_true")
parser.add_argument("--no_cuda", action="store_true")

args = parser.parse_args()

if args.sample:
    sample_text="_sample"
else:
    sample_text=""

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


# In[2]:


import warnings
warnings.filterwarnings("ignore")


# In[3]:


device = torch.device("cuda" if torch.cuda.is_available() and not args.no_cuda else "cpu")
multigpu = False
# if device == torch.device('cuda'):
# 	multigpu = torch.cuda.device_count() > 1
print('Device: ',device)
print('MultiGPU: ',multigpu)


# In[4]:


## Training & vocab parameters
DATA_PATH = 'data'
VOCAB_SIZE = 50000
BATCH_SIZE = args.batch
EMBED_SIZE = VOCAB_SIZE+2
EMBED_DIM = 768 #768


# In[5]:


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


## Load pre-trained tokenizers
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


# ### PREPARE DATA

# In[6]:


TEST_ONLY = False



# In[8]:


my_tokenizer.enable_truncation(max_length=1024)
my_tokenizer.enable_padding(direction='right', pad_id=1, pad_type_id=0, pad_token='<pad>', length=1024, pad_to_multiple_of=None)


# In[9]:


def cleaner(code):
    ## Remove code comments
    pat = re.compile(r'(/\*([^*]|(\*+[^*/]))*\*+/)|(//.*)')
    code = re.sub(pat,'',code)
    code = re.sub('\n','',code)
    code = re.sub('\t','',code)
    return(code)


# In[10]:


def process_encodings(encodings):
    input_ids=[]
    attention_mask=[]
    for enc in encodings:
        input_ids.append(enc.ids)
        attention_mask.append(enc.attention_mask)
    return {'input_ids':input_ids, 'attention_mask':attention_mask}


# In[11]:


def replace_colname(x):
    try:
        x = x.rename(columns={'functionSource': "func"})
    except:
        None

    try:
        x = x.rename(columns={'code': "func"})
    except:
        None

    try:
        x = x.rename(columns={'label': "target"})
    except:
        None
    return(x)

import jsonlines
def read_jsonl(filename):
    with jsonlines.open(filename) as reader:
        data = list(tqdm.tqdm(reader, desc="read file"))
    mydata = pd.DataFrame(data)
    return mydata

print("loading data from", args.data_path)
test_data = read_jsonl(args.data_path)
test_data.target = test_data.target.astype(int)
if args.sample:
    test_data = test_data.sample(100)
print(test_data.target.value_counts())

if args.eval_export:
    train_data = read_jsonl(os.path.join(os.path.dirname(args.data_path), "train.jsonlines"))
    valid_data = read_jsonl(os.path.join(os.path.dirname(args.data_path), "valid.jsonlines"))
    train_data.target = train_data.target.astype(int)
    valid_data.target = valid_data.target.astype(int)
    if args.sample:
        train_data = train_data.sample(100)
        valid_data = valid_data.sample(100)


print("encoding")
def encode(funcs):
    encodings = []
    for func in tqdm.tqdm(funcs, desc="encode"):
        encodings.append(my_tokenizer.encode(func))
    return encodings


# print(test_data.func)
test_data.func = test_data.func.apply(cleaner)
test_encodings = encode(test_data.func)
# print(test_encodings[0].tokens)
# print(test_encodings[0].ids)
# print(test_encodings[1].tokens)
# print(test_encodings[1].ids)
# print(test_encodings[2].tokens)
# print(test_encodings[2].ids)
if args.eval_export:
    test_encodings = [{'func':enc.ids,'target':lab,'index': i} for enc,lab,i in zip(test_encodings,test_data.target.tolist(), test_data.example_index.tolist())]

    CODES = data.Field(batch_first=True, fix_length=1024, use_vocab=False)
    LABEL = data.LabelField(dtype=torch.long, is_target=True, use_vocab=False)
    INDEX = data.LabelField(dtype=torch.long, is_target=False, use_vocab=False)
    fields = {'func': ('codes', CODES), 'target': ('label', LABEL), 'index': ('index', INDEX)}
else:
    test_encodings = [{'func':enc.ids,'target':lab} for enc,lab in zip(test_encodings,test_data.target.tolist())]

    CODES = data.Field(batch_first=True, fix_length=1024, use_vocab=False)
    LABEL = data.LabelField(dtype=torch.long, is_target=True, use_vocab=False)
    fields = {'func': ('codes', CODES), 'target': ('label', LABEL)}
print("test_encodings head", test_encodings[:5])

# In[12]:
print("dataset")

class TabularDataset_From_List(data.Dataset):
    def __init__(self, input_list, format, fields, skip_header=False, **kwargs):
        make_example = {
            'json': data.Example.fromJSON, 'dict': data.Example.fromdict}[format.lower()]

        examples = [make_example(item, fields) for item in input_list]

        if make_example in (data.Example.fromdict, data.Example.fromJSON):
            fields, field_dict = [], fields
            for field in field_dict.values():
                if isinstance(field, list):
                    fields.extend(field)
                else:
                    fields.append(field)

        super(TabularDataset_From_List, self).__init__(examples, fields, **kwargs)

    @classmethod
    def splits(cls, path=None, root='.data', train=None, validation=None,
               test=None, **kwargs):
        if path is None:
            path = cls.download(root)
        train_data = None if train is None else cls(
            train, **kwargs)
        val_data = None if validation is None else cls(
            validation, **kwargs)
        test_data = None if test is None else cls(
            test, **kwargs)
        return tuple(d for d in (train_data, val_data, test_data)
                     if d is not None)


## Import the 100K data as TabularDataset



test_dataset = TabularDataset_From_List(test_encodings,'dict',fields = fields)
print('')

# ### IF ITERABLE DATASETTEST_ONLY

# In[13]:

MAX_VOCAB_SIZE = VOCAB_SIZE

# place into iterators

print("iterators")
test_iterator = data.BucketIterator(
    test_dataset, 
    batch_size = 1,
    sort = False,
    shuffle = False)

UNK_IDX = 3
PAD_IDX = 1

# ### Define VulBERTa-CNN model

# In[18]:


class myCNN(nn.Module):
    def __init__(self, EMBED_SIZE, EMBED_DIM):
        super(myCNN,self).__init__()
        
        pretrained_weights = RobertaModel.from_pretrained('models/pre_trained/').embeddings.word_embeddings.weight

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

    


# In[19]:


model = myCNN(EMBED_SIZE,EMBED_DIM)


# In[20]:


#model.embed.weight.data[UNK_IDX] = torch.zeros(EMBED_DIM)
model.embed.weight.data[PAD_IDX] = torch.zeros(EMBED_DIM)


# In[21]:


if multigpu:
    model = torch.nn.DataParallel(model)
model.to(device)
print(model)


# In[22]:


print('Num of trainable param: ',sum(p.numel() for p in model.parameters() if p.requires_grad))


# ### Prepare loss function

# In[23]:

import sklearn

# In[24]:


def softmax_accuracy(probs,all_labels):
    def getClass(x):
        return(x.index(max(x)))
    
    all_labels = all_labels.tolist()
    probs = pd.Series(probs.tolist())
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
    return(acc, all_predicted, probs)


# ### Start training

# In[25]:

# ### Define evaluation function

# In[27]:


def evaluate_testing(all_pred, all_labels):
    def getClass(x):
        return(x.index(max(x)))

    probs = pd.Series(all_pred)
    # print(probs)
    all_predicted = probs.apply(getClass)
    # print(all_predicted)
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
    


# ### Evaluate on the testing set

# In[28]:


print('Testing started.......')
## Testing

def evaluate_epoch(epoch_load):
    print("evaluating epoch", epoch_load)
    print("loading model from", args.model_path + f'/model_ep_{epoch_load}.tar')
    checkpoint = torch.load(args.model_path + f'/model_ep_{epoch_load}.tar', map_location='cuda')
    model.load_state_dict(checkpoint['model_state_dict'])

    model.eval()
    with torch.no_grad():
        running_acc_test = 0
        all_pred =[]
        all_pred2 = []
        all_pred3 = []
        all_labels=[]
        all_predictions = []
        for batch in test_iterator:
            batch.codes, batch.label = batch.codes.to(device), batch.label.to(device)
            # print(batch.codes, batch.label)
            output_test = model(batch.codes).squeeze(1)
            acc_test,pred, predictions = softmax_accuracy(output_test,batch.label)
            all_pred += pred.tolist()
            running_acc_test += acc_test
            all_pred2 += output_test.tolist()
            all_pred3 += output_test.tolist()
            all_labels += batch.label.tolist()
            all_predictions += predictions.tolist()

    # i = 0
    # for row in all_pred2:
    #     all_pred2[i] = torch.nn.functional.softmax(torch.tensor(row), dim=0)[1].item()
    #     i+=1

    # results_test = pd.DataFrame(all_pred2)
    # results_test = results_test.rename(columns={0: "prob"})
    # predicted_labels_df_train = pd.DataFrame(all_pred)
    # predicted_labels_df_train = predicted_labels_df_train.rename(columns={0: "pred"})
    # actual_labels_df_train = pd.DataFrame(all_labels)
    # actual_labels_df_train= actual_labels_df_train.rename(columns={0: "target_"})

    # test_data.reset_index(inplace=True)
    # results_test = pd.concat([results_test, predicted_labels_df_train, actual_labels_df_train, pd.concat([test_data,test_data]).sort_index().reset_index(drop=True)], axis="columns")
    # results_test['seed'] = args.seed_input
    # results_test['split'] = "test"
    #results = results.drop(columns=["dropme"])
    ap=evaluate_testing(all_pred3, all_labels)

if args.epoch_load == "all":
    for i in range(1, 11):
        evaluate_epoch(i)
else:
    evaluate_epoch(args.epoch_load)



def evaluate_dataset(dataset, name, batch_size=args.batch):
    loader = data.BucketIterator(
        dataset, 
        batch_size = 1,
        sort = False,
        shuffle = False)

    with torch.no_grad():
        all_pred =[]
        all_prob = []
        all_labels=[]
        all_indices = []
        for batch in tqdm.tqdm(loader):
            batch.codes, batch.label = batch.codes.to(device), batch.label.to(device)
            output = model(batch.codes).squeeze(1)
            acc_test, pred, predictions = softmax_accuracy(output, batch.label)
            all_pred += pred.tolist()
            all_prob += output.tolist()
            all_labels += batch.label.tolist()
            all_indices.extend(batch.index.tolist())

    # print(all_prob)
    all_prob = torch.tensor(all_prob)
    # print(all_prob)
    all_prob = torch.nn.functional.softmax(all_prob, dim=1)
    # print(all_prob)
    all_prob = all_prob.numpy()[:, 1]
    # print(all_prob)

    all_pred = np.array(all_pred)
    all_labels= np.array(all_labels)
    all_indices =  np.array(all_indices)

    results = pd.DataFrame({"prob": all_prob, "prediction": all_pred, "target": all_labels, "example_index": all_indices})
    results['seed'] = args.seed_input
    results['split'] = name

    return results

if args.eval_export:
    train_data.func = train_data.func.apply(cleaner)
    train_encodings = encode(train_data.func)
    train_encodings = [{'func':enc.ids,'target':lab,'index': i} for enc,lab,i in zip(train_encodings, train_data.target.tolist(), train_data.example_index.tolist())]
    print("train_encodings head", train_encodings[:5])

    valid_data.func = valid_data.func.apply(cleaner)
    val_encodings = encode(valid_data.func)
    val_encodings = [{'func':enc.ids,'target':lab,'index': i} for enc,lab,i in zip(val_encodings, valid_data.target.tolist(), valid_data.example_index.tolist())]
    print("val_encodings head", val_encodings[:5])

    train_dataset = TabularDataset_From_List(train_encodings,'dict',fields = fields)
    val_dataset = TabularDataset_From_List(val_encodings,'dict',fields = fields)

    train_df = evaluate_dataset(train_dataset, "train")
    val_df = evaluate_dataset(val_dataset, "val")
    test_df = evaluate_dataset(test_dataset, "test")

    results_df = pd.concat((train_df, val_df, test_df))
    results_df.to_csv(f"results_VulBERTa-CNN_{args.seed_input}.csv")