#%%
from random import random
import pandas as pd

from case_studies.code_feats import *
from data_sources.devign import *
from data_sources.reveal import *
from data_sources.codebert import *
from data_sources.regvd import *
from data_sources.vulberta import *
from data_sources.vulberta_cnn import *
from data_sources.linevul import *
from data_sources.code2vec import *
from data_sources.plbart import *
from case_studies.get_lr_dataset import *


#%% get performance ordered by code feats
from sklearn.metrics import *


performance_by_percentile = []
import warnings

warnings.filterwarnings("ignore")

devign_code_df = (
    pd.read_json("data/devign/function.json")
    .rename_axis("example_index")
    .reset_index()
    .rename(columns={"func": "code"})[["example_index", "code"]]
)
devign_code_ds = get_counts_new(devign_code_df)
devign_code_ds = get_code_feats(devign_code_ds)
with open("data/CodeXGLUE-main/Code-Code/Defect-detection/dataset/train.txt") as f:
    train_indices = [int(l) for l in f.readlines()]
with open("data/CodeXGLUE-main/Code-Code/Defect-detection/dataset/valid.txt") as f:
    valid_indices = [int(l) for l in f.readlines()]
with open("data/CodeXGLUE-main/Code-Code/Defect-detection/dataset/test.txt") as f:
    test_indices = [int(l) for l in f.readlines()]
splits_df = (
    pd.DataFrame(
        [
            {"split": s, "example_index": i}
            for s, i in zip(
                ("train", "valid", "test"), (train_indices, valid_indices, test_indices)
            )
        ]
    )
    .explode("example_index")
    .sort_values("example_index")
    .reset_index(drop=True)
)
devign_code_ds = pd.merge(devign_code_ds, splits_df, on="example_index")

#%%
# from lr import process_model_sklearn

#%%
from sklearn.linear_model import LogisticRegression
from sklearn.utils import shuffle
import numpy as np
from sklearn.preprocessing import StandardScaler
from sklearn.feature_selection import VarianceThreshold

def process_model_sklearn(model_output, modelname, my_code_ds, verbose=True, scaler=True, variance=True):
    if verbose:
        print(modelname)
    model_predictions = model_output
    model_predictions["stable"] = model_predictions.groupby("example_index")["prediction"].transform("nunique").eq(1)
    model_predictions = model_predictions[model_predictions["stable"]].drop_duplicates(subset="example_index")
    model_predictions["correct"] = (model_predictions["prediction"].astype(int) == model_predictions["target"].astype(int)).astype(int)
    ds = pd.merge(my_code_ds, model_predictions, on="example_index", how="inner")

    x = ds[[c for c in ds.columns if c in code_feats_to_observe]]
    y = ds["correct"]

    # print(x)
    # print(y)

    # VarianceThreshold
    if variance:
        sel = VarianceThreshold(threshold=(.1)).fit(x.to_numpy())
        feats_in = x.columns.tolist()
        feats_out = sel.get_feature_names_out(input_features=feats_in)
        if verbose:
            print("removed feats:", list(sorted(set(feats_in) - set(feats_out))))
        x = x[feats_out]

    # StandardScaler
    if scaler:
        x_values = x.to_numpy()
        scaler = StandardScaler()
        if verbose:
            print("Before normalize:")
            print(x_values.mean(axis=0))
            print(x_values.std(axis=0))
        x_values = scaler.fit_transform(x_values)
        if verbose:
            print("After normalize:")
            print(x_values.mean(axis=0))
            print(x_values.std(axis=0))
        x.loc[:] = x_values

    x, y = shuffle(x, y, random_state=0)
    X_train = x
    y_train = y

    unique, counts = np.unique(y_train, return_counts=True)
    clf = LogisticRegression(random_state=0, max_iter=1e4).fit(X_train, y_train)
    
    perf = clf.score(x, y)
    # print("fit score:", perf)
    # print(clf.coef_.shape)
    result_df = pd.DataFrame(clf.coef_[0].tolist(), columns=["coeff"], index=list(feats_out))
    result_df = result_df.sort_values("coeff")
    return result_df, perf

#%%
def report_performance(ds):
    SCORES = (
        accuracy_score,
        precision_score,
        recall_score,
        f1_score,
    )
    results = {
        score_fn.__name__: score_fn(ds["target"], ds["prediction"])
        for score_fn in SCORES
    }
    return results

#%% get hard set from MSR
from getset_root import combined_df
msr = combined_df[combined_df["dataset"] == "MSR"]
msr = msr.assign(func=msr["func_before"])
msr_code_df = msr[["example_index", "func"]].rename(columns={"func": "code"})
msr_code_ds = get_counts_new(msr_code_df)
msr_code_ds = get_code_feats(msr_code_ds)
msr_code_ds = pd.merge(msr_code_ds, msr[["example_index", "target"]], on="example_index", how="inner")

#%%
# Devign test set
split_ds = devign_code_ds[devign_code_ds["split"].isin(["test"])]
# MSR entire set TODO implement
# split_ds = msr_code_ds

# Devign valid set
lrsplit_ds = devign_code_ds[devign_code_ds["split"].isin(("valid",))]

#%%
model_names = (
    "Devign",
    "ReVeal",
    "CodeBERT",
    "ReGVD",
    "VulBERTa-MLP",
    "VulBERTa-CNN",
    "LineVul",
    "Code2Vec",
    "PLBART",
)

model_outputs = dict(zip(
    model_names,
    (
        devign_df,
        reveal_df,
        codebert_df,
        regvd_df,
        vulberta_df,
        vulbertacnn_df,
        linevul_df,
        code2vec_df,
        plbart_df,
    ),
))

#%%
from data_sources.devign_msr import devign_msr_df
from data_sources.reveal_msr import reveal_msr_df
from data_sources.regvd_msr import regvd_msr_df
from data_sources.plbart_msr import plbart_msr_df
from data_sources.linevul_msr import linevul_msr_df
from data_sources.codebert_msr import codebert_msr_df
from data_sources.code2vec_msr import code2vec_msr_df
from data_sources.vulberta_msr import vulberta_msr_df
from data_sources.vulberta_cnn_msr import vulbertacnn_msr_df

#%%

model_output_dfs = [
    plbart_msr_df,
    devign_msr_df,
    reveal_msr_df,
    regvd_msr_df,
    codebert_msr_df,
    code2vec_msr_df,
    linevul_msr_df,
    vulberta_msr_df,
    vulbertacnn_msr_df,
]
model_names = [
    "PLBART",
    "Devign",
    "ReVeal",
    "ReGVD",
    "CodeBERT",
    "Code2Vec",
    "LineVul",
    "VulBERTa-MLP",
    "VulBERTa-CNN",
]
model_outputs = dict(zip(model_names, model_output_dfs,))

#%%
for modelname, mo in zip(model_names, model_output_dfs):
    print(modelname)
    for c in ["prediction", "example_index"]:
        assert c in mo.columns, (c, mo.columns)

#%%
splits_df = pd.read_csv("data/linevul_splits/splits.csv")

#%% switch to analyzing MSR dataset
# MSR test set
msr_split_ds = pd.merge(msr_code_ds, splits_df, left_on="example_index", right_on="index", suffixes=("", "_y"))

split_ds = msr_split_ds[msr_split_ds["split"].isin(["test"])]

# MSR valid set
lrsplit_ds = msr_split_ds[msr_split_ds["split"].isin(["valid"])]

#%%
all_results = []
lr_models = {}
for modelname in model_names:
    print(modelname)
    mo = model_outputs[modelname]
    if "target" not in mo:
        mo = pd.merge(mo, msr[["example_index", "target"]], on="example_index")
    # print(mo)

    # for seed in (1, 2, 3):
    mo["stable"] = mo.groupby("example_index")["prediction"].transform("nunique").eq(1)
    stable_mo = mo[mo["stable"]]
    stable_mo = stable_mo[["example_index", "prediction", "target"]].drop_duplicates()
    assert stable_mo.value_counts("example_index").max() == 1, stable_mo.value_counts("example_index")

    lr_df, performance = process_model_sklearn(stable_mo, modelname, lrsplit_ds, verbose=False, scaler=False, variance=True)
    lr_models[modelname] = lr_df

    for seed, seedgroup in mo.groupby("seed"):
        mo_ds = pd.merge(split_ds, seedgroup, on="example_index", suffixes=("", "_y"))
        mo_ds["easiness"] = mo_ds.apply(
            lambda row: np.sum(row[featname]*easiness for featname, easiness in lr_df["coeff"].to_dict().items()),
            axis=1)

        mo_ds = mo_ds.sort_values("easiness", ascending=True)
        ten_percent = int(len(mo_ds)*0.1)
        bad_result = report_performance(mo_ds.iloc[:ten_percent])
        bad_result["version"] = "bad"
        good_result = report_performance(mo_ds.iloc[-ten_percent:])
        good_result["version"] = "good"

        bad_result["performance"] = performance
        good_result["performance"] = performance

        bad_result["model"] = modelname
        good_result["model"] = modelname
        bad_result["seed"] = seed
        good_result["seed"] = seed

        all_results.append(bad_result)
        all_results.append(good_result)
all_results_df = pd.DataFrame(data=all_results)
all_results_df

#%% validate that good(easy) and bad(hard) sets are easy/hard
datas=[]
for model, group in all_results_df.groupby("model"):
    # print(group[["version", "f1_score"]])
    mean_f1 = group.groupby("version")["f1_score"].mean()
    # print(mean_f1)
    assert len(mean_f1) == 2
    signed_difference = (
        mean_f1.loc["good"] -
        mean_f1.loc["bad"]
        )
    datas.append({"model": model, "seed": seed, "good f1 - bad f1": signed_difference})
    # print(model, group[group["version"] == "good"]["accuracy_score"].iloc[0] - group[group["version"] == "bad"]["accuracy_score"].iloc[0])
performance_df = pd.DataFrame(datas)
performance_df

#%%
present_df = all_results_df.groupby(["model", "version"])[["accuracy_score", "precision_score", "recall_score", "f1_score"]].mean().reset_index().sort_values(["version", "model"])
present_df["version"] = present_df["version"].replace({"bad": "difficult", "good": "easy"})
present_df.pivot(index="model", columns="version").to_clipboard()

#%%
import tqdm.auto as tqdm

for modelname in tqdm.tqdm(model_names):
    lr = lr_models[modelname]
    msr_code_ds[f"easiness_{modelname}"] = msr_code_ds.apply(
        lambda row: np.sum(row[featname]*easiness for featname, easiness in lr["coeff"].to_dict().items()),
        axis=1)

#%%
devign_split_dfs = []
for split in ("train", "valid", "test"):
    split_fname = f"data/CodeXGLUE-main/Code-Code/Defect-detection/dataset/{split}.txt"
    with open(split_fname) as f:
        indices = f.readlines()
    codexglue_indices = [int(i) for i in indices]
    devign_split_df = pd.DataFrame(codexglue_indices, columns=["example_index"])
    devign_split_df["split"] = split
    devign_split_dfs.append(devign_split_df)
devign_split_df = pd.concat(devign_split_dfs, ignore_index=True).sort_values("example_index")
devign_split_df

#%%
balanced_df = pd.read_csv("data/subsets/dataset_size/balanced_1.0.csv")

def do_split(df):
    rs = np.random.RandomState(seed=0)
    train_end = int(len(df) * 0.9)
    split = pd.Series(range(len(df)), index=rs.permutation(df.index)).apply(lambda i: "train" if i <= train_end else "valid")
    return split

import os
def export_set(model, n):
    devign_subset = combined_df[combined_df["dataset"] == "Devign"]
    devign_subset = pd.merge(devign_subset, devign_split_df, how="left", on="example_index")
    msr_subset = combined_df[combined_df["dataset"] == "MSR"]

    # difficult
    d = []
    for target in (0, 1):
        subset = msr_code_ds[msr_code_ds["target"] == target]
        d.append(subset.sort_values(f"easiness_{model}").iloc[:portion])
    difficult_set = pd.concat(d)
    msr_difficult_subset = pd.merge(msr_subset, difficult_set[["example_index", f"easiness_{model}"]], on="example_index", how="inner")
    msr_difficult_subset = msr_difficult_subset.assign(split=do_split(msr_difficult_subset))
    output_difficult_df = pd.concat((devign_subset, msr_difficult_subset))
    output_difficult_df = output_difficult_df[["dataset", "example_index", "project", "commit_id", f"easiness_{model}", "split", "target", "func"]]

    # easy
    d = []
    for target in (0, 1):
        subset = msr_code_ds[msr_code_ds["target"] == target]
        d.append(subset.sort_values(f"easiness_{model}").iloc[-portion:])
    easy_set = pd.concat(d)
    msr_easy_subset = pd.merge(msr_subset, easy_set[["example_index", f"easiness_{model}"]], on="example_index", how="inner")
    msr_easy_subset = msr_easy_subset.assign(split=do_split(msr_easy_subset))
    output_easy_df = pd.concat((devign_subset, msr_easy_subset))
    output_easy_df = output_easy_df[["dataset", "example_index", "project", "commit_id", f"easiness_{model}", "split", "target", "func"]]

    # random
    d = []
    for target in (0, 1):
        subset = msr_code_ds[msr_code_ds["target"] == target]
        d.append(subset.sample(n, random_state=np.random.RandomState(seed=0)))
    random_set = pd.concat(d)
    msr_random_subset = pd.merge(msr_subset, random_set[["example_index", f"easiness_{model}"]], on="example_index", how="inner")
    msr_random_subset = msr_random_subset.assign(split=do_split(msr_random_subset))
    output_random_df = pd.concat((devign_subset, msr_random_subset))
    output_random_df = output_random_df[["dataset", "example_index", "project", "commit_id", f"easiness_{model}", "split", "target", "func"]]

    # TODO check correctness
    def check_correctness(df, name):
        # print("checking", name)
        # print(df.value_counts("split", dropna=False, normalize=True))
        # print(df.value_counts("dataset", dropna=False, normalize=True))
        # print("exporting", len(df), "examples", "n=", n, "for", model)
        assert np.all(df.set_index(["dataset", "example_index"]).loc["Devign"]["split"] == devign_split_df.set_index("example_index")["split"])
        assert np.any(df[f"easiness_{model}"].isna())
        assert np.all((df[f"easiness_{model}"].isna()) == (df["dataset"] == "Devign"))
    check_correctness(output_difficult_df, "difficult")
    check_correctness(output_easy_df, "easy")
    check_correctness(output_random_df, "random")

    # output
    def output(df, name):
        df.drop(columns=["func"]).to_csv(f"data/subsets/difficult_sets/{name}_{model}_{n}.csv")
        os.makedirs(f"data/subsets/difficult_sets/{name}_{model}_{n}", exist_ok=True)
        for split, group in df.groupby("split"):
            group.to_json(f"data/subsets/difficult_sets/{name}_{model}_{n}/{split}.jsonl", orient="records", lines=True)
    output(output_difficult_df, "difficult")
    output(output_easy_df, "easy")
    output(output_random_df, "random")


difficult_sets = []
for portion in (1000, 2500, 5000):
    for modelname in tqdm.tqdm(["Devign", "ReVeal", "LineVul"]):
        export_set(modelname, portion)

#%%
melted = pd.wide_to_long(msr_code_ds, stubnames="easiness", sep="_", i="example_index", j="model", suffix=r'\w+')
# melted = melted.sort_values("easiness").iloc[:5000]
melted = melted.reset_index()
melted = melted.sort_values("easiness")
melted = melted.drop_duplicates(subset=["example_index"], keep="first")
portion=5000
d = []
for target in (0, 1):
    subset = melted[melted["target"] == target]
    chosen = subset.sort_values("easiness").iloc[:portion]
    d.append(chosen)
difficult_set = pd.concat(d)
difficult_set

#%%
all_lr = []
model_order = [
    # GNN
    "Devign",
    "ReVeal",
    "ReGVD",
    # Transformer
    "CodeBERT",
    "VulBERTa-CNN",
    "VulBERTa-MLP",
    "PLBART",
    "LineVul",
    # MLP
    "Code2Vec",
]
# model_order = dict(zip(model_order, range(len(model_order))))
for modelname in model_order:
    lr = lr_models[modelname].copy()
    lr = lr.sort_values("coeff")
    lr = lr.rename(columns={"coeff": f"coeff_{modelname}"})
    lr = lr.rename_axis(f"name_{modelname}").reset_index()
    # lr["model"] = modelname
    all_lr.append(lr)
all_lr = pd.concat(all_lr, axis=1)
# all_lr.columns = pd.MultiIndex.from_tuples([(c.split("_")[1], c.split("_")[0]) for c in all_lr.columns])
# all_lr = pd.wide_to_long(all_lr, stubnames="coeff", sep="_", i="model", j="stuff", suffix=r'\w+')
# all_lr = pd.wide_to_long(all_lr, stubnames=["coeff", "name"], sep="_", i="model", j="stuff", suffix=r'\w+')
# all_lr.pivot(index="model", columns="coeff")
all_lr.to_clipboard()
all_lr
