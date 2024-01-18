#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=32
#SBATCH --mem=256G
#SBATCH --time=24:00:00
#SBATCH --gres=gpu:1
#SBATCH --partition=gpu
#SBATCH --output=<ANONYMOUS>/<ANONYMOUS>/sysevr/jobs/logs/model_trainer.out
#SBATCH --error=<ANONYMOUS>/<ANONYMOUS>/sysevr/jobs/logs/model_trainer.err
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END
#SBATCH --job-name="Model Trainer"

module load  python/3.6.5-fwk5uaj
module load tensorflow-gpu/1.2.1/u16-cuda8.0-libcudnn5.1-py36

path=<ANONYMOUS>/<ANONYMOUS>/sysevr/Implementation/model
cd $path

tf-gpu python bgru.py