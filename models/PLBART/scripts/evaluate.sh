#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --mem=128G
#SBATCH --gres=gpu:1
#SBATCH --partition=gpu
#SBATCH --nodelist=frost-6
#SBATCH --time=48:00:00
#SBATCH --job-name="PLBART"
#SBATCH --output=job.%J.out
#SBATCH --error=job.%J.out
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END


# Move to the working folder.
cd '<ANONYMOUS>/<ANONYMOUS>/PLBART/scripts/code_to_code/defect_prediction/combined'

module load ml-gpu/20220603


export PYTHONIOENCODING=utf-8
CURRENT_DIR=$(pwd)
HOME_DIR=$(realpath ../../../..)

while getopts ":h" option; do
    case $option in
    h | *) # display help
        echo
        echo "Syntax: bash run.sh GPU_ID"
        echo
        exit
        ;;
    esac
done

val="$2"
model="$1"
PATH_2_DATA=${HOME_DIR}/data/codeXglue/code-to-code/defect_prediction/combined/$val/processed

echo $PATH_2_DATA

SAVE_DIR=${CURRENT_DIR}/combined/$model
mkdir -p ${SAVE_DIR}
USER_DIR=${HOME_DIR}/source

export CUDA_VISIBLE_DEVICES=0

echo $SAVE_DIR

function generate() {

    RESULT_FILE=${SAVE_DIR}/result_$val.txt
    ml-gpu <ANONYMOUS>/<ANONYMOUS>/plbart_venv/bin/python evaluator.py \
        --user_dir $USER_DIR \
        --model_dir $SAVE_DIR \
        --csv_filename="model_${model}_data_${val}_test" \
        --model_name checkpoint_best.pt \
        --data_bin_path ${PATH_2_DATA}/data-bin \
        --input_file ${PATH_2_DATA}/test.input0 \
        --label_file ${PATH_2_DATA}/test.label \
        --batch_size 128 \
        --max_example -1 \
        --output $RESULT_FILE

    # RESULT_FILE=${SAVE_DIR}/result_$val.txt
    # ml-gpu <ANONYMOUS>/<ANONYMOUS>/plbart_venv/bin/python evaluator.py \
    #     --user_dir $USER_DIR \
    #     --model_dir $SAVE_DIR \
    #     --csv_filename="model_${model}_data_${val}_train" \
    #     --model_name checkpoint_best.pt \
    #     --data_bin_path ${PATH_2_DATA}/data-bin \
    #     --input_file ${PATH_2_DATA}/train.input0 \
    #     --label_file ${PATH_2_DATA}/train.label \
    #     --batch_size 128 \
    #     --max_example -1 \
    #     --output $RESULT_FILE

    # RESULT_FILE=${SAVE_DIR}/result_$val.txt
    # ml-gpu <ANONYMOUS>/<ANONYMOUS>/plbart_venv/bin/python evaluator.py \
    #     --user_dir $USER_DIR \
    #     --model_dir $SAVE_DIR \
    #     --csv_filename="model_${model}_data_${val}_valid" \
    #     --model_name checkpoint_best.pt \
    #     --data_bin_path ${PATH_2_DATA}/data-bin \
    #     --input_file ${PATH_2_DATA}/valid.input0 \
    #     --label_file ${PATH_2_DATA}/valid.label \
    #     --batch_size 128 \
    #     --max_example -1 \
    #     --output $RESULT_FILE

}

generate
