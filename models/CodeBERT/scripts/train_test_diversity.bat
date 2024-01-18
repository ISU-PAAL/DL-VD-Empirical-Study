python run.py ^
	--output_folder_name=fold_0_diverse ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/fold_0_diverse/train.jsonl ^
	--eval_data_file=../dataset/fold_0_diverse/valid.jsonl ^
	--test_data_file=../dataset/fold_0_diverse/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=fold_0_diverse ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/fold_0_diverse/train.jsonl ^
	--eval_data_file=../dataset/fold_0_diverse/valid.jsonl ^
	--test_data_file=../dataset/fold_0_holdout/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
