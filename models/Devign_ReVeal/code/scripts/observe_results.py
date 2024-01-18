#%%
import pandas as pd
import numpy as np
from sklearn.metrics import *

#%%

# concat codebert df
codebert_df = None
for split in ("train", "valid", "test"):
    print(split)
    split_df = pd.read_csv(f"data/subsets/dataset_size/results/balanced_1.0/codebert/predictions{split}.txt", sep="")
    if codebert_df is None:
        codebert_df = split_df
    else:
        codebert_df = pd.concat((codebert_df, split_df))

# convert "id" to "dataset"/"example_index"
codebert_df["id"] = codebert_df["id"].astype(int)
codebert_df["dataset"] = codebert_df.apply(lambda row: "MSR" if row["id"] >= 1e6 else "Devign", axis=1)
codebert_df["example_index"] = codebert_df["id"].apply(lambda i: i - 1e6 if i >= 1e6 else i).astype(int)
codebert_df

print("overall performance")
for score in (accuracy_score, f1_score, precision_score, recall_score):
    print(score.__name__, score(codebert_df["target"], codebert_df["pred"]))

#%%
from getset_root import combined_df

#%%
merge_df = pd.merge(codebert_df, combined_df, on=["dataset", "example_index"], suffixes=("_codebert", "_original"), how="left")
print(np.average(merge_df["target_codebert"] == merge_df["target_original"]))
merge_df

#%%
balanced_df = pd.read_csv("data/subsets/dataset_size/balanced_1.0.csv", index_col=0)
merge_df2 = pd.merge(balanced_df, combined_df, on=["dataset", "example_index"], suffixes=("_balanced", "_original"), how="left")
assert np.all(merge_df2["project_balanced"] == merge_df2["project_original"])
assert np.all(merge_df2["commit_id_balanced"] == merge_df2["commit_id_original"])
