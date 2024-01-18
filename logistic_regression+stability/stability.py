#%%
from data_sources.devign import devign_df
from data_sources.reveal import reveal_df
from data_sources.codebert import codebert_df
from data_sources.regvd import regvd_df
from data_sources.vulberta import vulberta_df
from data_sources.vulberta_cnn import vulbertacnn_df
from data_sources.linevul import linevul_df
from data_sources.code2vec import code2vec_df
from data_sources.plbart import plbart_df
import numpy as np
import pandas as pd

dfs = [
    plbart_df,
    code2vec_df,
    vulbertacnn_df,
    devign_df,
    reveal_df,
    codebert_df,
    regvd_df,
    vulberta_df,
    linevul_df,
]
df_names = [
    "plbart",
    "code2vec",
    "vulbertacnn",
    "devign",
    "reveal",
    "codebert",
    "regvd",
    "vulberta",
    "linevul",
]
dfs = [df for df in dfs if df["seed"].nunique() == 3]
df = pd.concat(dfs).reset_index(drop=True)
df["correct"] = df["prediction"] == df["target"]
# df = df[df["split"] == "test"]
df["model"].unique()

#%%

# Data analysis method:
# 1) The group of agreement across the models;
# 2) Analyze the model results for different category of models;
# 3) manual inspection of stable incorrect (smallest programs

# Summary of findings:
# 1) Unstable inputs range from x%, y%, average z%
# 2) Unstable likely to be incorrect?
# 3) All models agree on a% of the predictions, the same category of models agree more than across models

# %%
# 1) Unstable inputs range from x%, y%, average z%
# 2) Unstable likely to be incorrect?
df["correct"] = df["prediction"] == df["target"]
datas = []
for model, thismodel in df.groupby("model"):
    # print(model)
    thismodel["stable"] = thismodel.groupby("example_index")["prediction"].transform("nunique").eq(1)
    percent_same_prediction = thismodel.groupby("example_index")["prediction"].nunique().eq(1).rename_axis("stable").value_counts(normalize=True)
    # print("percent stable", np.average(thismodel["stable"]))
    # print("stable <=> incorrect", np.average(thismodel["stable"] == ~thismodel["correct"]))
    # print(thismodel.value_counts(["stable", "correct"], normalize=True))
    # print(thismodel["prob"].mean())
    data = {
        "model": model,
        "percent stable": np.average(thismodel["stable"]),
        # "stable incorrect": np.average(thismodel["stable"]),
        # "unstable incorrect": np.average(thismodel["stable"]),
    }
    for s, g in thismodel.groupby("stable"):
        # print("stable:", s, "% incorrect:", g.value_counts("correct", normalize=True)[False])
        data[f"stable={s} incorrect"] = g.value_counts("correct", normalize=True)[False]
        # data[f"stable={s} prob strength"] = np.abs(g["prob"].mean() - 0.5)
        # data[f"stable={s} positive"] = g.value_counts("target", normalize=True)[1]
    # thismodel["prob strength"] = np.abs(thismodel["prob"] - 0.5)
    # print(model)
    # print(thismodel[["prob strength", "stable"]].corr())
    datas.append(data)
stable_df = pd.DataFrame(datas)
stable_df

#%%
stable_df.describe()

#%%
stable_df.median()

#%%
stable_df[stable_df["model"].isin(("devign", "reveal"))]["percent stable"].mean()

#%%
stable_df[~stable_df["model"].isin(("devign", "reveal"))]["percent stable"].mean()

#%%
stable_df["stable=False incorrect"].mean() - stable_df["stable=True incorrect"].mean()

#%%
# (stable_df["stable=True prob strength"] - stable_df["stable=False prob strength"]).mean()

#%%

def calculate_agreement(df, seedwise):
    if seedwise:
        all_seed_agreement = []
        for s, group in df.groupby("seed"):
            seed_agreement = np.average(group.groupby("example_index")["prediction"].nunique().eq(1))
            all_seed_agreement.append(seed_agreement)
        return np.average(all_seed_agreement)
    else:
        return np.average(df.groupby("example_index")["prediction"].nunique().eq(1))

import itertools
# 3) All models agree on a% of the predictions, the same category of models agree more than across models
def get_agreement(df, groupname, group, combinations=None, seedwise=False):
    df = df[df["model"].isin(group)]
    models = df["model"].sort_values().unique()
    if combinations:
        pairwise_agreements = []
        for p in itertools.combinations(models, combinations):
            ab = df[df["model"].isin(p)]
            agreement = calculate_agreement(ab, seedwise)
            pairwise_agreements.append(agreement)
        print(len(pairwise_agreements), "combinations")
        all_agreement = np.average(pairwise_agreements)
    else:
        all_agreement = calculate_agreement(df, seedwise)
    print(groupname, "agree on", round(all_agreement, 4), models, "combinations:", combinations, "seedwise:", seedwise)
    return all_agreement


get_agreement(df, "all", [
    'devign',
    'reveal',
    'codebert',
    'GNN-ReGVD',
    'LineVul',
    'Code2Vec',
    'VulBERTa-CNN',
    'vulberta',
    'PLBART',
])
# get_agreement(df, "all", [
#     'devign',
#     'reveal',
#     'codebert',
#     'GNN-ReGVD',
#     'LineVul',
#     'Code2Vec',
#     'VulBERTa-CNN',
#     'vulberta',
#     'PLBART',
# ], pairwise=True)

# gnns = [
#     'devign',
#     'reveal',
# ]
# transformers = [
#     'codebert',
#     'LineVul',
#     'PLBART',
#     'VulBERTa-CNN',
#     'vulberta',
#     'PLBART',
# ]
get_agreement(df, "GNN", [
    'devign',
    'reveal',
    'GNN-ReGVD',
])
get_agreement(df, "Transformer", [
    'codebert',
    'LineVul',
    'PLBART',
    'VulBERTa-CNN',
    'vulberta',
])
get_agreement(df, "Transformer top 3 performance", [
    # 'codebert',
    'LineVul',
    'PLBART',
    'VulBERTa-CNN',
    # 'vulberta',
])
# get_agreement(df, "Transformer top 3 performance", [
#     'codebert',
#     'LineVul',
#     'PLBART',
#     'VulBERTa-CNN',
#     'vulberta',
# ], combinations=3)
# get_agreement(df, "Transformer top 3 stability", [
#     # 'codebert',
#     'LineVul',
get_agreement(df, "CPG-GNN", [
    'devign',
    'reveal',
])
get_agreement(df, "Token-based", [
    'GNN-ReGVD',
    'codebert',
    'LineVul',
    'PLBART',
    'VulBERTa-CNN',
    'vulberta',
])
get_agreement(df, "Token-based top 3 performance", [
    # 'codebert',
    'LineVul',
    'PLBART',
    'VulBERTa-CNN',
    # 'vulberta',
])
#     'PLBART',
#     'VulBERTa-CNN',
#     # 'vulberta',
# ])
# get_agreement(df, "Transformer", transformers, pairwise=False)

# iagreements = []
# rs = np.random.RandomState(seed=0)
# all_models = df["model"].sort_values().unique()
# print("choosing out of", all_models)
# for i in gnns:
#     for j in transformers:
#         iagreements.append(get_agreement(df, f"mismatch {i}", [i, j]))
# print("average random agreement:", np.average(iagreements))
pass

#%% report portion correct of all agreed
group = [
    'devign',
    'reveal',
    'codebert',
    'GNN-ReGVD',
    'LineVul',
    'Code2Vec',
    'VulBERTa-CNN',
    'vulberta',
    'PLBART',
]
df = df[df["model"].isin(group)]
models = df["model"].sort_values().unique()
agreed = df.groupby("example_index")["prediction"].nunique().eq(1)
all_agreement = np.average(agreed)
agreed_examples = agreed[agreed == True].index
print(np.average(df[df["example_index"].isin(agreed_examples)].drop_duplicates(subset=["example_index"])["correct"]))
print("all", "agree on", round(all_agreement, 4), models)

#%% performance variability across seeds (broken)
from sklearn.metrics import f1_score

def get_performance(group):
    group = group[group["split"] == "test"]
    performance = f1_score(group["target"], group["prediction"])
    return performance
performance_by_model_and_seed = df.groupby(["model", "seed"]).apply(get_performance).to_frame()
print(performance_by_model_and_seed.groupby(level=0).mean())
print(performance_by_model_and_seed.groupby(level=0).std())
