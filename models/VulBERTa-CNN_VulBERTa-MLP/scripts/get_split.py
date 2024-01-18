#%%
import pandas as pd
import jsonlines
import tqdm.auto as tqdm

with jsonlines.open("data/finetune/msr/MSR_data_cleaned.jsonlines") as inf, jsonlines.open("data/finetune/msr/func_target_only.jsonlines", "w") as outf:
    for example in tqdm.tqdm(inf):
        outf.write({
            "func": example["func_before"],
            "project": example["project"],
            "commit_id": example["commit_id"],
            "target": example["vul"],
        })

#%%
import numpy as np
df = pd.read_json("data/finetune/msr/func_target_only.jsonlines", lines=True)

for i in tqdm.tqdm(range(5)):
    splits_df = pd.read_csv(f"data/finetune/combined/rqb4_2/fold_{i}_holdout.csv", index_col=0).set_index("example_index")
    merge_df = df.join(splits_df, rsuffix="_split", how="right")
    assert len(splits_df) == len(merge_df)
    assert not np.any(merge_df.isna())
    assert np.all(merge_df["project"] == merge_df["project_split"])
    assert np.all(merge_df["commit_id"] == merge_df["commit_id_split"])
    merge_df = merge_df.rename_axis("example_index").reset_index(drop=False)
    merge_df[["example_index", "func", "target", "project", "commit_id"]].to_json(f"data/finetune/combined/rqb4_2/fold_{i}_holdout/holdout.jsonl", orient="records", lines=True)

