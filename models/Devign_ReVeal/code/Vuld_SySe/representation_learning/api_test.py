import argparse
import json
import random
import numpy as np
import pandas as pd

from sklearn.metrics import accuracy_score, f1_score, precision_score, recall_score
from Vuld_SySe.representation_learning.graph_dataset import DataSet
import numpy
import os
import sys
import torch
from representation_learning_api import RepresentationLearningModel
from models import MetricLearningModel
from trainer import evaluate
from baseline_svm import SVMLearningAPI
import jsonlines
import tqdm

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--features', default='ggnn', choices=['ggnn', 'wo_ggnn'])
    parser.add_argument('--lambda1', default=0.5, type=float)
    parser.add_argument('--lambda2', default=0.001, type=float)
    parser.add_argument('--num_epoch', default=100, type=int)
    parser.add_argument('--baseline', action='store_true')
    parser.add_argument('--baseline_balance', action='store_true')
    parser.add_argument('--baseline_model', default='svm')
    parser.add_argument('--num_layers', default=1, type=int)
    parser.add_argument('--input_dir', type=str, required=True, help='Input Directory of the parser')
    parser.add_argument('--fold')
    parser.add_argument('--seed', type=int)
    parser.add_argument('--train', action='store_true')
    parser.add_argument('--eval_export', action='store_true')
    parser.add_argument('--holdout', action='store_true')
    parser.add_argument('--holdout_test', action="store_true", help='Do holdout on test set')
    parser.add_argument('--features_bruh')
    parser.add_argument('--model_bruh')
    args = parser.parse_args()
        
    # random seed all
    has_cuda = torch.cuda.is_available()
    print("cuda:", has_cuda)
    random.seed(args.seed)
    np.random.seed(args.seed)
    torch.manual_seed(args.seed)
    if has_cuda:
        torch.cuda.manual_seed_all(args.seed)

    feature_name = args.features
    ds = os.path.join(args.input_dir, f"v{args.fold}")
    assert os.path.exists(ds), ds

    ds_indexes = []
    splits = []
    features = []
    targets = []
    if args.features_bruh:
        json_data_file = os.path.join(ds, f'GGNNinput_graph_ggnn_{args.seed}_{args.features_bruh}.jsonlines')
    else:
        json_data_file = os.path.join(ds, f'GGNNinput_graph_ggnn_{args.seed}.jsonlines')
    print("load data from", json_data_file)
    with jsonlines.open(json_data_file) as reader:
        for i, d in enumerate(reader):
            features.append(d['graph_feature'])
            targets.append(d['target'])
            ds_indexes.append(i)
    X = numpy.array(features)
    Y = numpy.array(targets)
    ds_indexes = numpy.array(ds_indexes)
    print('Dataset', X.shape, Y.shape, numpy.sum(Y), sep='\t', file=sys.stderr)
    print('=' * 100, file=sys.stderr, flush=True)

    splits_dir = ds
    indices = {}
    for split in ["train", "valid", "test", "holdout"]:
        if split not in indices:
            indices[split] = []
    with open(os.path.join(splits_dir, 'splits_reveal.json')) as f:
        splits_tuples = json.load(f)
        for i, split in splits_tuples.items():
            indices[split].append(int(i))

    train_X, train_Y, train_indices = X[indices["train"]], Y[indices["train"]], ds_indexes[indices["train"]]
    valid_X, valid_Y, valid_indices = X[indices["valid"]], Y[indices["valid"]], ds_indexes[indices["valid"]]
    test_X, test_Y, test_indices = X[indices["test"]], Y[indices["test"]], ds_indexes[indices["test"]]
    holdout_X, holdout_Y, holdout_indices = X[indices["holdout"]], Y[indices["holdout"]], ds_indexes[indices["holdout"]]
    print(
        "train", train_X.shape, train_Y.shape, len(indices["train"]),
        "valid", valid_X.shape, valid_Y.shape, len(indices["valid"]),
        "test", test_X.shape, test_Y.shape, len(indices["test"]),
        "holdout", holdout_X.shape, holdout_Y.shape, len(indices["holdout"]),
        sep='\n', file=sys.stderr, flush=True
    )

    model_dir = os.path.join("models", "devign", "reveal", os.path.basename(ds), str(args.seed))
    print("checkpointing path:", model_dir)

    if args.train:
        os.makedirs(model_dir, exist_ok=True)
        output_dir = 'results_test'
        if args.baseline:
            output_dir = 'baseline_' + args.baseline_model
            if args.baseline_balance:
                output_dir += '_balance'
        if not os.path.exists(output_dir):
            os.mkdir(output_dir)
        if args.lambda1 == 0:
            assert args.lambda2 == 0

        if args.baseline:
            model = SVMLearningAPI(True, args.baseline_balance, model_type=args.baseline_model)
        else:
            model = RepresentationLearningModel(
                lambda1=args.lambda1, lambda2=args.lambda2, batch_size=128, max_patience=5, balance=True,
                num_layers=args.num_layers, num_epoch=args.num_epoch,
            )
        model.train(train_X, train_Y, valid_X, valid_Y, model_dir)
        results = model.evaluate(test_X, test_Y)
        print("TEST RESULTS")
        print(results['accuracy'], results['precision'], results['recall'], results['f1'])

    if args.holdout or args.holdout_test:
        assert args.holdout != args.holdout_test
        model = MetricLearningModel(
            input_dim=train_X.shape[1], hidden_dim=256, aplha=0.5, dropout_p=0.2,
            lambda1=args.lambda1, lambda2=args.lambda2, num_layers=args.num_layers
        )
        if args.model_bruh:
            model_dir = args.model_bruh
        my_model_dir = model_dir.replace("_holdout", "")
        if "nondiverse" in my_model_dir:
            my_model_dir = my_model_dir[:-4] + my_model_dir[-2:]
        save_path = os.path.join(my_model_dir, "RepresentationLearningModel.bin")
        model.load_state_dict(torch.load(save_path))
        model = model.cuda()
        model.eval()

        if args.holdout:
            X = holdout_X
            Y = holdout_Y
            indices = holdout_indices
            name = "holdout"
        elif args.holdout_test:
            X = test_X
            Y = test_Y
            indices = test_indices
            name = "test"

        dataset = DataSet(64, X.shape[1], shuffle=False, with_index=False)
        for _x, _y, _index in zip(X, Y, indices):
            dataset.add_data_entry(_x.tolist(), _y.item(), name, _index)
        dataset.initialize_dataset(balance=False)

        if args.holdout:
            nbatch = dataset.initialize_holdout_batches()
            nextbatch = dataset.get_next_holdout_batch
        elif args.holdout_test:
            nbatch = dataset.initialize_test_batches()
            nextbatch = dataset.get_next_test_batch
        acc, pr, rc, f1 = evaluate(
            model=model, iterator_function=nextbatch,
            _batch_count=nbatch, cuda_device=0,
        )
        print("HOLDOUT RESULTS")
        print(acc, pr, rc, f1)

    if args.eval_export:
        model = MetricLearningModel(
            input_dim=train_X.shape[1], hidden_dim=256, aplha=0.5, dropout_p=0.2,
            lambda1=args.lambda1, lambda2=args.lambda2, num_layers=args.num_layers
        )
        if args.model_bruh:
            model_dir = args.model_bruh
        save_path = os.path.join(model_dir, "RepresentationLearningModel.bin")
        model.load_state_dict(torch.load(save_path))
        model.eval()

        dataset = DataSet(64, train_X.shape[1], shuffle=False, with_index=True)
        for _x, _y, _index in zip(train_X, train_Y, train_indices):
            dataset.add_data_entry(_x.tolist(), _y.item(), 'train', _index)
        for _x, _y, _index in zip(valid_X, valid_Y, valid_indices):
            dataset.add_data_entry(_x.tolist(), _y.item(), 'valid', _index)
        for _x, _y, _index in zip(test_X, test_Y, test_indices):
            dataset.add_data_entry(_x.tolist(), _y.item(), 'test', _index)
        for _x, _y, _index in zip(holdout_X, holdout_Y, holdout_indices):
            dataset.add_data_entry(_x.tolist(), _y.item(), 'holdout', _index)
        dataset.initialize_dataset(balance=False)

        with torch.no_grad():
            all_predictions, all_probs, all_targets, splitnames, all_indices = [], [], [], [], []
            for splitname, num_batches, data_iter in [
                ("train", dataset.initialize_train_batches(), dataset.get_next_train_batch),
                ("valid", dataset.initialize_valid_batches(), dataset.get_next_valid_batch),
                ("test", dataset.initialize_test_batches(), dataset.get_next_test_batch),
                ("holdout", dataset.initialize_holdout_batches(), dataset.get_next_holdout_batch),
                ]:
                split_predictions, split_targets = [], []
                for i in tqdm.tqdm(range(num_batches), desc=splitname):
                    data = data_iter()
                    if i == 0 or i == num_batches - 1:
                        print(f"{splitname} i: {i}, data: {data[2]}")
                    features, targets, indices = data[:3]
                    predictions, _, _ = model(example_batch=features)

                    probs = predictions[:, 1].detach().cpu().numpy().tolist()
                    predictions = numpy.argmax(predictions.detach().cpu().numpy(), axis=-1).tolist()
                    targets = targets.int().detach().cpu().numpy().tolist()
                    indices = indices.int().detach().cpu().numpy().tolist()

                    all_probs.extend(probs)
                    all_predictions.extend(predictions)
                    all_targets.extend(targets)
                    all_indices.extend(indices)

                    split_predictions.extend(predictions)
                    split_targets.extend(targets)

                    splitnames.extend([splitname] * len(targets))

                print(splitname, len(split_predictions), "items")
                if len(split_predictions) > 0:
                    print(splitname, "accuracy_score", accuracy_score(split_predictions, split_targets))
                    print(splitname, "precision_score", precision_score(split_predictions, split_targets))
                    print(splitname, "recall_score", recall_score(split_predictions, split_targets))
                    print(splitname, "f1_score", f1_score(split_predictions, split_targets))

            correct = (numpy.array(all_predictions) == numpy.array(all_targets)).tolist()
            assert len(all_indices) == len(splitnames), (len(all_indices), len(splitnames))
            assert len(splitnames) == len(correct), (len(splitnames), len(correct))
            assert len(correct) == len(all_predictions), (len(correct), len(all_predictions))
            assert len(all_predictions) == len(all_targets), (len(all_predictions), len(all_targets))
            assert len(all_targets) == len(all_probs), (len(all_targets), len(all_probs))

            df = pd.DataFrame(data={
                "prediction": all_predictions,
                "prob": all_probs,
                "target": all_targets,
            }, index=all_indices)
            df = df.reset_index().sort_values("index")
            if args.model_bruh:
                df.to_csv(os.path.join(splits_dir, f"eval_export_reveal_{args.seed}_{args.model_bruh.replace('/', '-')}.csv"))
            else:
                df.to_csv(os.path.join(splits_dir, f"eval_export_reveal_{args.seed}.csv"))
