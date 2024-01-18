#!/bin/bash
# To run: sbatch hpc/gpu.sh bash eval_devign_all.sh

for model_type in devign ggnn
do
for seed in 1 2 3
do
echo $model_type $seed
bash eval_devign.sh $model_type $seed
done
done