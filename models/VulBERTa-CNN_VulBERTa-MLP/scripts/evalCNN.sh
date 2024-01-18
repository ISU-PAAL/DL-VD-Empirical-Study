#!/bin/bash
 
seed="$1"
dataset="$2"
model="$3"

exec python -u VulBERTaCNN_eval.py \
    --seed_input=$seed \
    --batch=2 \
    --generate_json=False \
    --data_path=$dataset \
    --model_path=$model \
    --epoch_load=all --no_cuda 2>&1 | tee "$(basename $0)_${seed}_$(echo $dataset | sed s@/@-@g)_$(echo $model | sed s@/@-@g).log"
