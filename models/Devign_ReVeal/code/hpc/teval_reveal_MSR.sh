#!/bin/bash

fold=$1
seed=$2
echo evaling fold $fold seed $seed

python -u Devign/main.py --dataset MSR --input_dir data/MSR/full_experiment_real_data_processed --fold $fold --seed $seed \
    --model_type ggnn --node_tag node_features --graph_tag graph --label_tag targets --batch_size 256 --holdout --eval_export --save_after_ggnn 2>&1 | tee "$(basename $0)_ggnn_${fold}_${seed}.log"
retVal=${PIPESTATUS[0]}
if [ $retVal -ne 0 ]; then
    echo "Error"
    exit $retVal
fi
exec python -u Vuld_SySe/representation_learning/api_test.py --input_dir data/MSR/full_experiment_real_data_processed --fold $fold --seed $seed --features ggnn --holdout 2>&1 | tee "$(basename $0)_reveal_${fold}_${seed}.log"
