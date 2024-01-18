#!/bin/bash
set -x
for seed in 1 2 3
do
    bash trainCNN.sh $seed devign
    bash trainCNN.sh $seed msr
    bash trainMLP.sh $seed devign
    bash trainMLP.sh $seed msr
done
