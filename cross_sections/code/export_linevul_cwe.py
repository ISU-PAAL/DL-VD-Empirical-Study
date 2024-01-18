"""
Export CSVs of RQ.A2 (bug types) for linevul ingestion
"""

#%%
import pandas as pd
from getset_root import combined_df, msr_df

#%%
source_df = msr_df[["dataset", "example_index", "func_before", "target"]].copy()
source_df = source_df.rename(columns={"func_before": "processed_func"})

#%%
import os
import glob
import tqdm
linevul_dst = "/home/<ANONYMOUS>/code/LineVul"
filelist = []
# sorted(glob.glob("data/subsets/bug_type/*.csv"))
filelist += ("data/subsets/bug_type/bugtype_mixed.csv",)
for f in filelist:
    assert os.path.exists(f), f
filelist

#%%
for file in tqdm.tqdm(filelist):
    dsname = os.path.splitext(os.path.basename(file))[0]
    dsdir = os.path.join(linevul_dst, os.path.dirname(file), dsname)
    assert not os.path.exists(dsdir)
    if os.path.exists(dsdir):
        continue
    else:
        os.makedirs(dsdir, exist_ok=False)
    split_df = pd.read_csv(file, index_col=0)
    merge_df = pd.merge(split_df[["dataset", "example_index", "split"]], source_df[["dataset", "example_index", "processed_func", "target"]], how="inner", on=["dataset", "example_index"])
    for splitname, group in merge_df.groupby("split"):
        dstfile = os.path.join(dsdir, splitname + ".csv")
        group.to_csv(dstfile)
        print(file, dstfile, splitname, len(group))
