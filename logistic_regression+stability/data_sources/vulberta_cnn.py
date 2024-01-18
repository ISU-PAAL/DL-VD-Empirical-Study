#%%
import pandas as pd

dfs = []
for seed in (1, 2, 3):
    vulbertacnn_df = pd.read_csv(f"eval_exports/results_VulBERTa-CNN_{seed}.csv")
    vulbertacnn_df["model"] = "VulBERTa-CNN"
    vulbertacnn_df["split"] = vulbertacnn_df["split"].replace("val", "valid")
    vulbertacnn_df = vulbertacnn_df.sort_values(["example_index", "seed"])
    vulbertacnn_df = vulbertacnn_df.rename(columns={"func": "code"})
    dfs.append(vulbertacnn_df)
vulbertacnn_df = pd.concat(dfs, ignore_index=True)
vulbertacnn_df.head(6)

#%%
vulbertacnn_df["correct"] = vulbertacnn_df["prediction"] == vulbertacnn_df["target"]
vulbertacnn_df["correct"].value_counts()

#%%
vulbertacnn_df["num_correct"] = vulbertacnn_df.groupby(["example_index", "model"])["correct"].transform(sum)
vulbertacnn_df["num_correct"].value_counts()
