for m in GNN-ReGVD devign codebert vulberta random_data random_values
do
    for s in train valid test
    do
        logfile="corr_${m}_${s}.log"
        echo $logfile
        if [ ! -f "$logfile" ]
        then
            python analysis/case_studies/correlation_model.py --select_split $s --nn_model_type $m --train_on_test --classify_correct --regress_prob &> $logfile
        fi
    done
done