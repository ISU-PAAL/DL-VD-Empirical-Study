#%%
import json
import os

with open("data/MSR/full_data_with_slices.json") as msr, open("data/devign/full_data_with_slices.json") as devign, open("data/combined/full_data_with_slices.json", "w") as combined:
    msr_data = json.load(msr)
    devign_data = json.load(devign)
    all_data = []
    for d in msr_data:
        d["dataset"] = "MSR"
        d["file_name"] = "MSR/" + os.path.basename(d["file_path"])
        all_data.append(d)
    for d in devign_data:
        d["dataset"] = "Devign"
        d["file_name"] = "Devign/" + os.path.basename(d["file_path"])
        all_data.append(d)
    json.dump(msr_data + devign_data, combined)
