#%%
# Count number of commits in MSR dataset
import jsonlines
import tqdm

commit_ids = set()

with jsonlines.open("data/MSR/full_experiment_real_data_processed/MSR-line-ggnn.jsonlines") as f:
    for example in tqdm.tqdm(f, total=117325):
        commit_id = example["file_name"].split("_")[-3]
        commit_ids.add(commit_id)
len(commit_ids)