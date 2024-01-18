"""
Split "devign-line_ggnn.jsonlines" into train/valid/test sets with an optional 4th holdout set.

Previous output:

(Devign38) <ANONYMOUS>@AM:~/code/ReVeal$ python split_data_original.py --hold_out 10
data/line_ggnn/devign-line_ggnn.jsonlines data/line_ggnn/devign/ 10
Reading data: 26733it [01:12, 369.45it/s]
Finish Reading data, #examples 26733
100%|███████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████| 26733/26733 [00:00<00:00, 859106.84it/s]
Read data: Buggy 12198 Non Buggy 14535
Holding out examples: 1219 1453
data/line_ggnn/devign/holdout_GGNNinput.json: 2672: 100%|████████████████████████████████████████████████████████████████████████████| 2672/2672 [00:09<00:00, 279.62it/s]
Final counts: Buggy 10979 Non Buggy 13082
splitting with seed 1
data/line_ggnn/devign/v1/train_GGNNinput.jsonlines: 16842: 100%|███████████████████████████████████████████████████████████████████| 16842/16842 [01:37<00:00, 173.10it/s]
data/line_ggnn/devign/v1/valid_GGNNinput.jsonlines: 2405: 100%|██████████████████████████████████████████████████████████████████████| 2405/2405 [00:09<00:00, 250.22it/s]
data/line_ggnn/devign/v1/test_GGNNinput.jsonlines: 4814: 100%|███████████████████████████████████████████████████████████████████████| 4814/4814 [00:17<00:00, 278.15it/s]
splitting with seed 2
data/line_ggnn/devign/v2/train_GGNNinput.jsonlines: 16842: 100%|███████████████████████████████████████████████████████████████████| 16842/16842 [01:04<00:00, 260.74it/s]
data/line_ggnn/devign/v2/valid_GGNNinput.jsonlines: 2405: 100%|██████████████████████████████████████████████████████████████████████| 2405/2405 [00:10<00:00, 238.34it/s]
data/line_ggnn/devign/v2/test_GGNNinput.jsonlines: 4814: 100%|███████████████████████████████████████████████████████████████████████| 4814/4814 [00:24<00:00, 195.93it/s]
splitting with seed 3
data/line_ggnn/devign/v3/train_GGNNinput.jsonlines: 16842: 100%|███████████████████████████████████████████████████████████████████| 16842/16842 [01:29<00:00, 188.67it/s]
data/line_ggnn/devign/v3/valid_GGNNinput.jsonlines: 2405: 100%|███████████████████████████████████████████████████████| 2405/2405 [00:09<00:00, 265.53it/s]
data/line_ggnn/devign/v3/test_GGNNinput.jsonlines: 4814: 100%|████████████████████████████████████████████████████████| 4814/4814 [00:18<00:00, 253.59it/s]
splitting with seed 4
data/line_ggnn/devign/v4/train_GGNNinput.jsonlines: 16842: 100%|███████████████████████████████████████████████████████████████████| 16842/16842 [01:09<00:00, 243.91it/s]
data/line_ggnn/devign/v4/valid_GGNNinput.jsonlines: 2405: 100%|██████████████████████████████████████████████████████████████████████| 2405/2405 [00:10<00:00, 236.16it/s]
data/line_ggnn/devign/v4/test_GGNNinput.jsonlines: 4814: 100%|███████████████████████████████████████████████████████████████████████| 4814/4814 [00:41<00:00, 116.96it/s]
splitting with seed 5
data/line_ggnn/devign/v5/train_GGNNinput.jsonlines: 16842: 100%|███████████████████████████████████████████████████████████████████| 16842/16842 [01:53<00:00, 148.69it/s]
data/line_ggnn/devign/v5/valid_GGNNinput.jsonlines: 2405: 100%|██████████████████████████████████████████████████████████████████████| 2405/2405 [00:08<00:00, 278.11it/s]
data/line_ggnn/devign/v5/test_GGNNinput.jsonlines: 4814: 100%|███████████████████████████████████████████████████████████████████████| 4814/4814 [00:18<00:00, 262.36it/s]
"""

import argparse, os
import jsonlines
import numpy as np
from tqdm import tqdm
import pandas as pd


def split_and_save(output_dir, buggy, non_buggy, seed):
    print("splitting with seed", seed)
    random_state = np.random.RandomState(seed=seed)
    random_state.shuffle(buggy)
    random_state.shuffle(non_buggy)

    train_examples = []
    valid_examples = []
    test_examples = []

    num_bug = len(buggy)
    num_train_bugs = int(num_bug * 0.70)
    num_valid_bug = int(num_bug * 0.10)
    train_examples.extend(buggy[:num_train_bugs])
    valid_examples.extend(buggy[num_train_bugs:(num_train_bugs + num_valid_bug)])
    test_examples.extend(buggy[(num_train_bugs + num_valid_bug):])

    num_non_bug = len(non_buggy)
    num_train_nobugs = int(num_non_bug * 0.70)
    num_valid_nobug = int(num_non_bug * 0.10)
    train_examples.extend(non_buggy[:num_train_nobugs])
    valid_examples.extend(non_buggy[num_train_nobugs:(num_train_nobugs + num_valid_nobug)])
    test_examples.extend(non_buggy[(num_train_nobugs + num_valid_nobug):])

    train_df = pd.DataFrame(train_examples, columns=["index"])
    valid_df = pd.DataFrame(valid_examples, columns=["index"])
    test_df = pd.DataFrame(test_examples, columns=["index"])
    train_df["split"] = "train"
    valid_df["split"] = "valid"
    test_df["split"] = "test"
    df = pd.concat((train_df, valid_df, test_df), ignore_index=True)
    df.to_csv(os.path.join(output_dir, "splits.csv"))


if __name__ == '__main__':
    datasets = ['devign']
    for dataset_name in datasets:
        # for p in parts:
            data_dir = 'data/line_ggnn/'
            # NOTE: Use jq -c .[] devign-line_ggnn.json > devign-line_ggnn.jsonlines to convert json to jsonlines
            input_path = data_dir + dataset_name + '-line_ggnn.jsonlines'
            output_path = data_dir + dataset_name + '/'
            parser = argparse.ArgumentParser()
            parser.add_argument('--input', help='Path of the input file', default=input_path)
            parser.add_argument('--output', help='Output Directory', default=output_path)
            parser.add_argument('--repeat_count', help='Number of times to be repeated', default=5, type=int)
            parser.add_argument('--hold_out', help='Hold out extra percentage of data', default=None, type=int)
            args = parser.parse_args()
            assert args.hold_out is None or (0 <= args.hold_out <= 100)
            print(args.input, args.output, args.hold_out)

            # Load data
            input_data = []
            with jsonlines.open(args.input) as reader:
                for obj in tqdm(reader, desc="Reading data"):
                    input_data.append(obj)
            print('Finish Reading data, #examples', len(input_data))
            buggy = []
            non_buggy = []
            for i, example in enumerate(tqdm(input_data)):
                target = example['targets'][0][0]
                if target == 1:
                    buggy.append(i)
                else:
                    non_buggy.append(i)
            print('Read data:', 'Buggy', len(buggy), 'Non Buggy', len(non_buggy))
            if not os.path.exists(args.output):
                os.mkdir(args.output)
            
            # Shuffle
            random_state = np.random.RandomState(seed=0)
            random_state.shuffle(buggy)
            random_state.shuffle(non_buggy)

            # Split up rest of dataset
            print('Final counts:', 'Buggy', len(buggy), 'Non Buggy', len(non_buggy))
            for r in range(1, args.repeat_count + 1):
                output_dir = os.path.join(args.output, 'v' + str(r))
                if not os.path.exists(output_dir):
                    os.mkdir(output_dir)
                split_and_save(output_dir, buggy, non_buggy, r)
