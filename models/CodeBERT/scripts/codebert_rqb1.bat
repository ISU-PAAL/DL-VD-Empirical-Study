python run.py ^
	--output_folder_name=balanced_0.01 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/balanced_0.01/train.jsonl ^
	--eval_data_file=../dataset/balanced_0.01/valid.jsonl ^
	--test_data_file=../dataset/balanced_0.01/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12
 
 
python run.py ^
	--output_folder_name=balanced_0.01 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_test ^
	--train_data_file=../dataset/balanced_0.01/train.jsonl ^
	--eval_data_file=../dataset/balanced_0.01/valid.jsonl ^
	--test_data_file=../dataset/balanced_0.01/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12


python run.py ^
	--output_folder_name=balanced_0.05 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/balanced_0.05/train.jsonl ^
	--eval_data_file=../dataset/balanced_0.05/valid.jsonl ^
	--test_data_file=../dataset/balanced_0.05/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12
 
 
python run.py ^
	--output_folder_name=balanced_0.05 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_test ^
	--train_data_file=../dataset/balanced_0.05/train.jsonl ^
	--eval_data_file=../dataset/balanced_0.05/valid.jsonl ^
	--test_data_file=../dataset/balanced_0.05/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12
	
	
	
	
	
	
	
	
	
	
	
	
	
	
python run.py ^
	--output_folder_name=imbalanced_0.01 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.01/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.01/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.01/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12
 
 
python run.py ^
	--output_folder_name=imbalanced_0.01 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.01/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.01/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.01/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12


python run.py ^
	--output_folder_name=imbalanced_0.05 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.05/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.05/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.05/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12
 
 
python run.py ^
	--output_folder_name=imbalanced_0.05 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.05/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.05/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.05/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12
