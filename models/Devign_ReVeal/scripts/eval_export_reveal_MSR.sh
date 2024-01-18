#!/bin/bash

fold=$1
seed=$2
model=$3
model2=$4
model3=$5
echo evaling fold $fold seed $seed model $model $model2 $model3

python -u Devign/main.py --dataset MSR --input_dir data/MSR/full_experiment_real_data_processed --fold $fold --seed $seed \
    --model_type ggnn --node_tag node_features --graph_tag graph --label_tag targets --batch_size 256 --eval_export --save_after_ggnn --model_bruh $model 2>&1 | tee "$(basename $0)_ggnn_${fold}_$(echo $model | sed s@/@-@g)_${seed}.log"
retVal=${PIPESTATUS[0]}
if [ $retVal -ne 0 ]; then
    echo "Error"
    exit $retVal
fi
exec python -u Vuld_SySe/representation_learning/api_test.py --input_dir data/MSR/full_experiment_real_data_processed --fold $fold --seed $seed --features ggnn --eval_export --model_bruh $model2 --features_bruh $model3 2>&1 | tee "$(basename $0)_reveal_${fold}_$(echo $model | sed s@/@-@g)_${seed}.log"
