#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=16
#SBATCH --mem=256G
#SBATCH --time=10-00:00:00
#SBATCH --output=<ANONYMOUS>/<ANONYMOUS>/LineVul/linevul/code_runner_output.out
#SBATCH --error=<ANONYMOUS>/<ANONYMOUS>/LineVul/linevul/code_runner_eror.err
#SBATCH --job-name="Ex LiDe"
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END




path=<ANONYMOUS>/<ANONYMOUS>/LineVul/
cd $path

source env/bin/activate

cd linevul 

python explain.py