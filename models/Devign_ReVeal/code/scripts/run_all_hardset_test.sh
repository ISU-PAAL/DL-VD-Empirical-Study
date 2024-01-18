for m in GNN-ReGVD devign codebert vulberta random_data random_values
do
    for s in train valid
    do
        logfile="hardset_${m}_test_${s}.log"
        echo logging to $logfile
        python analysis/case_studies/make_hard_set.py --select_split test --nn_model_type $m --train_on_test --classify_correct --feature_score_method file --difficulty_score top_bottom_k --log_file "hardsets/hardset_${m}_${s}.log" &> $logfile
    done
done
