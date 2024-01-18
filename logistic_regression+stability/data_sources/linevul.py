#%%
import pandas as pd
import numpy as np

dfs = []
for seed in (1, 2, 3):
    try:
        df = pd.read_csv(f"eval_exports/linevul/eval_export_{seed}.csv", index_col=0)
        df["model"] = "LineVul"
        df["seed"] = seed
        df = df.rename(columns={"index": "example_index", "splits": "split"})
        dfs.append(df)
    except FileNotFoundError:
        print("missing file for seed", seed)
linevul_df = pd.concat(dfs, ignore_index=True)
linevul_df = linevul_df.sort_values(["example_index", "seed"])

code_dfs = []
for split in ("train", "val", "test"):
    df = pd.read_csv(f"eval_exports/linevul/eval_export_{split}.csv", index_col=0)
    df = df.rename(columns={"processed_func": "code"})
    code_dfs.append(df)
code_df = pd.concat(code_dfs)
linevul_df = pd.merge(linevul_df, code_df, left_on="example_index", right_index=True, suffixes=("", "_code"))
assert np.all(linevul_df["target"] == linevul_df["target_code"])
assert np.all(linevul_df["split"] == linevul_df["split_code"])
linevul_df = linevul_df.drop(columns=["target_code", "split_code"])

linevul_df
