from interactive_predict import SHOW_TOP_CONTEXTS
from common import common
from code2vec import load_model_dynamically
from config import Config
import json
import pandas as pd

config = Config(set_defaults=True, load_from_args=True, verify=True)
model = load_model_dynamically(config)

# To run, use: python prediction_outputter.py --load models/devign/saved_model_iter10.release
# (or whatever checkpoint you want to evaluate).
# Expects the raw files from preprocessing "{dataset}.{split}.raw.txt" in the current directory and "../astminer/dataset/{dataset}/{split}.jsonl".

# NOTE: modify this value to output to a different filename
output_filename = "predictions.csv"

dicti = {
    "safe": 0,
    "vuln": 1
}

datas = []
for dataset in ("msr",):
    for split in ("train", "valid", "test"):
        context_paths = f"{dataset}.{split}.raw.txt"
        json_file = f"../astminer/dataset/{dataset}/{split}.jsonl"
        with open(json_file) as sample_file, open(context_paths) as contexts_file:
            for sample, function in zip(sample_file, contexts_file):
                sample = json.loads(sample.strip())
                parts = function.rstrip().split(' ')
                method_name = parts[0]
                current_result_line_parts = [method_name]
                contexts = parts[1:]

                for context in contexts[:200]:
                    try:
                        context_parts = context.split(',')
                        context_word1 = context_parts[0]
                        context_path = context_parts[1] 
                        context_word2 = context_parts[2]
                    except:
                        breakpoint()
                    current_result_line_parts += ['%s,%s,%s' % (context_word1, context_path, context_word2)]
                space_padding = ' ' * (200 - len(contexts))
                result_line = ' '.join(current_result_line_parts) + space_padding
                raw_prediction_results = model.predict([result_line])
                method_prediction_results = common.parse_prediction_results(
                        raw_prediction_results,
                        model.vocabs.target_vocab.special_words, topk=SHOW_TOP_CONTEXTS)
                for raw_prediction, method_prediction in zip(raw_prediction_results, method_prediction_results):
                    binary_label = dicti[method_prediction.predictions[0]['name'][0]]
                    prob = method_prediction.predictions[0]['probability']
                    prob_positive = prob if binary_label == 1 else 1-prob
                    datas.append({
                        "dataset": dataset,
                        "split": split,
                        "example_index": sample["idx"],
                        "target": sample["target"],
                        # "project": sample["project"],
                        # "commit_id": sample["commit_id"],
                        "code": sample["func"],
                        "prediction": binary_label,
                        "probability": prob_positive,
                    })



print('OUTPUTTING DATA TO CSV FILE OUTPUTTING DATA TO CSV FILE OUTPUTTING DATA TO CSV FILE OUTPUTTING DATA TO CSV FILE OUTPUTTING DATA TO CSV FILE')
df = pd.DataFrame(data=datas)
df.to_csv(output_filename)
