import sys

import numpy as np
import torch
import json
from imblearn.over_sampling import SMOTE
import tqdm


class DataEntry:
    def __init__(self, dataset, feature_repr, label, meta_data=None, index=None):
        self.dataset = dataset
        assert isinstance(self.dataset, DataSet)
        self.features = feature_repr
        self.label = label
        self.meta_data = meta_data
        self.index = index
        pass

    def __repr__(self):
        return str(self.features) + '\t' + str(self.label)

    def __hash__(self):
        return str(self.features).__hash__

    def is_positive(self):
        return self.label == 1


class DataSet:
    def __init__(self, batch_size, hdim, shuffle=True, with_index=False):
        self.train_entries = []
        self.valid_entries = []
        self.test_entries = []
        self.holdout_entries = []
        self.train_batch_indices = []
        self.valid_batch_indices = []
        self.test_batch_indices = []
        self.holdout_batch_indices = []
        self.batch_size = batch_size
        self.hdim = hdim
        self.positive_indices_in_train = []
        self.negative_indices_in_train = []
        self.with_index = with_index
        self.shuffle = shuffle

    def initialize_dataset(self, balance=True):
        print("Initializing dataset...")
        if isinstance(balance, bool) and balance:
            entries = []
            train_features = []
            train_targets = []
            for entry in self.train_entries:
                train_features.append(entry.features)
                train_targets.append(entry.label)
            train_features = np.array(train_features)
            train_targets = np.array(train_targets)
            smote = SMOTE(random_state=1000)
            features, targets = smote.fit_resample(train_features, train_targets)
            for feature, target in tqdm.tqdm(zip(features, targets), total=features.shape[0], desc="smoting features"):
                entries.append(DataEntry(self, feature.tolist(), target.item()))
            self.train_entries = entries
        elif isinstance(balance, list) and len(balance) == 2:
            entries = []
            for entry in self.train_entries:
                if entry.is_positive():
                    for _ in range(balance[0]):
                        entries.append(
                            DataEntry(self, entry.features, entry.label, entry.meta_data)
                        )
                else:
                    if np.random.uniform() <= balance[1]:
                        entries.append(
                            DataEntry(self, entry.features, entry.label, entry.meta_data)
                        )
            self.train_entries = entries
            pass
        for tidx, entry in enumerate(self.train_entries):
            if entry.label == 1:
                self.positive_indices_in_train.append(tidx)
            else:
                self.negative_indices_in_train.append(tidx)
        self.positive_indices_in_train = np.array(self.positive_indices_in_train)
        self.negative_indices_in_train = np.array(self.negative_indices_in_train)
        self.initialize_train_batches()
        print('Number of Train Entries %d #Batches %d first 5: %s last 5: %s' % \
                (len(self.train_entries), len(self.train_batch_indices), [e.index for e in self.train_entries[:5]], [e.index for e in self.train_entries[-5:]]))
        self.initialize_valid_batches()
        print('Number of Valid Entries %d #Batches %d first 5: %s last 5: %s' % \
                (len(self.valid_entries), len(self.valid_batch_indices), [e.index for e in self.valid_entries[:5]], [e.index for e in self.valid_entries[-5:]]))
        self.initialize_test_batches()
        print('Number of Test Entries %d #Batches %d first 5: %s last 5: %s' % \
                (len(self.test_entries), len(self.test_batch_indices), [e.index for e in self.test_entries[:5]], [e.index for e in self.test_entries[-5:]]))
        self.initialize_holdout_batches()
        print('Number of Holdout Entries %d #Batches %d first 5: %s last 5: %s' % \
                (len(self.holdout_entries), len(self.holdout_batch_indices), [e.index for e in self.holdout_entries[:5]], [e.index for e in self.holdout_entries[-5:]]))

    def add_data_entry(self, feature, label, part='train', index=None):
        assert part in ['train', 'valid', 'test', 'holdout']
        if self.with_index:
            assert index is not None
        entry = DataEntry(self, feature, label, index=index)
        if part == 'train':
            self.train_entries.append(entry)
        elif part == 'valid':
            self.valid_entries.append(entry)
        elif part == 'test':
            self.test_entries.append(entry)
        elif part == 'holdout':
            self.holdout_entries.append(entry)
        else:
            raise NotImplementedError(part)

    def initialize_train_batches(self):
        self.train_batch_indices = self.create_batches(self.batch_size, self.train_entries)
        return len(self.train_batch_indices)
        pass

    def clear_test_set(self):
        self.test_entries = []

    def initialize_valid_batches(self, batch_size=-1):
        if batch_size == -1:
            batch_size = self.batch_size
        self.valid_batch_indices = self.create_batches(batch_size, self.valid_entries)
        return len(self.valid_batch_indices)
        pass

    def initialize_test_batches(self, batch_size=-1):
        if batch_size == -1:
            batch_size = self.batch_size
        self.test_batch_indices = self.create_batches(batch_size, self.test_entries)
        return len(self.test_batch_indices)
        pass

    def initialize_holdout_batches(self, batch_size=-1):
        if batch_size == -1:
            batch_size = self.batch_size
        self.holdout_batch_indices = self.create_batches(batch_size, self.holdout_entries)
        return len(self.holdout_batch_indices)
        pass

    def get_next_train_batch(self):
        if len(self.train_batch_indices) > 0:
            indices = self.train_batch_indices.pop(0)
            prepared_data = self.prepare_data(self.train_entries, indices)
            same_class_features = self.find_same_class_data(ignore_indices=indices)
            different_class_features = self.find_different_class_data(ignore_indices=indices)
            return (*prepared_data, same_class_features, different_class_features)
        raise ValueError('Initialize Train Batch First by calling dataset.initialize_train_batches()')
        pass

    def get_next_valid_batch(self):
        if len(self.valid_batch_indices) > 0:
            indices = self.valid_batch_indices.pop(0)
            return self.prepare_data(self.valid_entries, indices)
        raise ValueError('Initialize Valid Batch First by calling dataset.initialize_valid_batches()')
        pass

    def get_next_test_batch(self):
        if len(self.test_batch_indices) > 0:
            indices = self.test_batch_indices.pop(0)
            return self.prepare_data(self.test_entries, indices)
        raise ValueError('Initialize Test Batch First by calling dataset.initialize_test_batches()')
        pass

    def get_next_holdout_batch(self):
        if len(self.holdout_batch_indices) > 0:
            indices = self.holdout_batch_indices.pop(0)
            return self.prepare_data(self.holdout_entries, indices)
        raise ValueError('Initialize holdout Batch First by calling dataset.initialize_holdout_batches()')
        pass

    def create_batches(self, batch_size, entries):
        _batches = []
        if batch_size == -1:
            batch_size = self.batch_size
        total = len(entries)
        indices = np.arange(0, total, 1)
        if self.shuffle:
            np.random.shuffle(indices)
        start = 0
        end = len(indices)
        curr = start
        while curr < end:
            c_end = curr + batch_size
            if c_end > end:
                c_end = end
            _batches.append(indices[curr:c_end])
            curr = c_end
        return _batches

    def prepare_data(self, _entries, indices):
        batch_size = len(indices)
        features = np.zeros(shape=(batch_size, self.hdim))
        targets = np.zeros(shape=(batch_size))
        ds_indices = np.zeros(shape=(batch_size))
        for tidx, idx in enumerate(indices):
            entry = _entries[idx]
            assert isinstance(entry, DataEntry)
            targets[tidx] = entry.label
            for feature_idx in range(self.hdim):
                features[tidx, feature_idx] = entry.features[feature_idx]
            if self.with_index:
                ds_indices[tidx] = entry.index
        if self.with_index:
            return torch.FloatTensor(features), torch.LongTensor(targets), torch.LongTensor(ds_indices)
        else:
            return torch.FloatTensor(features), torch.LongTensor(targets)

    def find_same_class_data(self, ignore_indices):
        positive_indices_pool = np.setdiff1d(self.positive_indices_in_train, ignore_indices)
        negative_indices_pool = np.setdiff1d(self.negative_indices_in_train, ignore_indices)
        return self.find_triplet_loss_data(
            ignore_indices, negative_indices_pool, positive_indices_pool)

    def find_different_class_data(self, ignore_indices):
        positive_indices_pool = np.setdiff1d(self.negative_indices_in_train, ignore_indices)
        negative_indices_pool = np.setdiff1d(self.positive_indices_in_train, ignore_indices)
        return self.find_triplet_loss_data(
            ignore_indices, negative_indices_pool, positive_indices_pool)

    def find_triplet_loss_data(self, ignore_indices, negative_indices_pool, positive_indices_pool):
        # TODO: replace with p=0 for ignored indices, 1/(len(pool)-len(indices)) otherwise
        is_pos = np.array([self.train_entries[eidx].is_positive() for eidx in ignore_indices], dtype=bool)
        positive_chosen = np.random.choice(positive_indices_pool, size=np.count_nonzero(is_pos))
        negative_chosen = np.random.choice(negative_indices_pool, size=np.count_nonzero(np.invert(is_pos)))
        indices = []
        pos_i = 0
        neg_i = 0
        for ip in is_pos:
            if ip:
                indices.append(positive_chosen[pos_i])
                pos_i += 1
            else:
                indices.append(negative_chosen[neg_i])
                neg_i += 1
        # for eidx in ignore_indices:
        #     if self.train_entries[eidx].is_positive():
        #         indices_pool = positive_indices_pool
        #     else:
        #         indices_pool = negative_indices_pool
        #     indices_pool = list(indices_pool)
        #     indices.append(np.random.choice(indices_pool))
        prepared_data = self.prepare_data(self.train_entries, indices)
        features = prepared_data[0]
        return features


def create_dataset(train_file, valid_file=None, test_file=None, batch_size=32, output_buffer=sys.stderr):
    if output_buffer is not None:
        print('Reading Train data from %s' % train_file, file=output_buffer)
    train_data = json.load(open(train_file))
    # "target": 1, "graph_feature"
    hdim = len(train_data[0]["graph_feature"])
    dataset = DataSet(batch_size=batch_size, hdim=hdim)
    for data in train_data:
        dataset.add_data_entry(data["graph_feature"], min(int(data["target"]), 1), part='train')
    if valid_file is not None:
        if output_buffer is not None:
            print('Reading Valid data from %s' % valid_file, file=output_buffer)
        valid_data = json.load(open(valid_file))
        for data in valid_data:
            dataset.add_data_entry(data["graph_feature"], min(int(data["target"]), 1), part='valid')
    if test_file is not None:
        if output_buffer is not None:
            print('Reading Test data from %s' % test_file, file=output_buffer)
        test_data = json.load(open(test_file))
        for data in test_data:
            dataset.add_data_entry(data["graph_feature"], min(int(data["target"]), 1), part='test')
    # dataset.initialize_dataset()
    return dataset
