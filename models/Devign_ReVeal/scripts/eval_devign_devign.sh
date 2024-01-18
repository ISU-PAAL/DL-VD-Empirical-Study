#!/bin/bash

fold=$1
seed=$2
echo evaling fold $fold seed $seed

python -u Devign/main.py --dataset devign --input_dir data/devign/full_experiment_real_data_processed --fold $fold --seed $seed \
    --model_type devign --node_tag node_features --graph_tag graph --label_tag targets --batch_size 256 --eval_export
