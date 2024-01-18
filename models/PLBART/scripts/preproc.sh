#!/usr/bin/env bash

val="$1"
# Declare an array of string with type
# "balanced_0.8" "balanced_0.7" "balanced_0.6" "balanced_0.5" "balanced_0.4" "balanced_0.3" "balanced_0.2" "balanced_0.1" "imbalanced_0.9" "imbalanced_0.8" "imbalanced_0.7" "imbalanced_0.6" "imbalanced_0.5" "imbalanced_0.4" "imbalanced_0.3" "imbalanced_0.2" "imbalanced_0.1"
# declare -a StringArray=( "imbalanced_0.9" "imbalanced_0.8" "imbalanced_0.7" "imbalanced_0.6" "imbalanced_0.5" "imbalanced_0.4" "imbalanced_0.3" "imbalanced_0.2" "imbalanced_0.1")
# i=150
# # Iterate the string array using for loop
# for val in ${StringArray[@]}; do

    # rm '<ANONYMOUS>/<ANONYMOUS>/PLBART/data/codeXglue/code-to-code/defect_prediction/combined/test.jsonl'
    # rm '<ANONYMOUS>/<ANONYMOUS>/PLBART/data/codeXglue/code-to-code/defect_prediction/combined/train.jsonl'
    # rm '<ANONYMOUS>/<ANONYMOUS>/PLBART/data/codeXglue/code-to-code/defect_prediction/combined/valid.jsonl'
    rm -r "<ANONYMOUS>/<ANONYMOUS>/PLBART/data/codeXglue/code-to-code/defect_prediction/combined/$val/processed"
    

    # cp "<ANONYMOUS>/<ANONYMOUS>/PLBART/data/codeXglue/code-to-code/defect_prediction/combined/$val/test.jsonl" "/work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/PLBART/data/codeXglue/code-to-code/defect_prediction/combined/"
    # cp "<ANONYMOUS>/<ANONYMOUS>/PLBART/data/codeXglue/code-to-code/defect_prediction/combined/$val/train.jsonl" "/work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/PLBART/data/codeXglue/code-to-code/defect_prediction/combined/"
    # cp "<ANONYMOUS>/<ANONYMOUS>/PLBART/data/codeXglue/code-to-code/defect_prediction/combined/$val/valid.jsonl" "/work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/PLBART/data/codeXglue/code-to-code/defect_prediction/combined/"


 
    CURRENT_DIR=$(pwd)
    HOME_DIR=$(realpath ../../../..)
    DATA_DIR=${HOME_DIR}/data/codeXglue/code-to-code/defect_prediction/combined/$val
    SPM_DIR=${HOME_DIR}/sentencepiece

    function spm_preprocess() {

        for SPLIT in train valid test; do
            ml-gpu <ANONYMOUS>/<ANONYMOUS>/plbart_venv/bin/python encode.py \
                --model_file ${SPM_DIR}/sentencepiece.bpe.model \
                --src_file $DATA_DIR/$SPLIT.jsonl \
                --output_dir $DATA_DIR/processed \
                --split $SPLIT
        done

    }

    function binarize() {

        ml-gpu <ANONYMOUS>/<ANONYMOUS>/plbart_venv/bin/python /work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/PLBART/fairseq/fairseq_cli/preprocess.py \
            --only-source \
            --trainpref $DATA_DIR/processed/train.input0 \
            --validpref $DATA_DIR/processed/valid.input0 \
            --testpref $DATA_DIR/processed/test.input0 \
            --destdir $DATA_DIR/processed/data-bin/input0 \
            --srcdict ${SPM_DIR}/dict.txt \
            --workers 60
        ml-gpu <ANONYMOUS>/<ANONYMOUS>/plbart_venv/bin/python /work/LAS/<ANONYMOUS>-lab/rd<ANONYMOUS>/PLBART/fairseq/fairseq_cli/preprocess.py \
            --only-source \
            --trainpref $DATA_DIR/processed/train.label \
            --validpref $DATA_DIR/processed/valid.label \
            --destdir $DATA_DIR/processed/data-bin/label \
            --workers 60

    }

    spm_preprocess
    binarize

    # /bin/bash -x <ANONYMOUS>/<ANONYMOUS>/PLBART/scripts/code_to_code/defect_prediction/combined/run.sh $val 0

# done
