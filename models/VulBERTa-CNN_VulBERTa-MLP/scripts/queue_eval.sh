# for ds in data/finetune/combined/rqb4_1/fold_*_holdout
for i in `seq 0 4`
do
    for model in models_for_eval/VB-CNN_nondiverse models_for_eval/VB-CNN_rqb4.1_fold_0_diverse
    do
        ds="data/finetune/combined/rqb4_2/fold_${i}_holdout/holdout.jsonl"
        bash evalCNN.sh 1 $ds $model || exit
    done
done
