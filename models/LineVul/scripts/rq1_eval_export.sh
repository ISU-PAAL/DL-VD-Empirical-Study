dataset=$1
datadir=data/$dataset
weight_path=$2
seed=$3

python linevul_main.py \
  --model_name=$weight_path \
  --output_dir=./saved_models \
  --model_type=roberta \
  --tokenizer_name=microsoft/codebert-base \
  --model_name_or_path=microsoft/codebert-base \
  --eval_export \
  --seed $seed \
  --train_data_file=../$datadir/train.csv \
  --eval_data_file=../$datadir/val.csv \
  --test_data_file=../$datadir/test.csv \
  --block_size 512 \
  --eval_batch_size 4 2>&1 | tee "eval_export_$(echo $dataset | sed s@/@-@g)_$(echo $weight_path | sed s@/@-@g).log"
