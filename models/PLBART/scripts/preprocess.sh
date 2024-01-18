#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --mem=128G
#SBATCH --gres=gpu:1
#SBATCH --partition=gpu
#SBATCH --nodelist=frost-6
#SBATCH --time=48:00:00
#SBATCH --job-name="PLBART"
#SBATCH --output=job.%J.out
#SBATCH --error=job.%J.out
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END


# Move to the working folder.
cd '<ANONYMOUS>/<ANONYMOUS>/PLBART/scripts/code_to_code/defect_prediction/combined'

module load ml-gpu/20220603



bash preproc.sh "$1"
#bash run.sh 0
    

