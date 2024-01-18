"""
ORIGINALLY USED TO ALIGN THE SPLITS FROM CODEXGLUE TO DEVIGN PREPROCESSED DATA.
SEEMS TO WORK FINE BUT THE FILES ARE INCORRECT SOMEHOW AT THE TIME OF WRITING, SO USE generate_splits_csv.py instead
"""

#%%
from pathlib import Path
import json
import re
from cv2 import merge
import pandas as pd
import numpy as np

code_file = Path("data/ggnn_input/devign_cfg_full_text_files.json")
with open(code_file) as f:
    code_data = json.load(f)
code_df = pd.DataFrame(code_data)
code_df["id"], code_df["project"], code_df["commit_id"], _ = zip(*code_df["file_name"].apply(lambda s: s.split("_")))
code_df["my_unique_id"] = code_df.apply(lambda row: row["project"] + "_" + row["commit_id"] + "_" + " ".join(row["code"].split()), axis=1)
code_df
#%%
function_file = Path("data/CodeXGLUE-main/Code-Code/Defect-detection/dataset/function.json")
with open(function_file) as f:
    function_data = json.load(f)
function_df = pd.DataFrame(function_data)
function_df["my_unique_id"] = function_df.apply(lambda row: row["project"] + "_" + row["commit_id"] + "_" + " ".join(row["func"].split()), axis=1)
function_df = function_df.reset_index().rename(columns={"index":"function_id"})
function_df
#%%
merge_df = pd.merge(code_df, function_df, on="my_unique_id", how="inner")
merge_df
# %%
assert not any(merge_df["function_id"].isna())
assert np.all(code_df.index == merge_df.index)

#%%
from pathlib import Path
splits = {}
splitss = {}
for file in Path("data/CodeXGLUE-main/Code-Code/Defect-detection/dataset").glob("*.txt"):
    with open(file) as f:
        ids = list(map(int, f.read().split()))
        for _id in ids:
            splits[_id] = file.stem
        splitss[file.stem] = ids
splits
# %%
merge_df["split"] = merge_df["function_id"].apply(lambda i: splits[int(i)])
merge_df["index"] = merge_df.index
split_df = merge_df[["index", "split"]]
split_df.to_csv(Path("data/line_ggnn/devign/vcodexglue/splits.csv"))
split_df

#%%
map_df = merge_df.rename(columns={"function_id": "codexglue_index"})[["index", "codexglue_index"]]
map_df.to_csv(Path("data/line_ggnn/devign/vcodexglue/map.csv"))
map_df