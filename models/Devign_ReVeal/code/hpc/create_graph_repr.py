import json
files = ['test_GGNNinput.json', 'valid_GGNNinput.json', 'train_GGNNinput.json']
import numpy as np
import os

if not os.path.exists('graph_features'):
    os.mkdir('graph_features')

for file in files:
    new_data = []
    data = json.load(open(file))
    for d in data:
        node_features = np.array(d['node_features'])
        graph_features = np.sum(node_features, axis=0).tolist()
        target = int(d['targets'][0][0])
        new_data.append({
            'graph_feature': graph_features,
            'target': target
        })
    fp = open(os.path.join('graph_features', file), 'w')
    json.dump(new_data, fp)
    fp.close()
    print(file)
