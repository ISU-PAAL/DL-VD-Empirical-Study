import argparse
import json
import os
import pickle
import random
import sys

import numpy as np
import pandas as pd
import torch
from torch.nn import BCELoss
from torch.optim import Adam
import dgl
import tqdm

from data_loader.dataset import DataSet
from modules.model import DevignModel, GGNNSum
from trainer import train, evaluate_metrics
from utils import tally_param, debug
import jsonlines


if __name__ == '__main__':
    torch.manual_seed(1000)
    np.random.seed(1000)
    parser = argparse.ArgumentParser()
    parser.add_argument('--model_type', type=str, help='Type of the model (devign/ggnn)',
                        choices=['devign', 'ggnn'], default='devign')
    parser.add_argument('--dataset', type=str, required=True, help='Name of the dataset for experiment.')
    parser.add_argument('--input_dir', type=str, required=True, help='Input Directory of the parser')
    parser.add_argument('--fold', required=True, help='Which fold of the dataset to load')
    parser.add_argument('--node_tag', type=str, help='Name of the node feature.', default='node_features')
    parser.add_argument('--graph_tag', type=str, help='Name of the graph feature.', default='graph')
    parser.add_argument('--label_tag', type=str, help='Name of the label feature.', default='target')
    parser.add_argument('--seed', type=int, default=0, required=True, help='Which fold of the dataset to load')

    parser.add_argument('--feature_size', type=int, help='Size of feature vector for each node', default=169)
    parser.add_argument('--graph_embed_size', type=int, help='Size of the Graph Embedding', default=200)
    parser.add_argument('--num_steps', type=int, help='Number of steps in GGNN', default=6)
    parser.add_argument('--batch_size', type=int, help='Batch Size for training', default=128)
    parser.add_argument('--train', action="store_true", help='Do training')
    parser.add_argument('--holdout', action="store_true", help='Do holdout')
    parser.add_argument('--holdout_test', action="store_true", help='Do holdout on test set')
    parser.add_argument('--no_cuda', action="store_true", help='Do not use cuda')
    parser.add_argument('--eval_export', action="store_true", help='Do eval_export (evaluate and export results by sample)')
    parser.add_argument('--save_after_ggnn', action="store_true", help='Evaluate all examples and export them')
    parser.add_argument('--stop_after_dataset', action="store_true", help='Stop after loading the dataset')
    parser.add_argument('--no_split', action="store_true", help='Do not split data')
    parser.add_argument('--model_bruh')
    parser.add_argument('--mega_cool_mode', action="store_true")
    parser.add_argument('--shport', action="store_true")
    args = parser.parse_args()

    # random seed all
    has_cuda = torch.cuda.is_available() and (args.no_cuda is False)
    random.seed(args.seed)
    np.random.seed(args.seed)
    torch.manual_seed(args.seed)
    if has_cuda:
        torch.cuda.manual_seed_all(args.seed)
        dgl.seed(args.seed)

    if args.feature_size > args.graph_embed_size:
        print('Warning!!! Graph Embed dimension should be at least equal to the feature dimension.\n'
              'Setting graph embedding size to feature size', file=sys.stderr)
        args.graph_embed_size = args.feature_size

    input_dir = args.input_dir
    processed_data_path = os.path.join(input_dir, 'processed.bin')
    all_src = os.path.join(input_dir, args.dataset + '-full_graph.jsonlines')
    if os.path.exists(processed_data_path):
        debug('Reading already processed data from %s!' % processed_data_path)
        dataset = pickle.load(open(processed_data_path, 'rb'))
    else:
        dataset = DataSet(all_src=all_src,
                          batch_size=args.batch_size,
                          n_ident=args.node_tag,
                          g_ident=args.graph_tag,
                          l_ident=args.label_tag,
                          dsname=args.dataset)
        file = open(processed_data_path, 'wb')
        pickle.dump(dataset, file)
        file.close()
    dataset.feature_size = dataset.all_examples[0].graph.ndata["features"].shape[1]
    dataset.batch_size = args.batch_size
    splits_dir = os.path.join(input_dir, f"v{args.fold}")
    if not args.no_split:
        print("loading splits from", os.path.join(splits_dir, 'splits.csv'))
        splits_reveal = dataset.load_splits(all_src, os.path.join(splits_dir, 'splits.csv'), args.mega_cool_mode, args.shport)
        debug(len(dataset.train_examples), len(dataset.valid_examples), len(dataset.test_examples), len(dataset.holdout_examples))
    assert args.feature_size == dataset.feature_size, \
        f'Dataset contains different feature vector size {dataset.feature_size} than argument feature size {args.feature_size}. ' \
        'Either change the feature vector size in argument, or provide different dataset.'
    if args.stop_after_dataset:
        exit()

    if args.model_type == 'ggnn':
        model = GGNNSum(input_dim=dataset.feature_size, output_dim=args.graph_embed_size,
                        num_steps=args.num_steps, max_edge_types=dataset.max_edge_type)
    else:
        model = DevignModel(input_dim=dataset.feature_size, output_dim=args.graph_embed_size,
                            num_steps=args.num_steps, max_edge_types=dataset.max_edge_type)

    print(f"model: {model}")
    debug('Total Parameters : %d' % tally_param(model))
    debug('#' * 100)
    if has_cuda:
        model.cuda()
    loss_function = BCELoss(reduction='sum')
    optim = Adam(model.parameters(), lr=0.0001, weight_decay=0.001)
    model_dir = os.path.join('models', args.dataset, args.model_type, f"v{args.fold}", str(args.seed))
    if args.train:
        if not os.path.exists(model_dir):
            os.makedirs(model_dir)
        assert has_cuda
        # train(model=model, dataset=dataset, max_steps=3, dev_every=1,
        train(model=model, dataset=dataset, max_steps=1000000, dev_every=64, log_every=None,
            loss_function=loss_function, optimizer=optim,
            save_path=model_dir + '/GGNNSumModel', max_patience=100)
    if args.holdout or args.holdout_test:
        assert args.holdout != args.holdout_test
        from sklearn.metrics import f1_score, precision_score, recall_score, accuracy_score
        if args.model_bruh:
            model_dir = args.model_bruh
        model_dir = model_dir.replace("_holdout", "")
        if "nondiverse" in model_dir:
            model_dir = model_dir[:-4] + model_dir[-2:]
        save_path = model_dir + '/GGNNSumModel' + '-model.bin'
        if has_cuda:
            map_location = None
        else:
            map_location = map_location=torch.device('cpu')
        print("loading weights for holdout", save_path)
        model.load_state_dict(torch.load(save_path, map_location=map_location))
        model.eval()

        # acc, pr, rc, f1 = evaluate_metrics(model, loss_function, dataset.initialize_holdout_batch(), dataset.get_next_holdout_batch)
        if args.holdout:
            nbatch = dataset.initialize_holdout_batch()
            nextbatch = dataset.get_next_holdout_batch
        elif args.holdout_test:
            nbatch = dataset.initialize_test_batch()
            nextbatch = dataset.get_next_test_batch
        model.eval()
        with torch.no_grad():
            _loss = []
            all_predictions, all_targets = [], []
            for _ in range(nbatch):
                graph, targets = nextbatch()
                if has_cuda:
                    targets = targets.cuda()
                predictions = model(graph, cuda=has_cuda)
                batch_loss = loss_function(predictions, targets)
                _loss.append(batch_loss.detach().cpu().item())
                predictions = predictions.detach().cpu()
                if predictions.ndim == 2:
                    all_predictions.extend(np.argmax(predictions.numpy(), axis=-1).tolist())
                else:
                    all_predictions.extend(
                        predictions.ge(torch.ones(size=predictions.size()).fill_(0.5)).to(
                            dtype=torch.int32).numpy().tolist()
                    )
                all_targets.extend(targets.detach().cpu().numpy().tolist())
            model.train()
            acc, pr, rc, f1 = accuracy_score(all_targets, all_predictions) * 100, \
                precision_score(all_targets, all_predictions) * 100, \
                recall_score(all_targets, all_predictions) * 100, \
                f1_score(all_targets, all_predictions) * 100

        debug('Holdout Accuracy: %0.2f\tPrecision: %0.2f\tRecall: %0.2f\tF1: %0.2f' % (acc, pr, rc, f1))
        debug('=' * 100)
    if args.eval_export:
        if args.model_bruh:
            model_dir = args.model_bruh
        save_path = model_dir + '/GGNNSumModel' + '-model.bin'
        if has_cuda:
            map_location = None
        else:
            map_location = map_location=torch.device('cpu')
        print("loading weights for eval_export", save_path)
        model.load_state_dict(torch.load(save_path, map_location=map_location))
        model.eval()
        with torch.no_grad():
            all_predictions, all_probs, all_targets, all_indices = [], [], [], []
            index_start = 0
            writer = None
            examples_written = 0
            if args.save_after_ggnn:
                if args.model_bruh:
                    mb = args.model_bruh.split('/')[-2]
                    ofp = os.path.join(splits_dir, f"GGNNinput_graph_{args.model_type}_{args.seed}_{mb}.jsonlines")
                else:
                    ofp = os.path.join(splits_dir, f"GGNNinput_graph_{args.model_type}_{args.seed}.jsonlines")
                print("outputting features to", ofp)
                writer = jsonlines.open(ofp, "w")
                with open(os.path.join(splits_dir, f"splits_reveal.json"), "w") as splits_f:
                    json.dump(splits_reveal, splits_f)
            num_batches = dataset.initialize_all_batch()
            all_batch_sequence = np.concatenate(dataset.all_batches)
            assert np.all(all_batch_sequence == np.arange(0, len(dataset.all_examples), 1)), "batches out of order"
            for batch_i in tqdm.tqdm(range(num_batches), desc="pass through data"):
                graphs, targets = dataset.get_next_all_batch()
                targets = targets.detach().int().cpu().numpy().tolist()

                # get model outputs
                batch_indices = range(index_start, index_start + len(targets))
                if args.save_after_ggnn:
                    probs, features = model(graphs, cuda=True, save_after_ggnn=True)
                    features = features.detach().cpu().numpy().tolist()
                    for i, (feature, target) in enumerate(zip(features, targets)):
                        writer.write({
                            "graph_feature": feature,
                            "target": target,
                        })
                        examples_written += 1
                else:
                    probs = model(graphs, cuda=True, save_after_ggnn=False)
                probs = probs.detach().cpu()

                # get binary prediction
                if probs.ndim == 2:
                    predictions = np.argmax(probs.numpy(), axis=-1).tolist()
                else:
                    predictions = probs.ge(torch.ones(size=probs.size()).fill_(0.5)).to(dtype=torch.int32).numpy().tolist()
                all_predictions.extend(predictions)

                all_probs.extend(probs.numpy().tolist())
                all_targets.extend(targets)
                all_indices.extend(batch_indices)
                index_start += len(targets)
            all_correct = (np.array(all_predictions) == np.array(all_targets)).tolist()

            print(examples_written, "eexamples_written")
            assert len(all_indices) == len(all_correct), (len(all_indices), len(all_correct))
            assert len(all_correct) == len(all_predictions), (len(all_correct), len(all_predictions))
            assert len(all_predictions) == len(all_targets), (len(all_predictions), len(all_targets))
            assert len(all_targets) == len(all_probs), (len(all_targets), len(all_probs))

            if writer is not None:
                writer.close()

            df = pd.DataFrame(data={
                "prediction": all_predictions,
                "prob": all_probs,
                "target": all_targets,
            }, index=all_indices)
            df = df.reset_index().sort_values("index")
            if args.model_bruh:
                df.to_csv(os.path.join(splits_dir, f"eval_export_{args.model_type}_{args.seed}_{args.model_bruh.replace('/', '-')}.csv"))
            else:
                df.to_csv(os.path.join(splits_dir, f"eval_export_{args.model_type}_{args.seed}.csv"))
