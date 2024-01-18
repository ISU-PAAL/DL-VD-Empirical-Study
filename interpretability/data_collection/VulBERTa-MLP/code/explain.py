
from doctest import Example
import json
import re
import attr
import pandas as pd
import argparse

import jsonlines
import tqdm
import re
import pickle
import argparse
import os

from vulberta_mlp_explainer import VulbertaModel, Arg
from lit_nlp.components import gradient_maps


BASE_DIR = '<ANONYMOUS>/<ANONYMOUS>/'
def main(arg):
    args = Arg()
    print(args)
    model = VulbertaModel(args)
    model.activate_evaluation()

    def read_jsonl(filename):
        with jsonlines.open(filename) as reader:
            data = list(tqdm.tqdm(reader, desc="read file"))
        mydata = pd.DataFrame(data)
        return mydata
    test_data = read_jsonl(os.path.join(BASE_DIR,'data', arg.dataset, 'test.jsonl'))
    test_data.target = test_data.target.astype(int)

    def cleaner(code):
        ## Remove code comments
        pat = re.compile(r'(/\*([^*]|(\*+[^*/]))*\*+/)|(//.*)')
        code = re.sub(pat,'',code)
        code = re.sub('\n','',code)
        code = re.sub('\t','',code)
        return(code)
    test_data.func = test_data.func.apply(cleaner)

    def get_top(df):
        examples = []
        for _, row in df.iterrows():
            examples.append({
                'sentence': row['func'],
                'label': row['target']
            })
        return examples
    inputs = get_top(test_data)

    ig = gradient_maps.IntegratedGradients()
    print("Input Data size: ", len(inputs))
    ig_results = []
    for i in range(0, len(inputs), 128):
        ig_results += ig.run(inputs[i : i + 128], model, inputs)
        print("Finished from {} to {}, result length {}".format(i, i + 128, len(ig_results)))
        print("Finished ", len(ig_results))
    pickle.dump(ig_results,open('explanation_devign_mlp_test.pkl', 'wb'))
    pickle.dump(ig_results,open('./results/explanation_devign_mlp_test.pkl', 'wb'))
    print("Explanation Done for {}".format(len(ig_results)))
    print("Done")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--dataset', type=str, required=True, help='Name of the dataset for experiment.')
    arg = parser.parse_args()

    main(arg)