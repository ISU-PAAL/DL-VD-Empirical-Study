"""
USED TO CHECK DEVIGN SPLITS ARE CORRECT (THEY'RE NOT at the time of writing)
"""

#%% generate mapping from jsonl index to codexglue index
import pandas as pd
import jsonlines
import tqdm.auto as tqdm
import itertools

data = {
    "training_example_index": [],
    "codexglue_example_index": [],
}
with jsonlines.open("data/devign/full_experiment_real_data_processed/devign-full_graph.jsonlines") as reader:
    # reader = itertools.islice(reader, 1000)
    for i, example in tqdm.tqdm(enumerate(reader), desc="read jsonl"):
        func_json_idx = int(example["file_name"].split("_")[0])
        data["training_example_index"].append(i)
        data["codexglue_example_index"].append(func_json_idx-1)
map_df = pd.DataFrame(data)

#%% read mapping from codexglue index to splits
split_dfs = []
for split in ("train", "valid", "test"):
    split_fname = f"data/CodeXGLUE-main/Code-Code/Defect-detection/dataset/{split}.txt"
    with open(split_fname) as f:
        indices = f.readlines()
    codexglue_indices = [int(i) for i in indices]
    split_df = pd.DataFrame(codexglue_indices, columns=["example_index"])
    split_df["split"] = split
    split_dfs.append(split_df)
split_df = pd.concat(split_dfs, ignore_index=True).sort_values("example_index")
split_df

#%% generate mapping from jsonl index to splits
split_csv_df = pd.merge(map_df, split_df, left_on="codexglue_example_index", right_on="example_index")
split_csv_df = split_csv_df[["training_example_index", "split"]].rename(columns={"training_example_index": "example_index"})
split_csv_df

#%% read splits.csv to check its correctness
import numpy as np

split_csv_file_df = pd.read_csv("data/devign/full_experiment_real_data_processed/vcodexglue/splits.csv", index_col=0).rename(columns={"index": "example_index"})
merge_df = pd.merge(split_csv_df, split_csv_file_df, on="example_index")
assert np.all(merge_df["split_x"] == merge_df["split_y"])

#%%
import json
with open(f"splits.json") as f:
    splitsi_data = json.load(f)
    splitsi_df = pd.DataFrame(splitsi_data.items(), columns=["example_index", "split"])
    splitsi_df["example_index"] = splitsi_df["example_index"].astype(int)
    merge_df = pd.merge(split_csv_file_df, splitsi_df, on="example_index")
    assert np.all(merge_df["split_x"] == merge_df["split_y"])
    merge_df = pd.merge(split_csv_df, splitsi_df, on="example_index")
    assert np.all(merge_df["split_x"] == merge_df["split_y"])
merge_df
