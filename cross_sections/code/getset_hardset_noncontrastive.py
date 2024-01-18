# %%
# RQ.B1
# Shuffle Devign and MSR together.
# export progressively larger subsets of the dataset.
import pandas as pd
import numpy as np
from getset_root import combined_df, devign_df, msr_df

#%% get combined dataset
devign_msr_vul = combined_df[(combined_df["dataset"] == "Devign") | ((combined_df["dataset"] == "MSR") & (combined_df["target"] == 1))]
msr_vul = devign_msr_vul[(devign_msr_vul["dataset"] == "MSR") & (devign_msr_vul["target"] == 1)]

msr_nonvul = combined_df[(combined_df["dataset"] == "MSR") & (combined_df["target"] == 0)]
rs = np.random.RandomState(seed=0)
msr_nonvul = msr_nonvul.sample(n=len(msr_vul), random_state=rs)

result_df = pd.concat((devign_msr_vul, msr_nonvul)).rename(columns={"example_index": "idx"})
result_df = result_df.assign(func=result_df.apply(lambda row: row["func"] if row["dataset"] == "Devign" else row["func_before"], axis=1))
result_df = result_df[["dataset", "idx", "project", "commit_id", "target", "func"]]
result_df.value_counts(["dataset", "target"])

#%% check with original df
merge_df = pd.merge(result_df[(result_df["dataset"] == "Devign")], devign_df, how="left", left_on="idx", right_on="example_index", suffixes=("", "_orig"))
assert np.all(merge_df["target"] == merge_df["target_orig"])
assert np.all(merge_df["func"] == merge_df["func_orig"])

merge_df = pd.merge(result_df[(result_df["dataset"] == "MSR") & (result_df["target"] == 1)], msr_df, how="left", left_on="idx", right_on="example_index", suffixes=("", "_orig"))
assert np.all(merge_df["target"] == merge_df["target_orig"])
assert np.all(merge_df["func"] == merge_df["func_before"])

merge_df = pd.merge(result_df[(result_df["dataset"] == "MSR") & (result_df["target"] == 0)], msr_df, how="left", left_on="idx", right_on="example_index", suffixes=("", "_orig"))
assert np.all(merge_df["target"] == merge_df["target_orig"])
assert np.all(merge_df["func"] == merge_df["func_before"])

#%% check with balanced
balanced_df = pd.read_csv("data/subsets/dataset_size/balanced_1.0.csv")
merge_df = pd.merge(result_df[(result_df["dataset"] == "Devign") | (result_df["target"] == 1)], balanced_df, how="left", left_on=["dataset", "idx"], right_on=["dataset", "example_index"], suffixes=("", "_balanced"))
assert np.all(merge_df["target"] == merge_df["target_balanced"])
assert np.all(merge_df["project"] == merge_df["project_balanced"])
assert np.all(merge_df["commit_id"] == merge_df["commit_id_balanced"])

#%%
split_dfs = []
for split in ("train", "valid", "test"):
    split_fname = f"data/CodeXGLUE-main/Code-Code/Defect-detection/dataset/{split}.txt"
    with open(split_fname) as f:
        indices = f.readlines()
    codexglue_indices = [int(i) for i in indices]
    split_df = pd.DataFrame(codexglue_indices, columns=["idx"])
    split_df["split"] = split
    split_dfs.append(split_df)
split_df = pd.concat(split_dfs, ignore_index=True).sort_values("idx")
split_df["dataset"] = "Devign"
split_df

#%%
result_split_df = pd.merge(result_df, split_df, on=["dataset", "idx"], how="left")
assert np.all(result_split_df[result_split_df["dataset"] == "MSR"]["split"].isna())
def split(df):
    rs = np.random.RandomState(seed=0)
    train_end = int(len(df) * 0.9)
    split = pd.Series(range(len(df)), index=rs.permutation(df.index)).apply(lambda i: "train" if i <= train_end else "valid")
    return split
result_split_df_msr = result_split_df[result_split_df["dataset"] == "MSR"].drop(columns=["split"])

result_split_df_msr_vul = result_split_df_msr[result_split_df_msr["target"] == 1]
contrastive_df = pd.read_csv("data/subsets/contrastive/contrastive.csv", usecols=["dataset", "idx", "split", "target"])
contrastive_df = contrastive_df[(contrastive_df["dataset"] == "Devign") | (contrastive_df["target"] == 1)]
result_split_df_msr_vul = pd.merge(result_split_df_msr_vul, contrastive_df, on=["dataset", "idx"], how="inner", suffixes=("", "_contrastive"))
assert np.all(result_split_df_msr_vul["target"] == result_split_df_msr_vul["target_contrastive"])
result_split_df_msr_vul = result_split_df_msr_vul.drop(columns=["target_contrastive"])

result_split_df_msr_nonvul = result_split_df_msr[result_split_df_msr["target"] == 0]
result_split_df_msr_nonvul = result_split_df_msr_nonvul.assign(split=split(result_split_df_msr_nonvul))

result_split_df = pd.concat((result_split_df[result_split_df["dataset"] != "MSR"], result_split_df_msr_vul, result_split_df_msr_nonvul))
assert not np.any(result_split_df[(result_split_df["split"] == "test") & (result_split_df["dataset"] != "Devign")])
assert np.all(result_split_df[result_split_df["split"] == "test"]["idx"].reset_index(drop=True) == split_df[split_df["split"] == "test"]["idx"].reset_index(drop=True))
result_split_df.value_counts("split", dropna=False, normalize=True)

#%%
contrastive_df = pd.read_csv("data/subsets/contrastive/contrastive.csv", index_col=0)
result_intersect = result_split_df[(result_split_df["dataset"] == "Devign") | (result_split_df["target"] == 1)]
contr_intersect = contrastive_df[(contrastive_df["dataset"] == "Devign") | (contrastive_df["target"] == 1)]
merge_df = pd.merge(result_intersect, contr_intersect, on=["dataset", "idx"], how="inner", suffixes=("", "_contrastive"))
assert np.all(merge_df["target"] == merge_df["target_contrastive"])
assert np.all(merge_df["project"] == merge_df["project_contrastive"])
assert np.all(merge_df["commit_id"] == merge_df["commit_id_contrastive"])
assert np.all(merge_df["split"] == merge_df["split_contrastive"])

nonvul_msr_idx = result_split_df[(result_split_df["dataset"] == "MSR") & (result_split_df["target"] == 0)]["idx"]
assert not np.any(contrastive_df[(contrastive_df["dataset"] == "MSR") & (contrastive_df["idx"].isin(nonvul_msr_idx))])

#%% output
output_df = result_split_df.sort_values(["dataset", "idx"]).reset_index(drop=True)
output_df.drop(columns=["func"]).to_csv("data/subsets/noncontrastive/noncontrastive.csv")

for split, group in output_df.groupby("split"):
    group.to_json(f"data/subsets/noncontrastive/{split}.jsonl", orient="records", lines=True)
output_df
