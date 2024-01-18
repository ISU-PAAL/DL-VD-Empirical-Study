"""
Back before we'd assigned sequential indices to the dataset examples,
this script was used to pair up the dataset examples in GGNN input with the original source code.
NOT NEEDED ANYMORE, use the indices assigned in split_data_original.py.
"""
import json
import pandas as pd
import jsonlines
import tqdm

if __name__ == "__main__":
    print("load w2v")
    w2v_hash = {}
    with jsonlines.open('devign-line_ggnn.jsonlines') as reader:
        for i, d in enumerate(tqdm.tqdm(reader, desc="w2v")):
            w2v_hash[json.dumps(d["node_features"])] = i
    
    fold_idx = 1
    print("load splitted data from fold", fold_idx)
    split_hash = {}
    for split in ["train", "valid", "test"]:
        with jsonlines.open(f"devign/v{fold_idx}/{split}_GGNNinput.jsonlines") as reader:
            for i, d in enumerate(tqdm.tqdm(reader, desc=f"fold {fold_idx}")):
                split_hash[json.dumps(d["node_features"])] = (split, i)
    
    print("pair up")
    df = pd.DataFrame([(wi, fold_idx, *(split_hash.get(h, ("not found", -1)))) for h, wi in w2v_hash.items()], columns=["w2v_idx", "fold_idx", "split", "split_idx"])
    del w2v_hash
    del split_hash
    df.to_csv("devign-line_ggnn.json__to__split_GGNNinput.csv")

    print("load code")
    with open("../ggnn_input/devign_cfg_full_text_files.json") as f:
        code_data = json.load(f)

    print("aapply code")
    df["code"] = df["w2v_idx"].apply(lambda i: code_data[i]["code"])
    df["file_name"] = df["w2v_idx"].apply(lambda i: code_data[i]["file_name"])
    df.to_csv("devign-line_ggnn.json__to__split_GGNNinput__full.csv")
