# %%
import pandas as pd
import numpy as np

#%% get msr dataset
msr_df = pd.read_csv("data/MSR/MSR_data_cleaned.csv", index_col=0)
msr_orig = msr_df.copy()
nv = msr_df[msr_df["vul"] == 0]
assert np.all(nv["func_before"] == nv["func_after"])

# msr_df["patch_index"] = msr_df.index
# msr_df["version"] = msr_df.apply(lambda row: ["before", "after"] if row["vul"] == 1 else "after", axis=1)
# msr_df = msr_df.explode("version")
# msr_df["target"] = msr_df["version"].apply(lambda t: 1 if t == "before" else 0)
# msr_df["func"] = msr_df.apply(lambda row: row["func_before"] if row["target"] == 1 else row["func_after"], axis=1)
msr_df["dataset"] = "MSR"
# msr_df["example_index"] = msr_df.reset_index().index
msr_df["example_index"] = msr_df.index
msr_df["target"] = msr_df["vul"]
msr_df

#%% export MSR map
# map_df = msr_df.copy()
# map_df["version"] = map_df["target"].apply(lambda t: "before" if t == 1 else "after")
# map_df = map_df[["example_index", "patch_index", "version", "vul"]]
# map_df.to_csv("data/subsets/msr_map.csv")
# map_df

#%% get devign dataset
devign_df = pd.read_json("data/devign/function.json")
devign_df["dataset"] = "Devign"
devign_df["example_index"] = devign_df.index
devign_df

#%% get combined dataset
combined_df = pd.concat((msr_df, devign_df), ignore_index=True)
duplicated = (
    combined_df[combined_df["project"].isin(["FFmpeg", "qemu"])]
        .drop_duplicates(subset=["commit_id", "dataset"])
        .sort_values(["commit_id", "dataset"])
        .duplicated(subset=["commit_id"], keep="first")
    )
print(np.sum(duplicated), "deduplicated between Devign and MSR")
combined_df = combined_df.drop(duplicated[duplicated == True].index).reset_index(drop=True)

# #%% print target counts (outdated, uses "after" version of code)
# target_df = combined_df
# def get_target(row):
#     if row["dataset"] == "MSR":
#         return [1, 0] if row["vul"] == 1 else [0]
#     else:
#         return row["target"]
# target_df["target"] = target_df.apply(get_target, axis=1)
# target_df = target_df.explode("target")
# print("imbalanced:")
# print(target_df.value_counts("target", normalize=True))
# print("balanced:")
# print(target_df[(target_df["dataset"] == "Devign") | (target_df["vul"] == 1)].value_counts("target", normalize=True))
