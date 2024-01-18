#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --mem=128G
#SBATCH --gres=gpu:1
#SBATCH --partition=gpu
#SBATCH --time=48:00:00
#SBATCH --job-name="code2vec"
#SBATCH --output=job.%J.out
#SBATCH --error=job.%J.out
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END

module load ml-gpu/20220603

val="$1"
val2="$2"

#!/bin/bash
 
# # Declare an array of string with type
# # "balanced_0.8" "balanced_0.7" "balanced_0.6" "balanced_0.5" "balanced_0.4" "balanced_0.3" "balanced_0.2" "balanced_0.1" "imbalanced_0.9" "imbalanced_0.8" "imbalanced_0.7" "imbalanced_0.6" "imbalanced_0.5" "imbalanced_0.4" "imbalanced_0.3" "imbalanced_0.2" "imbalanced_0.1"
# declare -a StringArray=( "balanced_0.9" "balanced_0.8" "balanced_0.7" "balanced_0.6" "balanced_0.5" "balanced_0.4" "balanced_0.3" "balanced_0.2" "balanced_0.1")
# i=150
# # Iterate the string array using for loop
# for val in ${StringArray[@]}; do

	# unlink "<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/test.jsonl"
	# unlink "<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/train.jsonl"
	# unlink "<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/valid.jsonl"
	# ln -s "<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/combined/$val/test.jsonl" "/work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/dx2021/astminer/dataset/test.jsonl"
	# ln -s "<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/combined/$val/train.jsonl" "/work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/dx2021/astminer/dataset/train.jsonl"
	# ln -s "<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/combined/$val/valid.jsonl" "/work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/dx2021/astminer/dataset/valid.jsonl"

	# # rm '<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/test.jsonl'
	# # rm '<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/train.jsonl'
	# # rm '<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/valid.jsonl'
	# # cp "<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/combined/$val/test.jsonl" "/work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/dx2021/astminer/dataset/"
	# # cp "<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/combined/$val/train.jsonl" "/work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/dx2021/astminer/dataset/"
	# # cp "<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/dataset/combined/$val/valid.jsonl" "/work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/dx2021/astminer/dataset/"

	# # Move to the working folder.
	# cd '<ANONYMOUS>/<ANONYMOUS>/dx2021/astminer/'

	# rm -f "devign.train.raw.txt"
	# rm -f "devign.valid.raw.txt"
	# rm -f "devign.test.raw.txt"

	# ./cli.sh test
	# ./cli.sh valid
	# ./cli.sh train


	cd '<ANONYMOUS>/<ANONYMOUS>/dx2021/code2vec'

	# mv "devign.train.raw.txt" "$val.train.raw.txt" 
	# mv "devign.valid.raw.txt" "$val.valid.raw.txt" 
	# mv "devign.test.raw.txt" "$val.test.raw.txt"

	echo <ANONYMOUS> is now preprocessing $val 

	# source preprocess.sh $val
	source preprocess.sh $val2


	echo <ANONYMOUS> is now training $val 

	# ./train.sh $val

	best_f1=-0.1
	best_name=""
	search_dir=models/$val/
	for entry in "$search_dir"/*
	do
	  echo "$entry"
	  echo "$entry" | grep -oP 'f1=\d+.\d+'
	  echo "$entry" | grep -oP 'saved_model_iter\d+_performance_precision=\d+.\d+_recall=\d+.\d+_accuracy=\d+.\d+error_rate=\d+.\d+_f1=\d+.\d+'

	  	pat='f1=([0-9]+.[0-9]+)'
	  	s="$entry"
		[[ $s =~ $pat ]] # $pat must be unquoted
		echo "$s"
		echo "match 0:"
		echo "${BASH_REMATCH[0]}"
		echo "match 1:"
		echo "${BASH_REMATCH[1]}"
		current_f1="${BASH_REMATCH[1]}"


		pat='saved_model_iter[0-9]+_performance_precision=[0-9]+.[0-9]+_recall=[0-9]+.[0-9]+_accuracy=[0-9]+.[0-9]+error_rate=[0-9]+.[0-9]+_f1=[0-9]+.[0-9]+'
	  	s="$entry"
		[[ $s =~ $pat ]] # $pat must be unquoted
		echo "$s"
		echo "match 0:"
		echo "${BASH_REMATCH[0]}"
		echo "match 1:"
		echo "${BASH_REMATCH[1]}"

		echo $current_f1
		echo $best_f1
		if (( $(echo "$current_f1 > $best_f1" |bc -l) )); then
			best_f1=$current_f1
			best_name="${BASH_REMATCH[0]}"
		fi

		# pat='[^0-9]+([0-9]+)'
		# s='I am a string with some digits 1024'
		# [[ $s =~ $pat ]] # $pat must be unquoted
		# echo "${BASH_REMATCH[0]}"
		# echo "${BASH_REMATCH[1]}"
	done

	echo $best_name

	echo <ANONYMOUS> is now releasing $val 

	ml-gpu <ANONYMOUS>/<ANONYMOUS>/code2vec_venv2/bin/python code2vec.py --load models/$val/$best_name --release

	echo <ANONYMOUS> is now evaluating $val 

	ml-gpu <ANONYMOUS>/<ANONYMOUS>/code2vec_venv2/bin/python code2vec.py --load models/$val/$best_name.release --test data/$val2/$val2.test.c2v


	ml-gpu <ANONYMOUS>/<ANONYMOUS>/code2vec_venv2/bin/python prediction_outputter.py --load models/$val/$best_name.release



	# echo <ANONYMOUS> is now releasing $val 

	# ml-gpu <ANONYMOUS>/<ANONYMOUS>/code2vec_venv2/bin/python code2vec.py --load models/$val/saved_model_iter16 --release

	# echo <ANONYMOUS> is now evaluating $val 

	# ml-gpu <ANONYMOUS>/<ANONYMOUS>/code2vec_venv2/bin/python code2vec.py --load models/$val/saved_model_iter16.release --test data/$val/$val.test.c2v

# done






    

