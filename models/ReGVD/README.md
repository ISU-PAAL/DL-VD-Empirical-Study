# GNN-ReGVD Reproduction

## To train and test, run the following slurmn command:


### Slurm Script
```shell
    bash scripts/reproduction_runner.sh [dataset] [seed] [train batch size] [test split file name without extension]
```
For example, if we want to train and test on devign data, we can run  the following command

```shell
   bash scripts/reproduction_runner.sh devign 123456 512 test
```
