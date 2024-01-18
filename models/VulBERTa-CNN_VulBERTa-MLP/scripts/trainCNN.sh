#!/bin/bash
 
seed="$1"
dataset="$2"

exec python -u VulBERTaCNN.py \
    --seed_input=$seed \
    --train_test=train \
    --batch=4 \
    --epochs=10 \
    --generate_json=False \
    --data_folder=$dataset 2>&1 | tee "$(basename $0)_${seed}_${dataset}.log"
