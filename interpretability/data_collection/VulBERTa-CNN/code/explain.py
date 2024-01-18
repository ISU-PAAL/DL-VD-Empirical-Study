import pandas as pd
import jsonlines
import tqdm
import re
import pickle
import argparse
import os

from vulberta_cnn_explainer import VulbertaCNNModel, Arg
from lit_nlp.components import lime_explainer

BASE_DIR = '<ANONYMOUS>/<ANONYMOUS>/'

def main(arg):
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

    args = Arg()
    args.output_dir= os.path.join('<ANONYMOUS>/<ANONYMOUS>/saved_models/vulberta/cnn/devign/')
    model= VulbertaCNNModel(args)
    model.enable_gpu()
    model.load_model()

    funs = []
    for i, sample in enumerate(test_data.func.values):
        data = model.tokenizer.encode(sample)
        st = model.tokenizer.decode(data.ids, skip_special_tokens=True)
        x = st.index("<s>")
        y = st.index("</s>")
        st = st[x + 4: y]
        cnt = st.count("<unk>")
        while cnt:
            cnt -= 1
            st = st.replace("<unk>", "")
        st = ' '.join(st.split())
        funs.append(st)
    test_data['func']=funs


    lime = lime_explainer.LIME()

    results = []
    for _, sample in test_data.iterrows():
        try:
            data = [{
                'sentence': sample['func']
            }]
            lime_result = lime.run(data, model, data)[0]
            lime_result['idx'] = sample['idx']
            results.append(lime_result)
            print(" Done with {} samples.".format(len(results)))
            # if len(results) == 5:
            #     break
        except Exception as e:
            print(e)
    pickle.dump(results, open("explanation_cnn_test.pkl", "wb"))
    pickle.dump(results, open("./results/explanation_cnn_test.pkl", "wb"))
    print("written")




if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--dataset', type=str, required=True, help='Name of the dataset for experiment.')
    arg = parser.parse_args()

    main(arg)