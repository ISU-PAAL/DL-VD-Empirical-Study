#!/bin/bash
#SBATCH -N 1
#SBATCH -n 2
#SBATCH --mem 8G
#SBATCH --time=06:00:00
#SBATCH --err="hpc/logs/ld_%j.info"
#SBATCH --output="hpc/logs/ld_%j.info"
#SBATCH --job-name="ld"
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END

conda activate Devign37

which <ANONYMOUS>/<ANONYMOUS>/envs/Devign37/bin/python
<ANONYMOUS>/<ANONYMOUS>/envs/Devign37/bin/python -V

echo running on $SLURM_JOB_NODELIST

fold=$1
echo "load dataset for" $fold

<ANONYMOUS>/<ANONYMOUS>/envs/Devign37/bin/python -u Devign/main.py --dataset devign --input_dir data/line_ggnn/devign --fold $fold \
    --node_tag node_features --graph_tag graph --label_tag targets --batch_size 256 --stop_after_dataset
