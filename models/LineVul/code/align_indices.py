"""
Checker script.
"""

#%%
import pandas as pd
import glob
import os

split_dfs = []
for split_f in glob.glob("data/devign/*.csv"):
    if "eval_export" in split_f:
        continue
    splitname = os.path.splitext(os.path.basename(split_f))[0]
    split_df = pd.read_csv(split_f, index_col=0)
    split_df["split"] = splitname
    split_dfs.append(split_df)
split_df = pd.concat(split_dfs).sort_index()
split_df

#%%

for ee_f in glob.glob("data/devign/eval_export_1.csv"):
    df = pd.read_csv(ee_f, index_col=0)
    df = df.sort_values("example_index")
    print(df)
    # df = pd.merge(df, split_df, left_on="example_index", right_index=True)
    # print(df)
