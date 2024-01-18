# RQ.B2


### Cross project
## Slurm Script 
To train and test, run the following slurm command:
```shell
    bash scripts/rq_cross_project_runner.sh [dataset_name] [split name]
```

To train and test on fold_0 dataset and on the holdout test split, use the following command:

```shell
    bash scripts/rq_cross_project_runner.sh fold_0 holdout
```

### Diversity
## Slurm Script 
To train and test, run the following slurm command:
```shell
    bash scripts/rq_diversity_runner.sh [dataset_name] [Split Name]
```

To train and test on fold_0 dataset and on the holdout split, use the following command:

```shell
    bash scripts/rq_diversity_runner.sh fold_0 holdout
```