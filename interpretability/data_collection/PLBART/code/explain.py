import re
import sys
import pickle
import argparse
import math


import torch
import numpy as np
from tqdm import tqdm
from sklearn.metrics import classification_report
from fairseq.data import data_utils
from fairseq.models.bart import BARTModel
import transformers


from absl import app
from absl import flags
from absl import logging
from lit_nlp import dev_server
from lit_nlp import server_flags
from lit_nlp.api import model as lit_model
from lit_nlp.api import types as lit_types
from lit_nlp.lib import utils


# https://github.com/pytorch/fairseq/blob/108f7204f6ccddb676e6d52006da219ce96a02dc/fairseq/models/bart/hub_interface.py#L33
def encode(model, sentence, max_positions=512):
    tokens = sentence
    if len(tokens.split(" ")) > max_positions - 2:
        tokens = " ".join(tokens.split(" ")[: max_positions - 2])
    bpe_sentence = "<s> " + tokens + " </s>"
    tokens = model.task.source_dictionary.encode_line(
        bpe_sentence, add_if_not_exist=False, append_eos=False
    )
    return tokens.long()


# def model()

class CodebertModel(lit_model.Model):
    def __init__(self, args):
        self.LABELS = [0, 1]
        self.bart = BARTModel.from_pretrained(
            args.model_dir,
            checkpoint_file=args.model_name,
            data_name_or_path=args.data_bin_path,
            user_dir=args.user_dir,
            task="plbart_sentence_prediction",
        )
    
    def predict_minibatch(self, inputs):
        self.bart.eval()
        batch_input = []
        for input in  inputs:
            tokens = encode(self.bart, input['sentence'])
            batch_input.append(tokens)
        with torch.no_grad():
            batch_input = data_utils.collate_tokens(
                batch_input, self.bart.model.encoder.dictionary.pad(), left_pad=False
            )
            prediction = self.bart.predict(args.classification_head_name, batch_input)
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
    

from lit_nlp.components import lime_explainer


def main(args):
    with open(args.input_file) as inpf, open(args.label_file) as labelf, open(args.output, 'w') as outp:
        inputs = inpf.readlines()
        print(len(inputs))

        lime = lime_explainer.LIME()
        model = CodebertModel(args)
        results = []
        cnt =0
        for input in inputs:
            try:
                data = {
                    'sentence': input
                }
                lime_result = lime.run([data], model)
                results.append(lime_result)
                cnt += 1
                print(cnt)
            except Exception as e:
                print(input)
        pickle.dump(results, open('explanation_devign.pkl', 'wb'))

class Args:
    def __init__(self):
        self.base_dir = '<ANONYMOUS>/<ANONYMOUS>/PLBART/'
        self.model_dir = '<ANONYMOUS>/<ANONYMOUS>/saved_models/PLBART/devign/'
        self.user_dir = self.base_dir + 'source/'
        self.model_name = 'checkpoint_best.pt'
        self.data_path='<ANONYMOUS>/<ANONYMOUS>/data/PLBART/devign/processed/'
        self.data_bin_path = self.data_path + 'data-bin'
        self.input_file = self.data_path + 'test.input0'
        self.label_file = self.data_path + 'test.label'
        self.batch_size = 1
        self.max_example = -1
        self.output = self.base_dir + 'result.txt'
        self.classification_head_name = 'sentence_classification_head'


if __name__ == '__main__':
    args = Args()
    main(args)
