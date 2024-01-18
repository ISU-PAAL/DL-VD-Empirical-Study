#!/bin/bash

subset="$1"

exec python run2.py \
--output_folder_name=$subset \
--output_dir=./saved_models \
--model_type=roberta \
--tokenizer_name=microsoft/codebert-base \
--model_name_or_path=microsoft/codebert-base \
--do_train \
--train_data_file=../data/${subset}/train.jsonl \
--eval_data_file=../data/${subset}/valid.jsonl \
--test_data_file=../data/${subset}/test.jsonl \
--epoch 5 \
--block_size 400 \
--train_batch_size 32 \
--eval_batch_size 64 \
--learning_rate 2e-5 \
--max_grad_norm 1.0 \
--evaluate_during_training \
--seed 1 2>&1 | tee "train_$(echo $subset | sed s@/@-@g).log"
