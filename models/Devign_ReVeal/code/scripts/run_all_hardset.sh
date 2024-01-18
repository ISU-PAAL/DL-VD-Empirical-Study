dir=$1

mkdir -p $dir
cp $0 $dir

# for m in GNN-ReGVD devign codebert vulberta #random_data random_values
for m in devign_msr
do
    for s in train valid test
    do
        # for e in easiness normalized_easiness
        for e in normalized_easiness
        do
            logfile="$dir/hardset_${m}_${s}_${e}.log"
            echo logging to $logfile $m $s $e | tee $logfile
            python analysis/case_studies/make_hard_set.py --select_split $s --nn_model_type $m --train_on_test --classify_correct --feature_score_method $e &>> $logfile

            if [ "$s" != "test" ]
            then
                test_after_logfile="$dir/hardset_${m}_${s}_${e}_testafter.log"
                echo logging testafter $logfile to $test_after_logfile $m $s $e | tee $test_after_logfile
                python analysis/case_studies/make_hard_set.py --select_split test --nn_model_type $m --train_on_test --classify_correct --feature_score_method file --log_file "$logfile" &> $test_after_logfile
            fi
        done
    done
done
