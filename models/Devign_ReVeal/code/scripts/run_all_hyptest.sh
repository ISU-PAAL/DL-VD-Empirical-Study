dir=$1

mkdir -p $dir
cp $0 $dir


for m in devign_msr
do
    for s in train valid test
    do
        logfile="$dir/hyptest_${m}_${s}.txt"
        echo $logfile
        python analysis/case_studies/hypothesis_test.py --select_split $s --nn_model_type $m --output_dir hyptest_${m}_${s} &> $logfile
    done
done