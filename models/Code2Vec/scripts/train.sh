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

	source preprocess.sh $val


	echo <ANONYMOUS> is now training $val 

	./train.sh $val

	

# done






    

