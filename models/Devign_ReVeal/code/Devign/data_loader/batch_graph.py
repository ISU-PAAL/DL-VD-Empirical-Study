import torch
import dgl

has_cuda = torch.cuda.is_available()


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