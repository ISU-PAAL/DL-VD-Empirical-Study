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
from pathlib import Path
import pandas as pd
import random
import re
import os
import time
import torch
import torch.nn as nn
import torch.nn.functional as F
import torchtext
import torchtext.vocab as vocab
import sklearn.metrics
from transformers import RobertaModel
from transformers import RobertaConfig
from sklearn.metrics import confusion_matrix
from sklearn.utils.class_weight import compute_class_weight
from torch.autograd import Variable
from torch import nn, optim
from torch.optim import SGD,Adam,RMSprop
from torch.utils.data import Dataset, DataLoader, IterableDataset
from clang import *


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
parser.add_argument("--dataset", default=None, type=str, required=True,
                    help="dataset")
parser.add_argument("--batch", default=4, type=int, required=False,
                    help="The input training data file (a text file).")
parser.add_argument("--epochs", default=20, type=int, required=False,
                    help="The input training data file (a text file).")
parser.add_argument("--generate_json", default=None, type=bool, required=True,
                    help="determines whether to generate jsons or simply read them from previous run")                    

args = parser.parse_args()

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


device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
multigpu = False
if device == torch.device('cuda'):
	multigpu = torch.cuda.device_count() > 1
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


# ### PREPARE DATA

# In[6]:


TEST_ONLY = False


# In[7]:


mydataset = args.dataset


# In[8]:


my_tokenizer.enable_truncation(max_length=1024)
my_tokenizer.enable_padding(direction='right', pad_id=1, pad_type_id=0, pad_token='<pad>', length=None, pad_to_multiple_of=None)


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

if mydataset =='devign':
    if TEST_ONLY:
        
        test_index=set()
        with open('data/finetune/devign/test.txt') as f:
            for line in f:
                line=line.strip()
                test_index.add(int(line))
        mydata = pd.read_json('data/finetune/devign/Devign.json')
        m3=mydata.iloc[list(test_index)]
        mydata = None
        del(mydata)
        
    else:
        train_index=set()
        valid_index=set()
        test_index=set()

        with open('data/finetune/devign/train.txt') as f:
            for line in f:
                line=line.strip()
                train_index.add(int(line))

        with open('data/finetune/devign/valid.txt') as f:
            for line in f:
                line=line.strip()
                valid_index.add(int(line))

        with open('data/finetune/devign/test.txt') as f:
            for line in f:
                line=line.strip()
                test_index.add(int(line))

        mydata = pd.read_json('data/finetune/devign/Devign.json')
        m1=mydata.iloc[list(train_index)]
        m2=mydata.iloc[list(valid_index)]
        m3=mydata.iloc[list(test_index)]

        mydata = None
        del(mydata)

elif mydataset == 'combined':

    #print('data/finetune/combined/' + args.data_folder + '/train.jsonl')
    
    file_loc = 'data/finetune/combined/' + args.data_folder + '/train.jsonl'
    print(file_loc)
    m1 = pd.read_json(file_loc, lines=True)

    file_loc = 'data/finetune/combined/' + args.data_folder + '/valid.jsonl'
    print(file_loc)
    m2 = pd.read_json(file_loc, lines=True)





if mydataset == 'msr':
    pass


else:
    if TEST_ONLY:
        m3.func = m3.func.apply(cleaner)
        test_encodings = my_tokenizer.encode_batch(m3.func)
        try:
            test_encodings = [{'func':enc.ids,'target':lab} for enc,lab in zip(test_encodings,m3.target.tolist())]
        except:
            test_encodings = [{'func':enc.ids,'target':lab} for enc,lab in zip(test_encodings,(m3['combine']*1).tolist())]

    else:

        m1.func = m1.func.apply(cleaner)
        train_encodings = my_tokenizer.encode_batch(m1.func)
        try:
            train_encodings = [{'func':enc.ids,'target':lab} for enc,lab in zip(train_encodings,m1.target.tolist())]
        except:
            train_encodings = [{'func':enc.ids,'target':lab} for enc,lab in zip(train_encodings,(m1['combine']*1).tolist())]


        m2.func = m2.func.apply(cleaner)
        val_encodings = my_tokenizer.encode_batch(m2.func)
        try:
            val_encodings = [{'func':enc.ids,'target':lab} for enc,lab in zip(val_encodings,m2.target.tolist())]
        except:
            val_encodings = [{'func':enc.ids,'target':lab} for enc,lab in zip(val_encodings,(m2['combine']*1).tolist())]





# In[12]:


CODES = torchtext.data.Field(batch_first=True, fix_length=1024,use_vocab=False)
LABEL = torchtext.data.LabelField(dtype=torch.long, is_target=True,use_vocab=False)
fields = {'func': ('codes', CODES), 'target': ('label', LABEL)}

class TabularDataset_From_List(torchtext.data.Dataset):
    def __init__(self, input_list, format, fields, skip_header=False, **kwargs):
        make_example = {
            'json': torchtext.data.Example.fromJSON, 'dict': torchtext.data.Example.fromdict}[format.lower()]

        examples = [make_example(item, fields) for item in input_list]

        if make_example in (torchtext.data.Example.fromdict, torchtext.data.Example.fromJSON):
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



if TEST_ONLY:
    test_data = TabularDataset_From_List(test_encodings,'dict',fields = fields)
else:
    train_data = TabularDataset_From_List(train_encodings,'dict',fields = fields)
    val_data = TabularDataset_From_List(val_encodings,'dict',fields = fields)
    # test_data = TabularDataset_From_List(test_encodings,'dict',fields = fields)
    # holdout_data = TabularDataset_From_List(holdout_encodings, 'dict', fields=fields)
    print('')



MAX_VOCAB_SIZE = VOCAB_SIZE

# place into iterators


if TEST_ONLY:
    test_iterator = torchtext.data.BucketIterator(
        test_data, 
        batch_size = 1,
        sort = False,
        shuffle = False)
    
else:
    # train_iterator, valid_iterator, test_iterator, holdout_iterator = torchtext.data.BucketIterator.splits(
    #     (train_data, val_data, test_data, holdout_data),
    #     batch_size = BATCH_SIZE,
    #     sort = False,
    #     shuffle = False)
    train_iterator, valid_iterator = torchtext.data.BucketIterator.splits(
        (train_data, val_data),
        batch_size = BATCH_SIZE,
        sort = False,
        shuffle = False)

UNK_IDX = 3
PAD_IDX = 1

# test_iterator = torchtext.data.BucketIterator(
#     test_data, 
#     batch_size = BATCH_SIZE,
#     sort = False,
#     shuffle = False)

#from torch.utils.data import DataLoader

# train_dataloader = DataLoader(train_dataset, shuffle=False, batch_size=BATCH_SIZE)
# val_dataloader = DataLoader(val_dataset, shuffle=False, batch_size=BATCH_SIZE)
# test_dataloader = DataLoader(test_dataset, shuffle=False, batch_size=BATCH_SIZE)


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

try:
    y_ = []
    for i in range(0, len(train_data)):
        y_.append(train_data[i].label)
    cw = sklearn.utils.class_weight.compute_class_weight(class_weight='balanced',classes=[0,1],y=y_)
except:
    y_ = []
    for i in range(0, len(train_data)):
        y_.append(train_data[i].label)
    cw = sklearn.utils.class_weight.compute_class_weight(class_weight='balanced',classes=[0,1],y=y_)
    
c_weights = torch.FloatTensor([cw[0], cw[1]])
criterion = nn.CrossEntropyLoss(weight=c_weights)
criterion = criterion.to(device)

optimizer = Adam(model.parameters(), lr=0.0005)


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


try:
    model_foldername = 'VB-CNN_%s'%(mydataset) + args.data_folder
except FileExistsError:
    print('Folder exists')


# In[26]:


print('Training started.....')

EPOCHS=10
BEST_VAL = 9999.9
BEST_MODEL = None
BEST_EPOCH = None

for e in range(EPOCHS):
    running_acc = 0
    running_loss = 0
    timer = time.time()
    model.train()

    for batch in train_iterator:
        batch.codes, batch.label = batch.codes.to(device), batch.label.to(device)
        optimizer.zero_grad()
        output = model(batch.codes)
        loss = criterion(output, batch.label)
        loss.backward()
        optimizer.step()
        acc,pred, predictions = softmax_accuracy(output,batch.label)
        running_acc += acc
        running_loss += loss.item()

    with torch.no_grad():
        model.eval()
        running_acc_val = 0
        running_loss_val = 0
        for batch in valid_iterator:
            batch.codes, batch.label = batch.codes.to(device), batch.label.to(device)
            output_val = model(batch.codes)
            loss_val = criterion(output_val,batch.label)
            acc_val,pred, predictions = softmax_accuracy(output_val,batch.label)
            running_acc_val += acc_val
            running_loss_val += loss_val.item()

    print_out = "Epoch %d - Training acc: %.4f -Training loss: %.4f - Val acc: %.4f - Val loss: %.4f - Time: %.4fs \n" % (e+1,
    running_acc/len(train_iterator),
    running_loss/len(train_iterator),
    running_acc_val/len(valid_iterator),
    running_loss_val/len(valid_iterator),
    (time.time()-timer))
    
    
    selected_model = False
    
    if selected_model:
        
        myfile = open("res.txt", "a")

        if (running_loss_val/len(valid_iterator)) < BEST_VAL:
            print('Val_loss decreased!')
            print(print_out, end='')
            myfile.write('Val_loss decreased!')
            myfile.write(print_out)

            BEST_VAL = (running_loss_val/len(valid_iterator))
            BEST_MODEL = copy.deepcopy(model)
            BEST_EPOCH = e+1
            model_name = 'models/%s/model_ep_%d.tar' % (model_foldername,e+1)
            torch.save({
                'epoch': e+1,
                'model_state_dict': model.state_dict(),
                'optimizer_state_dict': optimizer.state_dict(),
                'loss': loss}, model_name)

        else:
            print(print_out, end='')
            myfile.write(print_out)

        myfile.close()
        
    else:
        print(print_out, end='')
        #"models/VB-MLP_%s" % mydataset + str(args.seed_input)
        model_name = 'models/%s/model_ep_%d.tar' % (args.save_folder,e+1)
        try:
            os.mkdir('models/' + args.save_folder)
        except:
            pass
        torch.save({
            'epoch': e+1,
            'model_state_dict': model.state_dict(),
            'optimizer_state_dict': optimizer.state_dict(),
            'loss': loss}, model_name)

        

print('Training completed!')

