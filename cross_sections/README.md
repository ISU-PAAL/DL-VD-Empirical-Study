# General guidelines

`example_index` sequentially labels the canonical versions of the two datasets. The indices correspond to rows in these files.
- MSR: `MSR_data_cleaned.csv` https://drive.google.com/file/d/1-0VhnHBp9IGh90s2wCNjeCMuy70HPl8X/view?usp=sharing
- Devign: `function.json` https://drive.google.com/uc?id=1x6hoF7G-tSYxg8AFybggypLZgMGDNHfF
For example, the 1st item in `function.json` will have `example_index == 0`, 50th item has `example_index == 49`, ...
For example, the 1st row in `MSR_data_cleaned.csv` will have `example_index == 0`, 50th row has `example_index == 49`, ...

For combined dataset, both `dataset` and `example_index` are needed to uniquely identify a dataset example.
**DEPRECATED:** _For MSR, include both `before` and `after` versions of code for each `example_index` in the same dataset partition._
We are now excluding all `after` examples from MSR.

# dataset_size

Meaning of filenames:
- `imbalanced_XXX.csv`: proportion XXX sampled from the imbalanced version of combined dataset (Devign + MSR). `imbalanced_1.0.csv` contains the entire combined dataset.
- `balanced_XXX.csv`: balanced version of `imbalanced_XXX.csv` (excludes rows from MSR where `vul == 0`).

Label proportions:
```
        imbalanced  balanced
target                      
0.0       0.897009  0.524416
1.0       0.102991  0.475584
```

Meaning of columns:
- dataset: MSR or Devign, which dataset this example came from
- example_index: numerical index for the example which is unique _within a dataset_ (but not unique in combined datasets)
- project: metadata, name of the project this code came from
- commit_id: metadata, name of the commit id this code came from
- split: dataset split to which this example is allocated

# cross-project and project_diversity

Note: `fold_XXX_holdout` is identical for the same fold index in both cross-project and project-diversity settings. They are provided separately in both settings for convenience.

Label proportions of first fold:
```
cross_project_dataset
total: 199536
target
0    0.945373
1    0.054627

diverse_dataset
total: 92582
target
0    0.941911
1    0.058089

nondiverse_dataset
total: 91590
target
0    0.952113
1    0.047887
```

## cross-project

Meaning of filenames:
- `fold_XXX` denotes that the file belongs to fold number `XXX`.
- `fold_XXX_holdout.csv` is the holdout set, which is the set of ~10k examples whose projects are distinct from the projects in `fold_XXX_dataset.csv`.
- `fold_XXX_dataset.csv` is the mixed-project dataset, which is split into train/validation/test without separating projects.

Steps for the experiment.
For each fold `fold_XXX`:
1. Train on the `train` split in `fold_XXX_dataset.csv` and use `valid` split for validation.
2. Evaluate on both the `test` split of `fold_XXX_dataset.csv` and all the examples in `fold_XXX_holdout.csv`.

## project_diversity

Meaning of filenames:
- `nondiverse.csv` is the nondiverse set containing only examples from `Chrome`, which is split into training/validation splits. This set is the same for all folds, so it is not identified by `fold_XXX`.
- `fold_XXX` denotes that the file belongs to fold number `XXX`.
- `fold_XXX_diverse.csv` is the diverse set which excludes `Chrome` and the projects in `holdout`, and is split into training/validation splits.
- `fold_XXX_holdout.csv` is the holdout set, which is the set of ~10k examples whose projects are distinct from the projects in the diverse and nondiverse sets.

Steps for the experiment:
1. Train/validate the model on `train`/`valid` splits respectively in `nondiverse.csv`.
2. Train/validate for each `fold_XXX_diverse.csv`.
3. Evaluate both nondiverse and diverse models on `fold_XXX_holdout.csv` for each fold. Only evaluate the diverse model on its respective holdout set.

# bug_type

Each file contains the examples from a set of CWEs which have similar semantics.
All files are mutually exclusive.
All files contain train/valid/test splits.

Steps for the experiment.
For each file `bugtype_XXX`:
1. Train on the `train` split in `bugtype_XXX.csv` and use `valid` split for validation.
2. Evaluate on the `test` split of `bugtype_XXX.csv`.
2. Evaluate on the `test` split of each other `bugtype_YYY.csv`.
