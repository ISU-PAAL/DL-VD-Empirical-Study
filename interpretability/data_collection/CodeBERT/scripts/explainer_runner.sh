#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=16
#SBATCH --mem=128G
#SBATCH --time=10-00:00:00
#SBATCH --output=<ANONYMOUS>/<ANONYMOUS>/codebert/jobs/model_trainer.out
#SBATCH --error=<ANONYMOUS>/<ANONYMOUS>/codebert/jobs/model_trainer.err
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END
#SBATCH --job-name="Ex CoDe"


path=<ANONYMOUS>/<ANONYMOUS>/codebert/
cd $path

source env/bin/activate


cd <ANONYMOUS>/<ANONYMOUS>/codebert/code 

python explain.py