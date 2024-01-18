"""
See how dataset is constructed and compare to original.
Why is processed_func processed?
"""

#%%
import pandas as pd

dataset_dfs = []
for split_name in ["train", "val", "test"]:
    dataset_dfs.append(pd.read_csv(f"data/big-vul_dataset/{split_name}.csv", index_col=0))
dataset_df = pd.concat(dataset_dfs, ignore_index=False).sort_index()
dataset_df

#%%
msr_df = pd.read_csv("/home/<ANONYMOUS>/code/ReVeal/data/MSR/MSR_data_cleaned.csv", index_col=0)
msr_df

#%%
merge_df = dataset_df.join(msr_df, how="inner", lsuffix="_test", rsuffix="_msr")
merge_df

#%%
import difflib
import itertools
mismatch = merge_df[merge_df["func_before_test"] != merge_df["processed_func"]]
for tup in itertools.islice(mismatch.itertuples(), 5):
    print("".join(difflib.ndiff(
        tup.func_before_test.splitlines(keepends=True),
        tup.processed_func.splitlines(keepends=True)
        )))
mismatch
# %%
still_mismatch = mismatch[mismatch["func_before_test"].str.split().str.join("") != mismatch["processed_func"].str.split().str.join("")].copy()
still_mismatch["func_before_test"] = mismatch["func_before_test"].str.split().str.join("\n")
still_mismatch["processed_func"] = mismatch["processed_func"].str.split().str.join("\n")
for tup in itertools.islice(still_mismatch.itertuples(), 5):
    print("".join(difflib.ndiff(
        tup.func_before_test.splitlines(keepends=True),
        tup.processed_func.splitlines(keepends=True)
        )))
# still_mismatch[["func_before_test", "processed_func"]]

# %%
