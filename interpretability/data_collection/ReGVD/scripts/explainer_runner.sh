#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=16
#SBATCH --mem=128G
#SBATCH --time=10-00:00:00
#SBATCH --output=<ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/jobs/logs_explanations/code_runner_output.out
#SBATCH --error=<ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/jobs/logs_explanations/code_runner_eror.err
#SBATCH --job-name="Ex ReGVD"
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END




path=<ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/
cd $path

source env/bin/activate

cd code

python explain.py