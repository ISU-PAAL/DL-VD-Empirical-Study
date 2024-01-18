#%%
import jsonlines
import numpy as np
import more_itertools as mit
from tqdm import auto as tqdm
import itertools

# with jsonlines.open("data/MSR_export_code/full_experiment_real_data/data.jsonlines") as export_code_reader, jsonlines.open("data/MSR/full_experiment_real_data/data.jsonlines") as orig_reader:
with jsonlines.open("data/MSR_export_code/full_experiment_real_data_processed/MSR_export_code-full_graph.jsonlines") as export_code_reader, jsonlines.open("data/MSR/full_experiment_real_data_processed/MSR-full_graph.jsonlines") as orig_reader:
    for i, (ec, o) in itertools.islice(tqdm.tqdm(enumerate(mit.zip_equal(export_code_reader, orig_reader))), 100):
        assert ec["file_name"] == o["file_name"]
        assert ec["file_path"] == o["file_path"]
        assert ec["id"] == o["id"]
        # assert ec["graph"] == o["graph"], (ec["graph"], o["graph"])
        assert ec["targets"] == o["targets"]
        # assert list(ec.keys()) == list(o.keys())
        # assert list(ec["full_graph"].keys()) == list(o["full_graph"].keys()), (list(ec["full_graph"].keys()), list(o["full_graph"].keys()))
        ec_f = np.array(ec["node_code"])
        ec_f = np.array(ec["node_features"])
        o_f = np.array(o["node_features"])
        match_found = []
        empty_feat = []
        for erow in ec_f:
            row_match_found = False
            for orow in o_f:
                # print(np.sum(erow))
                if np.sum(erow) == 1.0:
                    print("oof")
                if np.all(erow == orow):
                    # print("match")
                    # print(erow)
                    # print(orow)
                    row_match_found = True
            match_found.append(row_match_found)
        assert np.all(match_found)
                    
        # print(ec_f, o_f)
        assert len(ec_f) == len(o_f), i
        # print(ec_f)
        # print(o_f)
        # assert np.all(ec_f == o_f), (ec_f, o_f)        

#%%
with jsonlines.open("data/MSR_export_code/full_experiment_real_data_processed/MSR_export_code-full_graph-code_only.jsonlines", "w") as of, jsonlines.open("data/MSR_export_code/full_experiment_real_data_processed/MSR_export_code-full_graph.jsonlines", "r") as inf:
    for example in tqdm.tqdm(inf):
        del example["node_features"]
        of.write(example)
