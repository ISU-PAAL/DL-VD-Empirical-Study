#%%
import pandas as pd

codebert_df = pd.read_csv("eval_exports/result-vulberta-codebert-codexglue-v3.csv")
codebert_df = codebert_df[codebert_df["model"] == "codebert"]
codebert_df["original_seed"] = codebert_df["seed"]
codebert_seed_map = {s: i for i, s in enumerate(sorted(codebert_df["original_seed"].unique()), start=1)}
codebert_df["seed"] = codebert_df["original_seed"].map(codebert_seed_map)
codebert_df = codebert_df.sort_values(["example_index", "seed"])
codebert_df = codebert_df.rename(columns={"func": "code"})
codebert_df
