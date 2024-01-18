# %%
# RQ.B1
# Shuffle Devign and MSR together.
# export progressively larger subsets of the dataset.
import pandas as pd
import numpy as np
from getset_root import combined_df

#%% get imbalanced dataset
keepcols = ["dataset", "example_index", "project", "commit_id", "target"]
imbalanced_df = combined_df[keepcols]

from split import split
imbalanced_df["split"] = split(imbalanced_df)
imbalanced_df["split"].value_counts(normalize=True)

print("imbalanced_df")
print(imbalanced_df)
imbalanced_df = imbalanced_df.sort_values(by=list(imbalanced_df.columns)).reset_index(drop=True)

#%% get balanced dataset
imbalanced_msr_df = imbalanced_df[imbalanced_df["dataset"] == "MSR"]
balanced_msr_vul_df = imbalanced_msr_df[imbalanced_msr_df["target"] == 1]
num_vul_msr = len(balanced_msr_vul_df)
rs_balance = np.random.RandomState(seed=0)
balanced_msr_nonvul_df = imbalanced_msr_df[imbalanced_msr_df["target"] == 0].sample(n=num_vul_msr, random_state=rs_balance)
balanced_df = imbalanced_df[
    (imbalanced_df["dataset"] == "Devign") |
    (imbalanced_df.index.isin(balanced_msr_vul_df.index)) |
    (imbalanced_df.index.isin(balanced_msr_nonvul_df.index))
    ]
print("balanced_df")
print(balanced_df)
print(balanced_df.value_counts(["dataset", "target"], normalize=True))
print(balanced_df.value_counts("target", normalize=True))

# %% export csvs of different proportions
# preserve the same test set for all proportions
exportcols = ["dataset", "example_index", "project", "commit_id", "target", "split"]
rs = np.random.RandomState(seed=0)
choice_df = imbalanced_df[imbalanced_df["split"] != "test"].sample(frac=1.0, random_state=rs)
test_df = imbalanced_df[imbalanced_df["split"] == "test"]

fracs = [
    "1.0",
    "0.9",
    "0.8",
    "0.7",
    "0.6",
    "0.5",
    "0.4",
    "0.3",
    "0.2",
    "0.1",
    "0.05",
    "0.01",
]
for frac in fracs:
    proportion = int(float(frac) * len(choice_df))
    frac_df = pd.concat((
        choice_df.iloc[:proportion].sort_index(),
        imbalanced_df[imbalanced_df["split"] == "test"],
        ), ignore_index=False)
    frac_df[exportcols].to_csv(f"data/subsets/dataset_size/imbalanced_{frac}.csv")
    balanced_frac_df = frac_df[frac_df.index.isin(balanced_df.index)]
    balanced_frac_df[exportcols].to_csv(f"data/subsets/dataset_size/balanced_{frac}.csv")
    print("imbalanced:", *[f"{k} = {v:.3f}" for k, v in sorted(list(frac_df.value_counts("split").to_dict().items()), key=lambda p: p[0])])
    print("balanced:", *[f"{k} = {v:.3f}" for k, v in sorted(list(balanced_frac_df.value_counts("split").to_dict().items()), key=lambda p: p[0])])

#%% check test sets all equal
import glob
for patt in ("data/subsets/dataset_size/imbalanced_*.csv", "data/subsets/dataset_size/balanced_*.csv"):
    test_sets = []
    for csv_filename in sorted(glob.glob(patt)):
        print(csv_filename)
        df = pd.read_csv(csv_filename, index_col=0)
        if "/balanced" in patt:
            vc = df.value_counts("target", normalize=True)
            assert np.all((0.4 < vc) & (vc < 0.6))
        test_sets.append(df[df["split"] == "test"])
    for i in range(len(test_sets)-1):
        pd.testing.assert_frame_equal(test_sets[i], test_sets[i+1])

#%% print statistics
"""
LOG
proportions:
        imbalanced  balanced
target                      
0.0       0.897009  0.524416
1.0       0.102991  0.475584
"""
# def get_target(row):
#     if row["dataset"] == "MSR":
#         if row["vul"] == 1:
#             return [1, 0]
#         else:
#             return [0]
#     else:
#         return [row["target"]]
# proportions = pd.concat(
#     (
#         imbalanced_df.assign(target=imbalanced_df.apply(get_target, axis=1)).explode("target").value_counts("target", normalize=True).to_frame(),
#         balanced_df.assign(target=balanced_df.apply(get_target, axis=1)).explode("target").value_counts("target", normalize=True).to_frame(),
#     ), axis=1, ignore_index=True)
# proportions.columns = ["imbalanced", "balanced"]
# print("proportions:")
# print(proportions)

#%% check that mutual exclusion and identicality are as expected
import glob
import pandas as pd
import tqdm
for balance in ["imbalanced", "balanced"]:
    test_idxs = []
    for file_name in tqdm.tqdm(glob.glob(f"data/subsets/dataset_size/{balance}_*.csv"), desc=f"check mutually exclusive for {balance}"):
        df = pd.read_csv(file_name, index_col=0)
        train_idx = set(zip(df[df["split"] == "train"]["dataset"].tolist(), df[df["split"] == "train"]["example_index"].tolist()))
        valid_idx = set(zip(df[df["split"] == "valid"]["dataset"].tolist(), df[df["split"] == "valid"]["example_index"].tolist()))
        test_idx = set(zip(df[df["split"] == "test"]["dataset"].tolist(), df[df["split"] == "test"]["example_index"].tolist()))
        assert len(train_idx.intersection(valid_idx)) == 0, "sets should be mutually exclusive"
        assert len(valid_idx.intersection(test_idx)) == 0, "sets should be mutually exclusive"
        test_idxs.append(test_idx)
    for i in tqdm.tqdm(range(len(test_idxs)-1), desc=f"check test sets identical for {balance}"):
        assert test_idxs[i] == test_idxs[i+1], "test sets should be identical"
