REM python run.py ^
	REM --output_folder_name=md ^
	REM --output_dir=./saved_models ^
	REM --model_type=roberta ^
	REM --tokenizer_name=microsoft/codebert-base ^
	REM --model_name_or_path=microsoft/codebert-base ^
	REM --do_train ^
	REM --train_data_file=../dataset/devign/train.jsonl ^
	REM --eval_data_file=../dataset/devign/valid.jsonl ^
	REM --test_data_file=../dataset/devign/test.jsonl ^
	REM --epoch 5 ^
	REM --block_size 400 ^
	REM --train_batch_size 32 ^
	REM --eval_batch_size 64 ^
	REM --learning_rate 2e-5 ^
	REM --max_grad_norm 1.0 ^
	REM --evaluate_during_training ^
	REM --seed 12
 
 
python run.py ^
	--output_folder_name=md ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_test ^
	--train_data_file=../dataset/devign/train.jsonl ^
	--eval_data_file=../dataset/devign/valid.jsonl ^
	--test_data_file=../dataset/devign/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12

