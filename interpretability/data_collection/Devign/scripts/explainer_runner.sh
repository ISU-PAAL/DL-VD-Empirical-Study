#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --mem=32G
#SBATCH --time=10-00:00:00
#SBATCH --partition=gpu
#SBATCH --gres=gpu:rtx_2080_Ti:1
#SBATCH --output=<ANONYMOUS>/<ANONYMOUS>/devign/code_runner_output_devign.out
#SBATCH --error=<ANONYMOUS>/<ANONYMOUS>/devign/code_runner_eror_devign.err
#SBATCH --job-name="Ex DeDe"
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END




path=<ANONYMOUS>/<ANONYMOUS>/devign/
cd $path

source env/bin/activate

python -u explain.py --dataset devign --input_dir <ANONYMOUS>/<ANONYMOUS>/data/devign_model/devign/full_experiment_real_data_processed\
    --fold codexglue --seed 1 --model_type devign --node_tag node_features\
    --graph_tag graph --label_tag targets --batch_size 1\
    --explain