for seed in 1 2 3
do
    echo bash trainCNN.sh $seed devign
    bash trainCNN.sh $seed devign
    echo bash trainCNN.sh $seed msr
    bash trainCNN.sh $seed msr
done
