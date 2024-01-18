#%%
import pandas as pd
import numpy as np

dfs = []
for seed in (1, 2, 3):
    for split in ("train", "valid", "test"):
        plbart_df = pd.read_csv(f"eval_exports/PLBART/seed {seed}/model_devign_data_devign_{split}.csv")
        plbart_df["model"] = "PLBART"
        plbart_df["seed"] = seed
        plbart_df["split"] = split
        plbart_df = plbart_df.rename(columns={
            "Pred": "prediction",
            "Prob": "prob",
            "Target": "target",
        })
        assert np.all((plbart_df["prob"] >= 0.5) == plbart_df["prediction"])
        dfs.append(plbart_df)
plbart_df = pd.concat(dfs, ignore_index=False)
plbart_df = plbart_df.rename_axis("split_index").reset_index()
plbart_df

#%%

map_dfs = []
for split in ("train", "valid", "test"):
    with open(f"data/CodeXGLUE-main/Code-Code/Defect-detection/dataset/{split}.txt") as test_indices:
        codexglue_indices = [int(i) for i in test_indices.readlines()]
        map_df = pd.DataFrame(codexglue_indices, columns=["example_index"])
        map_df["split"] = split
        map_dfs.append(map_df)
map_df = pd.concat(map_dfs, ignore_index=False)
map_df["split_index"] = map_df.groupby("split").rank("first").astype(int) - 1
# map_df = map_df.rename_axis("split_index").reset_index()
map_df

#%%
merge_df = pd.merge(plbart_df, map_df, on=["split", "split_index"])
merge_df = merge_df.sort_values(["split", "example_index"])
merge_df

#%% check correctness against function.json labels
func_df = pd.read_json("data/devign/function.json")
merge2_df = pd.merge(merge_df, func_df, left_on="example_index", right_index=True, suffixes=("", "_func"))
merge2_df = merge2_df.sort_values("example_index")
assert np.all(merge2_df["target"] == merge2_df["target_func"])
merge2_df = merge2_df.drop(columns=["target_func"])
merge2_df = merge2_df.rename(columns={"func": "code"})
merge2_df

#%%
plbart_df = merge2_df
