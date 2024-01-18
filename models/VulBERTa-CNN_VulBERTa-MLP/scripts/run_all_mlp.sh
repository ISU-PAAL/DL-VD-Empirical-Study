for seed in 1 2 3
do
    bash trainMLP.sh $seed devign
    bash trainMLP.sh $seed msr
done
