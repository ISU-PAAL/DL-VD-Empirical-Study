import copy
import traceback

import torch
from dgl import DGLGraph
from tqdm import tqdm

from data_loader.batch_graph import GGNNBatchGraph
from utils import load_default_identifiers, initialize_batch, debug
from pathlib import Path
import pandas as pd
import copy
import warnings
import jsonlines

class DataEntry:
    def __init__(self, _id, datset, num_nodes, features, edges, target, code=False, node_tokens=False, node_code=False):
        self._id = _id
        self.num_nodes = num_nodes
        self.target = target
        self.code=code
        self.node_tokens = node_tokens
        self.node_code = node_code
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

    def load_splits(self, all_src, splits_src):
        splits_df = pd.read_csv(splits_src)
        if "index" in splits_df.columns:
            splits = splits_df.set_index("index")["split"].to_dict()
        elif "combined" in all_src:
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

            new_splits = {}
            with jsonlines.open(all_src) as reader:
                for json_idx, entry in tqdm(enumerate(reader), desc="load json -> msr mapping"):
                    file_name = entry["file_name"]
                    if "_after_" in file_name:
                        print("skipped", file_name, "because _after_")
                        continue
                    dataset, real_file_name = file_name.split("/")
                    example_idx = int(real_file_name.split("_")[0])
                    if dataset == "Devign":
                        example_idx -= 1
                    source_idx = (dataset, example_idx)
                    try:
                        split_idx = splits[source_idx]
                    except KeyError:
                        missing_keys.append(source_idx)
                        continue
                    new_splits[json_idx] = split_idx
            splits = new_splits

            print(len(missing_keys), "keys missing from splits.csv")
            with open(missing_src, "w") as f:
                f.write("\n".join(str(m) for m in missing_keys))

        if "MSR" in all_src:
            missing_src = splits_src + ".missing.txt"
            missing_keys = []

            new_splits = {}
            with jsonlines.open(all_src) as reader:
                for json_idx, entry in tqdm(enumerate(reader), desc="load json -> msr mapping"):
                    file_name = entry["file_name"]
                    if "_after_" in file_name:
                        print("skipped", file_name, "because _after_")
                        continue
                    source_idx = int(file_name.split("_")[0])
                    try:
                        split_idx = splits[source_idx]
                    except KeyError:
                        missing_keys.append(source_idx)
                        continue
                    new_splits[json_idx] = split_idx
            splits = new_splits

            print(len(missing_keys), "keys missing from splits.csv")
            with open(missing_src, "w") as f:
                f.write("\n".join(str(m) for m in missing_keys))

        skipped_keys = 0
        for example in self.all_examples:
            json_idx = example._id
            if json_idx in splits:
                split_examples[splits[json_idx]].append(example)
            else:
                skipped_keys += 1
        print("skipped", skipped_keys, "keys")
        self.initialize_dataset()
        return splits

    def read_dataset(self, all_src):
        debug('Reading all data File!')
        with jsonlines.open(all_src) as reader:
            for i, entry in enumerate(tqdm(reader, desc="read data")):
                # print(entry.keys())
                # print(entry['node_code'])
                # print(entry['node_tokens'])
                # print(entr['bash'])
                print(entry.keys())
                # print(entry.keys(), self.g_ident, self.l_ident, entry['code'], entry['id'], entry['graph'], entry['file_path'])
                example = DataEntry(
                    _id=i,
                    datset=self,
                    num_nodes=len(entry[self.n_ident]),
                    features=entry[self.n_ident],
                    edges=entry[self.g_ident],
                    target=entry[self.l_ident][0][0],
                    code=entry['code'],
                    node_tokens=entry['node_tokens'],
                    node_code=entry['node_code'],
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
            batch_graph = GGNNBatchGraph()
            for entry in taken_entries:
                batch_graph.add_subgraph(copy.deepcopy(entry.graph))
            return batch_graph, torch.FloatTensor(labels), ids

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
