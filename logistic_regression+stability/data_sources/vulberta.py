#%%
import pandas as pd

vulberta_df = pd.read_csv("eval_exports/result-vulberta-codebert-codexglue-v3.csv")
vulberta_df = vulberta_df[vulberta_df["model"] == "vulberta"]
vulberta_df["original_seed"] = vulberta_df["seed"]
vulberta_seed_map = {s: i for i, s in enumerate(sorted(vulberta_df["original_seed"].unique()), start=1)}
vulberta_df["seed"] = vulberta_df["original_seed"].map(vulberta_seed_map)
vulberta_df = vulberta_df.sort_values(["example_index", "seed"])
vulberta_df = vulberta_df.rename(columns={"func": "code"})
vulberta_df.head(6)

#%%
# regvd_df = regvd_df[regvd_df["split"] == "train"]
#%%
vulberta_df["correct"] = vulberta_df["prediction"] == vulberta_df["target"]
vulberta_df["correct"].value_counts()

#%%
vulberta_df["num_correct"] = vulberta_df.groupby(["example_index", "model"])["correct"].transform(sum)
vulberta_df["num_correct"].value_counts()
