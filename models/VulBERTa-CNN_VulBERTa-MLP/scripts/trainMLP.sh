#!/bin/bash
 
seed="$1"
dataset="$2"

python -u Finetuning_VulBERTa-MLP.py \
    --seed_input=$seed \
    --train_test=test \
    --batch=1 \
    --epochs=3 \
    --data_folder=$dataset 2>&1 | tee "$(basename $0)_${seed}_${dataset}.log"
retVal=${PIPESTATUS[0]}
if [ $retVal -ne 0 ]; then
    echo "Error"
    exit $?
fi
exec python -u Evaluation_VulBERTa-MLP.py \
    --seed_input=$seed \
    --batch=2 \
    --data_folder=$dataset 2>&1 | tee "$(basename $0)_eval_${seed}_${dataset}.log"
