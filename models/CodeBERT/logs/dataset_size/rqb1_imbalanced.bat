python run.py ^
	--output_folder_name=imbalanced_1.0 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_1.0/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_1.0/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_1.0/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=imbalanced_1.0 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_1.0/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_1.0/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_1.0/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
	
	
python run.py ^
	--output_folder_name=imbalanced_0.9 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.9/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.9/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.9/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=imbalanced_0.9 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.9/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.9/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.9/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
	
	
python run.py ^
	--output_folder_name=imbalanced_0.8 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.8/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.8/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.8/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=imbalanced_0.8 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.8/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.8/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.8/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
	
	
python run.py ^
	--output_folder_name=imbalanced_0.7 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.7/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.7/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.7/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=imbalanced_0.7 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.7/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.7/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.7/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
	
python run.py ^
	--output_folder_name=imbalanced_0.6 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.6/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.6/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.6/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=imbalanced_0.6 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.6/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.6/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.6/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
	
	
python run.py ^
	--output_folder_name=imbalanced_0.5 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.5/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.5/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.5/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=imbalanced_0.5 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.5/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.5/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.5/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
	
	
python run.py ^
	--output_folder_name=imbalanced_0.4 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.4/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.4/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.4/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=imbalanced_0.4 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.4/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.4/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.4/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
	
python run.py ^
	--output_folder_name=imbalanced_0.3 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.3/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.3/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.3/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=imbalanced_0.3 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.3/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.3/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.3/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
	
python run.py ^
	--output_folder_name=imbalanced_0.2 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.2/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.2/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.2/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=imbalanced_0.2 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.2/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.2/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.2/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
	
python run.py ^
	--output_folder_name=imbalanced_0.1 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/imbalanced_0.1/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.1/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.1/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
 
 
python run.py ^
	--output_folder_name=imbalanced_0.1 ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_eval ^
	--do_test ^
	--train_data_file=../dataset/imbalanced_0.1/train.jsonl ^
	--eval_data_file=../dataset/imbalanced_0.1/valid.jsonl ^
	--test_data_file=../dataset/imbalanced_0.1/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 123456
