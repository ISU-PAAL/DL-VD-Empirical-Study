#%%
import pandas as pd
import numpy as np

dfs = []
for seed in (1, 2, 3):
    code2vec_df = pd.read_csv(f"eval_exports/code2vec/seed {seed}/devign.csv", index_col=0)
    code2vec_df["model"] = "Code2Vec"
    code2vec_df["seed"] = seed
    code2vec_df = code2vec_df.rename(columns={"probability": "prob"})
    dfs.append(code2vec_df)
code2vec_df = pd.concat(dfs, ignore_index=True)
code2vec_df = code2vec_df.sort_values(["example_index", "seed"])
# assert np.all((code2vec_df["prob"] >= 0.5) == code2vec_df["prediction"])

code2vec_df
