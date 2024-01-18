
"""
THIS IS THE NEW CORRECT SCRIPT FOR GENERATING splits.csv AND map.csv
"""

#%% generate map.csv
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
map_df.to_csv("data/devign/full_experiment_real_data_processed/vcodexglue/map.csv")

#%%
map_df = pd.read_csv("data/devign/full_experiment_real_data_processed/vcodexglue/map.csv", index_col=0)

#%%
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

#%%
split_csv_df = pd.merge(map_df, split_df, left_on="codexglue_example_index", right_on="example_index")
split_csv_df = split_csv_df[["training_example_index", "split"]].rename(columns={"training_example_index": "example_index"})
split_csv_df.to_csv("data/devign/full_experiment_real_data_processed/vcodexglue/splits.csv")
split_csv_df
