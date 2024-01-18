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
import json

#%% check labels and code alignment
def compare(a, b):
    success = True

    ab = pd.merge(a, b, on="example_index", how="inner", suffixes=("_a", "_b"))

    print(len(ab))
    if len(ab) == 0:
        print("failed empty")
        success = False

    # print(ab)

    # All others for some reason can't be chopped because of their carriage return. Boo hoo.
    if not np.all(ab["target_a"] == ab["target_b"]):
        print("failed target")
        success = False

    if "code" in a.columns and "code" in b.columns:
        ab["matches_code"] = ab["code_a"].apply(lambda s: " ".join(s.split())) == ab["code_b"].apply(lambda s: " ".join(s.split()))
        if not np.all(ab["matches_code"]):
            print("failed code")
            success = False
    else:
        print("skip code")

    if "split" in a.columns and "split" in b.columns:
        if not np.all(ab["split_a"] == ab["split_b"]):
            print("failed split")
            success = False
    else:
        print("skip split")

    if "project" in a.columns and "project" in b.columns:
        if not np.all(ab["project_a"] == ab["project_b"]):
            print("failed project")
            success = False
    else:
        print("skip project")

    if "commit_id" in a.columns and "commit_id" in b.columns:
        if not np.all(ab["commit_id_a"] == ab["commit_id_b"]):
            print("failed commit_id")
            success = False
    else:
        print("skip commit_id")

    return success

#%%
dataset_df = pd.read_json("data/devign/function.json")
dataset_df = dataset_df.rename(columns={"func": "code"})
dataset_df = dataset_df.rename_axis("example_index").reset_index()
dataset_df

#%%

for seed in (1, 2, 3):
    print("seed", seed)
    # TODO: check against original df
    # (chances are low that ALL dfs would match and
    # be wrong, but this will make it complete)
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
    failed = []
    subset_dfs = [df[df["seed"] == seed] for df in dfs]
    subset_dfs.insert(0, dataset_df)
    df_names.insert(0, "dataset")
    for i in range(len(subset_dfs)):
        subset_dfs[i].to_csv(f"eval_export_clean/{df_names[i]}.csv")
        for j in range(len(subset_dfs)):
            # if i == j:
            #     continue
            print("***", df_names[i], df_names[j], "***")
            success = compare(subset_dfs[i], subset_dfs[j])
            if not success:
                failed.append((seed, df_names[i], df_names[j]))
            # break
        # break
    if len(failed) > 0:
        print("failed:", json.dumps(failed, indent=2))
    else:
        print("none failed")

    # subset_devign_df = devign_df[devign_df["seed"] == seed]
    # subset_reveal_df = reveal_df[reveal_df["seed"] == seed]
    # subset_regvd_df = regvd_df[regvd_df["seed"] == seed]
    # subset_codebert_df = codebert_df[codebert_df["seed"] == seed]
    # subset_vulberta_df = vulberta_df[vulberta_df["seed"] == seed]
    # print("regvd", "devign")
    # compare(subset_regvd_df, subset_devign_df)
    # print("regvd", "codebert")
    # compare(subset_regvd_df, subset_codebert_df)
    # print("codebert", "vulberta")
    # compare(subset_codebert_df, subset_vulberta_df)

# %%
