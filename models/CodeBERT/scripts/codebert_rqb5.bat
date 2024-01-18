python run.py ^
	--output_folder_name=rqb5_1_contrastive ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/rqb5_1_contrastive/train.jsonl ^
	--eval_data_file=../dataset/rqb5_1_contrastive/valid.jsonl ^
	--test_data_file=../dataset/rqb5_1_contrastive/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12
 
 
python run.py ^
	--output_folder_name=rqb5_1_contrastive ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_test ^
	--train_data_file=../dataset/rqb5_1_contrastive/train.jsonl ^
	--eval_data_file=../dataset/rqb5_1_contrastive/valid.jsonl ^
	--test_data_file=../dataset/rqb5_1_contrastive/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12
	
python run.py ^
	--output_folder_name=rqb5_2_noncontrastive ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_train ^
	--train_data_file=../dataset/rqb5_2_noncontrastive/train.jsonl ^
	--eval_data_file=../dataset/rqb5_2_noncontrastive/valid.jsonl ^
	--test_data_file=../dataset/rqb5_2_noncontrastive/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12
 
 
python run.py ^
	--output_folder_name=rqb5_2_noncontrastive ^
	--output_dir=./saved_models ^
	--model_type=roberta ^
	--tokenizer_name=microsoft/codebert-base ^
	--model_name_or_path=microsoft/codebert-base ^
	--do_test ^
	--train_data_file=../dataset/rqb5_2_noncontrastive/train.jsonl ^
	--eval_data_file=../dataset/rqb5_2_noncontrastive/valid.jsonl ^
	--test_data_file=../dataset/rqb5_2_noncontrastive/test.jsonl ^
	--epoch 5 ^
	--block_size 400 ^
	--train_batch_size 32 ^
	--eval_batch_size 64 ^
	--learning_rate 2e-5 ^
	--max_grad_norm 1.0 ^
	--evaluate_during_training ^
	--seed 12
	
