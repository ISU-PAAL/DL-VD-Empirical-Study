"""
Export CSVs of devign
"""

#%%
import pandas as pd
import os

#%%
split_idx = []
split_label = []
for split in ("train", "valid", "test"):
    fname = os.path.join("data/devign/codexglue_splits", f"{split}.txt")
    with open(fname) as f:
        for i in f.readlines():
            split_idx.append(int(i))
            split_label.append(split)
split_df = pd.DataFrame(data={"split": split_label}, index=split_idx).sort_index()
split_df

#%%
devign_src = "data/devign/function.json"
devign_df = pd.read_json(devign_src)
devign_df = devign_df.rename(columns={"func": "processed_func"})
devign_df = devign_df.join(split_df)
devign_df

#%%
linevul_dst = "/home/<ANONYMOUS>/code/LineVul/data/devign"
rows_written = 0
for split in ("train", "valid", "test"):
    split_subset = devign_df[devign_df["split"] == split]
    split_subset.to_csv(os.path.join(linevul_dst, f"{split}.csv"))
    rows_written += len(split_subset)
print(rows_written, "rows written")
