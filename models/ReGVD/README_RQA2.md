# RQ.A2

## To get explanation for each model from the explanation tools


### Slurm Script
```shell
    bash scripts/rq_a2_runner.sh [train_data_folder] [test_data_folder] [seed]
```
For example, if we want to train on "value_error" bug type but test on "resource_error" bug type, then run:

```shell
    bash rq_a2_runner.sh value_error resource_error 123456
```