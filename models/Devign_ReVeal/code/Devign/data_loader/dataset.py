import torch
from dgl import DGLGraph
from tqdm import tqdm

import dgl
from utils import load_default_identifiers, initialize_batch, debug
from pathlib import Path
import pandas as pd
import copy
import warnings
import jsonlines
import json
import itertools

class DataEntry:
    def __init__(self, _id, datset, num_nodes, features, edges, target):
        self._id = _id
        self.num_nodes = num_nodes
        self.target = target
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            self.graph = DGLGraph()
        self.graph.add_nodes(
            self.num_nodes,
            data={'features': torch.FloatTensor(features)}
        )
        for s, _type, t in edges:
            etype_number = datset.get_edge_type_number(_type)
            with warnings.catch_warnings():
                warnings.simplefilter("ignore")
                self.graph.add_edge(s, t, data={'etype': torch.LongTensor([etype_number])})


class DataSet:
    def __init__(self, all_src, batch_size=32, n_ident=None, g_ident=None, l_ident=None, dsname=None):
        self.all_examples = []
        self.train_examples = []
        self.valid_examples = []
        self.test_examples = []
        self.holdout_examples = []

        self.all_batches = []
        self.train_batches = []
        self.valid_batches = []
        self.test_batches = []
        self.holdout_batches = []
        
        self.batch_size = batch_size
        self.edge_types = {}
        self.max_etype = 0
        self.feature_size = 0
        self.dsname = dsname
        self.n_ident, self.g_ident, self.l_ident= load_default_identifiers(n_ident, g_ident, l_ident)
        self.read_dataset(all_src)

    def initialize_dataset(self):
        self.initialize_train_batch()
        self.initialize_valid_batch()
        self.initialize_test_batch()

    def load_splits(self, all_src, splits_src, mega_cool_mode, shport):
        splits_df = pd.read_csv(splits_src)
        if "index" in splits_df.columns:
            splits = splits_df.set_index("index")["split"].to_dict()
        elif "combined" in all_src:
            if mega_cool_mode:
                if "version" not in splits_df.columns:
                    print("adding dummy version")
                splits_df["version"] = "before"
                splits = splits_df.fillna("before").set_index(["dataset", "idx", "version"])["split"].to_dict()
            else:
                splits = splits_df.set_index(["dataset", "example_index"])["split"].to_dict()
        else:
            splits = splits_df.set_index("example_index")["split"].to_dict()
        split_examples = {
            "train": self.train_examples,
            "valid": self.valid_examples,
            "test": self.test_examples,
            "holdout": self.holdout_examples,
        }

        if "combined" in all_src:
            missing_src = splits_src + ".missing.txt"
            missing_keys = []
            after_src = splits_src + ".after.txt"
            after_keys = []

            new_splits = {}
            with jsonlines.open(all_src) as reader:
                if shport:
                    reader = itertools.islice(reader, 1000)
                print("load json -> msr mapping...")
                for json_idx, entry in enumerate(reader):
                    file_name = entry["file_name"]
                    version = "before"
                    if "_after_" in file_name:
                        version = "after"
                    if version == "after" and not mega_cool_mode:
                        after_keys.append((json_idx, file_name))
                        continue
                    dataset, real_file_name = file_name.split("/")
                    example_idx = int(real_file_name.split("_")[0])
                    if dataset == "Devign":
                        example_idx -= 1
                    if mega_cool_mode:
                        source_idx = (dataset, example_idx, version)
                    else:
                        source_idx = (dataset, example_idx)
                    try:
                        split_idx = splits[source_idx]
                    except KeyError:
                        missing_keys.append(source_idx)
                        continue
                    new_splits[json_idx] = split_idx
                print("done loading json -> msr mapping")
                if shport:
                    print(json.dumps(new_splits))
            splits = new_splits

            print(len(missing_keys), "keys missing from splits.csv")
            with open(missing_src, "w") as f:
                f.write("\n".join(str(m) for m in missing_keys))

            print(len(after_keys), "keys skipped because _after_")
            with open(after_src, "w") as f:
                f.write("\n".join(",".join([str(mm) for mm in m]) for m in after_keys))

        if "MSR" in all_src:
            missing_src = splits_src + ".missing.txt"
            missing_keys = []
            after_src = splits_src + ".after.txt"
            after_keys = []

            new_splits = {}
            with jsonlines.open(all_src) as reader:
                print("load json -> msr mapping...")
                for json_idx, entry in enumerate(reader):
                    file_name = entry["file_name"]
                    if "_after_" in file_name:
                        after_keys.append((json_idx, file_name))
                        continue
                    source_idx = int(file_name.split("_")[0])
                    try:
                        split_idx = splits[source_idx]
                    except KeyError:
                        missing_keys.append(source_idx)
                        continue
                    new_splits[json_idx] = split_idx
                print("done loading json -> msr mapping")
            splits = new_splits

            print(len(missing_keys), "keys missing from splits.csv")
            with open(missing_src, "w") as f:
                f.write("\n".join(str(m) for m in missing_keys))

            print(len(after_keys), "keys skipped because _after_")
            with open(after_src, "w") as f:
                f.write("\n".join(",".join([str(mm) for mm in m]) for m in after_keys))

        print("splits:", json.dumps(splits))
        splits_reveal = {}
        skipped_keys = 0
        printed_keys = 0
        for i, example in enumerate(self.all_examples):
            json_idx = example._id
            if json_idx in splits:
                split_examples[splits[json_idx]].append(example)
                splits_reveal[i] = splits[json_idx]
                if printed_keys < 10:
                    print("PRINTING DEBUG", printed_keys, json_idx, splits[json_idx], example._id, example.num_nodes, example.target, example.graph)
                    printed_keys += 1
            else:
                skipped_keys += 1
        print("skipped", skipped_keys, "keys")
        self.initialize_dataset()
        return splits_reveal

    def read_dataset(self, all_src):
        debug('Reading all data File!')
        with jsonlines.open(all_src) as reader:
            for i, entry in enumerate(tqdm(reader, desc="read data")):
                example = DataEntry(
                    _id=i,
                    datset=self,
                    num_nodes=len(entry[self.n_ident]),
                    features=entry[self.n_ident],
                    edges=entry[self.g_ident],
                    target=entry[self.l_ident][0][0],
                    )
                self.all_examples.append(example)

    def get_edge_type_number(self, _type):
        if _type not in self.edge_types:
            self.edge_types[_type] = self.max_etype
            self.max_etype += 1
        return self.edge_types[_type]

    @property
    def max_edge_type(self):
        return self.max_etype

    def initialize_train_batch(self, batch_size=-1):
        if batch_size == -1:
            batch_size = self.batch_size
        self.train_batches = initialize_batch(self.train_examples, batch_size, shuffle=True)
        return len(self.train_batches)
        pass

    def initialize_valid_batch(self, batch_size=-1):
        if batch_size == -1:
            batch_size = self.batch_size
        self.valid_batches = initialize_batch(self.valid_examples, batch_size)
        return len(self.valid_batches)
        pass

    def initialize_test_batch(self, batch_size=-1):
        if batch_size == -1:
            batch_size = self.batch_size
        self.test_batches = initialize_batch(self.test_examples, batch_size)
        return len(self.test_batches)
        pass

    def initialize_holdout_batch(self, batch_size=-1):
        if batch_size == -1:
            batch_size = self.batch_size
        self.holdout_batches = initialize_batch(self.holdout_examples, batch_size)
        return len(self.holdout_batches)
        pass

    def initialize_all_batch(self, batch_size=-1):
        if batch_size == -1:
            batch_size = self.batch_size
        self.all_batches = initialize_batch(self.all_examples, batch_size)
        return len(self.all_batches)
        pass

    def get_dataset_by_ids_for_GGNN(self, entries, ids, use_cache=False):
        unique_ids = ",".join(map(str, sorted(set(ids))))
        if use_cache and unique_ids in self.batch_cache:
            return self.batch_cache[unique_ids]
        else:
            taken_entries = [entries[i] for i in ids]
            labels = [e.target for e in taken_entries]
            batch_graph = dgl.batch([entry.graph for entry in taken_entries])
            return batch_graph, torch.FloatTensor(labels)

    def get_next_train_batch(self):
        if len(self.train_batches) == 0:
            self.initialize_train_batch()
        ids = self.train_batches.pop(0)
        return self.get_dataset_by_ids_for_GGNN(self.train_examples, ids)

    def get_next_valid_batch(self):
        if len(self.valid_batches) == 0:
            self.initialize_valid_batch()
        ids = self.valid_batches.pop(0)
        return self.get_dataset_by_ids_for_GGNN(self.valid_examples, ids)

    def get_next_test_batch(self):
        if len(self.test_batches) == 0:
            self.initialize_test_batch()
        ids = self.test_batches.pop(0)
        return self.get_dataset_by_ids_for_GGNN(self.test_examples, ids)

    def get_next_holdout_batch(self):
        if len(self.holdout_batches) == 0:
            self.initialize_test_batch()
        ids = self.holdout_batches.pop(0)
        return self.get_dataset_by_ids_for_GGNN(self.holdout_examples, ids)

    def get_next_all_batch(self):
        if len(self.all_batches) == 0:
            self.initialize_all_batch()
        ids = self.all_batches.pop(0)
        return self.get_dataset_by_ids_for_GGNN(self.all_examples, ids)

def test_ds():
    ds = DataSet(Path("data/line_ggnn/devign/v1/train_GGNNinput.json"),
                          n_ident='node_features',
                          g_ident='graph',
                          l_ident='targets',
                          dsname="devign")
    assert ds.feature_size == ds.train_examples[0].ndata["features"].shape[1]
    assert ds.max_edge_type == max(g.edata["etype"].max().item() for g in (ds.train_examples + ds.valid_examples + ds.test_examples))
