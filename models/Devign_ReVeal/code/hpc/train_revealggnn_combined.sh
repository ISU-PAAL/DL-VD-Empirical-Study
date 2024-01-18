#!/bin/bash

fold=$1
seed=$2

exec python -u Vuld_SySe/representation_learning/api_test.py --input_dir data/combined/full_experiment_real_data_processed --fold $fold --seed $seed --features ggnn --train 2>&1 | tee "train_reveal_combined.sh_reveal_${fold}_${seed}.log"
