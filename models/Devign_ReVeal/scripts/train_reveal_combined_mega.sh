#!/bin/bash

fold=$1
seed=$2
savedir=models/combined/ggnn/v$fold/$seed
echo training fold $fold seed $seed
rm -rf $savedir

python -u Devign/main.py --dataset combined --input_dir data/combined/full_experiment_real_data_processed --fold $fold --seed $seed \
    --model_type ggnn --node_tag node_features --graph_tag graph --label_tag targets --batch_size 256 --train --eval_export --save_after_ggnn --mega_cool_mode 2>&1 | tee "$(basename $0)_ggnn_${fold}_${seed}.log"
retVal=$?
if [ $retVal -ne 0 ]; then
    echo "Error"
    exit $?
fi
exec python -u Vuld_SySe/representation_learning/api_test.py --input_dir data/combined/full_experiment_real_data_processed --fold $fold --seed $seed --features ggnn --train 2>&1 | tee "$(basename $0)_reveal_${fold}_${seed}.log"
