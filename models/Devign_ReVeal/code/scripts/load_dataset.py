"""
Try to load the dataset for Devign model in order to test it interactively.
"""

#%%
import sys
sys.path.append("Devign")

#%%
import pickle
processed_data_path = "data/combined/full_experiment_real_data_processed/processed.bin"
dataset = pickle.load(open(processed_data_path, 'rb'))

# %%
import os
all_src = "data/combined/full_experiment_real_data_processed/combined-full_graph.jsonlines"
splits_dir = "data/combined/full_experiment_real_data_processed/vimbalanced"
dataset.load_splits(all_src, os.path.join(splits_dir, 'splits.csv'))

#%%
len(dataset.train_examples)

#%%

from dgl.nn import GatedGraphConv
ggnn = GatedGraphConv(in_feats=169, out_feats=200, n_steps=6, n_etypes=dataset.max_edge_type)
ggnn = ggnn.cuda()
# taken_entries = dataset.train_examples[:5]

#%% model.py inside GGNN forward()

import torch
from dgl import DGLGraph
import warnings

has_cuda = torch.cuda.is_available()

class BatchGraph:
    def __init__(self):
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            self.graph = DGLGraph()
        self.number_of_nodes = 0
        self.graphid_to_nodeids = {}
        self.num_of_subgraphs = 0

    def add_subgraph(self, _g):
        assert isinstance(_g, DGLGraph)
        num_new_nodes = _g.number_of_nodes()
        self.graphid_to_nodeids[self.num_of_subgraphs] = torch.LongTensor(
            list(range(self.number_of_nodes, self.number_of_nodes + num_new_nodes)))
        self.graph.add_nodes(num_new_nodes, data=_g.ndata)
        sources, dests = _g.all_edges()
        sources += self.number_of_nodes
        dests += self.number_of_nodes
        self.graph.add_edges(sources, dests, data=_g.edata)
        self.number_of_nodes += num_new_nodes
        self.num_of_subgraphs += 1

    def cuda(self, device=None):
        self.graph = self.graph.to(device)
        for k in self.graphid_to_nodeids.keys():
            self.graphid_to_nodeids[k] = self.graphid_to_nodeids[k].cuda(device=device)

    def de_batchify_graphs(self, features=None):
        if features is None:
            features = self.graph.ndata['features']
        assert isinstance(features, torch.Tensor)
        vectors = [features.index_select(dim=0, index=self.graphid_to_nodeids[gid]) for gid in
                   self.graphid_to_nodeids.keys()]
        lengths = [f.size(0) for f in vectors]
        max_len = max(lengths)
        for i, v in enumerate(vectors):
            vectors[i] = torch.cat(
                (v, torch.zeros(size=(max_len - v.size(0), *(v.shape[1:])), requires_grad=v.requires_grad,
                                device=v.device)), dim=0)
        output_vectors = torch.stack(vectors)
        lengths = torch.LongTensor(lengths).to(device=output_vectors.device)
        return output_vectors, lengths

    def get_network_inputs(self, cuda=False):
        raise NotImplementedError('Must be implemented by subclasses.')

    #def to(self, device):
    #self.graph = self.graph.to(device)


class GGNNBatchGraph(BatchGraph):
    def get_network_inputs(self, cuda=False, device=None):
        features = self.graph.ndata['features']
        edge_types = self.graph.edata['etype']
        if cuda and has_cuda:
            self.cuda(device=device)
            return self.graph, features.cuda(device=device), edge_types.cuda(device=device)
        else:
            return self.graph, features, edge_types

# Check that new and old batching methods are equivalent
#%%
import itertools
import tqdm.auto as tqdm
def grouper(n, iterable):
    it = iter(iterable)
    while True:
        chunk = tuple(itertools.islice(it, n))
        if not chunk:
            return
        yield chunk
chunks = grouper(100, dataset.train_examples)
for taken_entries in itertools.islice(tqdm.tqdm(chunks), 25):
    # old method - manual batch
    # taken_entries = list(itertools.islice(it, 100))
    import copy
    batch1 = GGNNBatchGraph()
    for entry in taken_entries:
        batch1.add_subgraph(copy.deepcopy(entry.graph))

    graph1, features1, edge_types1 = batch1.get_network_inputs(cuda=True, device="cuda:0")
    outputs1 = ggnn(graph1, features1, edge_types1)
    h1, _ = batch1.de_batchify_graphs(outputs1)
    # print(h1)

    # new method - dgl.batch
    import dgl

    def get_network_inputs(graph, cuda=False, device=None):
        features = graph.ndata['features']
        edge_types = graph.edata['etype']
        if cuda and has_cuda:
            graph = graph.to(device)
            features = features.cuda(device=device)
            edge_types = edge_types.cuda(device=device)
        return graph, features, edge_types

    def de_batchify_graphs(graph, features=None):
        graph.ndata["features"] = features
        graphs = dgl.unbatch(graph)
        vectors = [g.ndata['features'] for g in graphs]
        lengths = [f.size(0) for f in vectors]
        max_len = max(lengths)
        for i, v in enumerate(vectors):
            vectors[i] = torch.cat(
                (v, torch.zeros(size=(max_len - v.size(0), *(v.shape[1:])), requires_grad=v.requires_grad,
                                device=v.device)), dim=0)
        output_vectors = torch.stack(vectors)
        return output_vectors


    batch2 = dgl.batch([entry.graph for entry in taken_entries])
    graph2, features2, edge_types2 = get_network_inputs(batch2, cuda=True, device="cuda:0")
    outputs = ggnn(graph2, features2, edge_types2)
    h2 = de_batchify_graphs(graph2, outputs)
    # print(h2)tqdm.tqdm(chunks)
    assert torch.all(h1 == h2)
