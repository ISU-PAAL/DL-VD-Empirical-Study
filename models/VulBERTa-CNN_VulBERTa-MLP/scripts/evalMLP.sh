#!/bin/bash
 
seed="$1"
dataset="$2"

exec python -u Evaluation_VulBERTa-MLP.py \
    --seed_input=$seed \
    --batch=2 \
    --data_folder=$dataset 2>&1 | tee "$(basename $0)_eval_${seed}_${dataset}.log"
