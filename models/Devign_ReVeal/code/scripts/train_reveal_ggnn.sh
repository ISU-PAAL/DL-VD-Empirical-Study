for fold in 1 2 3 4 5
do
    sbatch hpc/train_reveal_ggnn.sh $fold
done
