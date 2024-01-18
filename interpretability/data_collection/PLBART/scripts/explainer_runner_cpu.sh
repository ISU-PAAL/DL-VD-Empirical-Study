#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --mem=32G
#SBATCH --time=10-00:00:00
#SBATCH --partition=gpu
#SBATCH --gres=gpu:1
#SBATCH --output=<ANONYMOUS>/<ANONYMOUS>/PLBART/jobs/model_trainer_cpu.out
#SBATCH --error=<ANONYMOUS>/<ANONYMOUS>/PLBART/jobs/model_trainer_cpu.err
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END
#SBATCH --job-name="Ex PLDE"


path=<ANONYMOUS>/<ANONYMOUS>/PLBART/
cd $path

source env/bin/activate


cd <ANONYMOUS>/<ANONYMOUS>/PLBART/code 

python explain.py