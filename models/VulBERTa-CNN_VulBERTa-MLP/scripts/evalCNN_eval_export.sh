#!/bin/bash
 
seed="$1"
dataset="$2"
model="$3"

exec python -u VulBERTaCNN_eval.py \
    --seed_input=$seed \
    --batch=4 \
    --generate_json=False \
    --data_path=$dataset \
    --model_path=$model \
    --epoch_load=10 --eval_export 2>&1 | tee "$(basename $0)_${seed}_$(echo $dataset | sed s@/@-@g)_$(echo $model | sed s@/@-@g)_eval_export.log"
