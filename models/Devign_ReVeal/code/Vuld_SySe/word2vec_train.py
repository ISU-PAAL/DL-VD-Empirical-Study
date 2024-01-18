import argparse
from tabnanny import verbose
from gensim.models import Word2Vec
import json
import os
import glob

import pandas as pd
import logging
logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.DEBUG)

data_dir = "data/MSR"
csv_name = "MSR_data_cleaned.csv"

def train(args):
    files = args.data_paths
    sentences = []
    for f in files:
        if f.endswith(".csv"):
            df = pd.read_csv(f, index_col=0)
            df["version"] = df["vul"].apply(lambda v: ["before", "after"] if v == 1 else ["before"])
            df = df.explode("version")
            print(len(df), "examples")
            print(df)
            for i, row in df.iterrows():
                code = row[f"func_" + row['version']]
                sentences.append([token.strip() for token in code.split()])
        elif f.endswith(".json"):
            with open(f) as inf:
                datas = json.load(inf)
            for d in datas:
                code = d.get("func")
                sentences.append([token.strip() for token in code.split()])
    print(len(sentences), "sentences")
    wvmodel = Word2Vec(sentences, workers=8, vector_size=100, window=10, epochs=100)
    print('Embedding Size : ', wvmodel.vector_size)
    wvmodel.train(sentences, total_examples=len(sentences), epochs=wvmodel.epochs)
    if not os.path.exists(args.save_model_dir):
        os.mkdir(args.save_model_dir)
    save_file_path = os.path.join(args.save_model_dir, args.model_name)
    wvmodel.save(save_file_path)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--data_paths', type=str, nargs='+', default=[f'{data_dir}/{csv_name}'])
    parser.add_argument('--min_occ', type=int, default=1)
    parser.add_argument('-bin', '--save_model_dir', type=str, default=f'{data_dir}/wv_models')
    parser.add_argument('-n', '--model_name', type=str, default='raw_code.100')
    args = parser.parse_args()
    train(args)