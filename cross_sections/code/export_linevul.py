"""
Export CSVs of RQ.B1 for linevul ingestion
"""

#%%
import pandas as pd
from getset_root import combined_df

#%%
source_df = combined_df[["dataset", "example_index", "func", "func_before", "target", "vul"]].copy()
source_df.loc[source_df["target"].isna(), "target"] = source_df["vul"]
source_df["processed_func"] = source_df.apply(lambda row: row["func_before"] if row["dataset"] == "MSR" else row["func"], axis=1)
source_df = source_df.drop(columns=["func_before", "func"])

#%%
import os
import glob
import tqdm
linevul_dst = "/home/<ANONYMOUS>/code/LineVul/data/subsets/dataset_size"
# for file in tqdm.tqdm(sorted(glob.glob("data/subsets/dataset_size/*.csv"))):
filelist = []
filelist += sorted(glob.glob("data/subsets/dataset_size/*_0.01.csv"))
filelist += sorted(glob.glob("data/subsets/dataset_size/*_0.05.csv"))

#%%
for file in tqdm.tqdm(filelist):
    print("exporting", file)
    dsname = os.path.splitext(os.path.basename(file))[0]
    dsdir = os.path.join(linevul_dst, dsname)
    os.makedirs(dsdir, exist_ok=True)
    split_df = pd.read_csv(file, index_col=0)
    merge_df = pd.merge(source_df[["dataset", "example_index", "processed_func", "target"]], split_df[["dataset", "example_index", "split"]], on=["dataset", "example_index"])
    for splitname, group in merge_df.groupby("split"):
        group.to_csv(os.path.join(dsdir, splitname + ".csv"))
