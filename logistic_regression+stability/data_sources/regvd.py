#%%
import json
import numpy as np
import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt

regvd_df = pd.read_csv("eval_exports/result-regvd-codexglue.csv")
regvd_df

#%%
# regvd_df = regvd_df[regvd_df["split"] == "train"]
#%%
regvd_df["correct"] = regvd_df["prediction"] == regvd_df["target"]
regvd_df["correct"].value_counts()

#%%
regvd_df["num_correct"] = regvd_df.groupby(["example_index", "model"])["correct"].transform(sum)
regvd_df["num_correct"].value_counts()
