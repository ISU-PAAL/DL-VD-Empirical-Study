for task in cross_holdout diverse_holdout nondiverse_holdout
do
for fold in `seq 0 4`
do
tsp bash hpc/teval_reveal_MSR.sh ${task}_${fold} 1
done
done
