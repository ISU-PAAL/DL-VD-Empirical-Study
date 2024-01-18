#%%
import json
import numpy as np
import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt

#%%
reveal_df = None

splits_df = pd.read_csv("eval_exports/devign_reveal/splits.csv", usecols=["example_index", "split"]).set_index("example_index")
for seed in [1, 2, 3]:
    for model in ["reveal"]:
        fname = f"eval_exports/devign_reveal/eval_export_{model}_{seed}.csv"
        
        df = pd.read_csv(fname, usecols=["index", "prediction", "prob", "target"]).set_index("index")
        df = df.sort_index()
        df = df.join(splits_df)
        df["model"] = model
        df["seed"] = seed
        df["correct"] = df["prediction"] == df["target"]
        df["prob strength"] = np.abs(df["prob"] - 0.5)

        if reveal_df is None:
            reveal_df = df
        else:
            reveal_df = pd.concat((reveal_df, df))
reveal_df = reveal_df.rename_axis('training_example_index').reset_index()

map_df = pd.read_csv("eval_exports/devign_reveal/map.csv", index_col=0)
reveal_df = pd.merge(reveal_df, map_df, on="training_example_index").rename(columns={"codexglue_example_index": "example_index"}).sort_values(["example_index", "seed"])

with open("data/devign/function.json") as f:
    od = json.load(f)
code_df = pd.DataFrame(od)
reveal_df = pd.merge(reveal_df, code_df, how="left", left_on="example_index", right_index=True, suffixes=("", "_code"))
assert np.all(reveal_df["target"] == reveal_df["target_code"])
reveal_df = reveal_df.drop(columns=["target_code"])
reveal_df = reveal_df.rename(columns={"func": "code"})

reveal_df

#%% generate map.csv
if False:
    import pandas as pd
    import jsonlines
    import tqdm.auto as tqdm
    import itertools
    data = {
        "training_example_index": [],
        "codexglue_example_index": [],
    }
    with jsonlines.open("data/devign/full_experiment_real_data_processed/devign-full_graph.jsonlines") as reader:
        # reader = itertools.islice(reader, 1000)
        for i, example in tqdm.tqdm(enumerate(reader), desc="read jsonl"):
            func_json_idx = int(example["file_name"].split("_")[0])
            data["training_example_index"].append(i)
            data["codexglue_example_index"].append(func_json_idx-1)
    map_df = pd.DataFrame(data)
    map_df.to_csv("eval_exports/devign_reveal/map.csv")
