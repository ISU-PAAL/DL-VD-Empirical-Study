#%%
import pandas as pd

test_df = pd.read_csv("data/linevul_splits/test.csv")
test_df["split"] = "test"
train_df = pd.read_csv("data/linevul_splits/train.csv")
train_df["split"] = "train"
valid_df = pd.read_csv("data/linevul_splits/val.csv")
valid_df["split"] = "valid"

#%%
merge_df = pd.concat((train_df[["index", "split"]], valid_df[["index", "split"]], test_df[["index", "split"]]), ignore_index=True)
merge_df = merge_df.set_index("index").sort_index()
merge_df

#%%
merge_df.value_counts("split", normalize=True)

#%%
merge_df.to_csv("data/linevul_splits/splits.csv")

#%%
split_df = pd.read_csv("data/MSR/full_experiment_real_data_processed/vlinevd/splits.csv")
split_df

# %%
