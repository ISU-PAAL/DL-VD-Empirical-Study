#!/bin/bash
sbatch << EOT
#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --mem=32G
#SBATCH --time=1-24:00:00
#SBATCH --partition=gpu
#SBATCH --gres=gpu
#SBATCH --output="<ANONYMOUS>/<ANONYMOUS>/VulBERTa/jobs/model_trainer_"$1_$2".out"
#SBATCH --error="<ANONYMOUS>/<ANONYMOUS>/VulBERTa/jobs/model_trainer_"$1_$2".err"
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END
#SBATCH --job-name=$1

echo $1


source <ANONYMOUS>/<ANONYMOUS>/VulBERTa/env/bin/activate
export  PYTHONPATH=<ANONYMOUS>/<ANONYMOUS>/lit/:${PYTHONPATH}

cd <ANONYMOUS>/<ANONYMOUS>/VulBERTa/

python explain.py --dataset  $2

EOT