"""
Check that we are using the correct indices for devign preprocessing.
"""


#%%
import pandas as pd
import os
files_dir = "data/devign/raw_code"
files = os.listdir(files_dir)
datas = []
for fname in files:
    with open(os.path.join(files_dir, fname)) as f:
        datas.append({
            "file_name": fname,
            "code": f.read(),
        })
raw_code_df = pd.DataFrame(data=datas)
raw_code_df

#%%
preprocessed_df = pd.read_json("data/devign/full_experiment_real_data_processed/devign-line-ggnn.jsonlines", lines=True)
preprocessed_df

#%%
cached_code_df = pd.read_json("data/ggnn_input/devign_cfg_full_text_files.json")
cached_code_df

#%%
cached_feat_df = pd.read_json("data/line_ggnn/devign/devign-line_ggnn.jsonlines", lines=True)
cached_feat_df

#%%
cached_df = pd.concat((cached_code_df, cached_feat_df), axis=0)
cached_df
