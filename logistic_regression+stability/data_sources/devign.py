#%%
import json
import numpy as np
import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt

#%%
devign_df = None

splits_df = pd.read_csv("eval_exports/devign_reveal/splits.csv", usecols=["example_index", "split"]).set_index("example_index")
for seed in [1, 2, 3]:
    for model in ["devign"]:
        fname = f"eval_exports/devign_reveal/eval_export_{model}_{seed}.csv"
        
        df = pd.read_csv(fname, usecols=["index", "prediction", "prob", "target"]).set_index("index")
        df = df.sort_index()
        df = df.join(splits_df)
        df["model"] = model
        df["seed"] = seed

        if devign_df is None:
            devign_df = df
        else:
            devign_df = pd.concat((devign_df, df))
devign_df = devign_df.rename_axis('training_example_index').reset_index()

map_df = pd.read_csv("eval_exports/devign_reveal/map.csv", index_col=0)
# map_df["codexglue_example_index"] += 1
devign_df = pd.merge(devign_df, map_df, on="training_example_index").rename(columns={"codexglue_example_index": "example_index"}).sort_values(["example_index", "seed"])

with open("data/devign/function.json") as f:
    od = json.load(f)
code_df = pd.DataFrame(od)
devign_df = pd.merge(devign_df, code_df, how="left", left_on="example_index", right_index=True, suffixes=("", "_code"))
assert np.all(devign_df["target"] == devign_df["target_code"])
devign_df = devign_df.drop(columns=["target_code"])
devign_df = devign_df.rename(columns={"func": "code"})

devign_df

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
merge_df = pd.merge(devign_df, split_df, on="example_index")
merge_df

# %%
