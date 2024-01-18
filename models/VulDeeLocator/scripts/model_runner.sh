#!/bin/bash
sbatch << EOT
#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=8
#SBATCH --mem=32G
#SBATCH --time=1-24:00:00
#SBATCH --partition=gpu
#SBATCH --gres=gpu:rtx_2080_Ti:1
#SBATCH --output="<ANONYMOUS>/<ANONYMOUS>/VulDeeLocator/src/jobs/model_trainer_"$1".out"
#SBATCH --error="<ANONYMOUS>/<ANONYMOUS>/VulDeeLocator/src/jobs/model_trainer_"$1".err"
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END
#SBATCH --job-name=$1

echo $1


module load tensorflow-gpu/1.14.1/u16-cuda10.0-libcudnn7.4-py36

cd <ANONYMOUS>/<ANONYMOUS>/VulDeeLocator/src/

tf-gpu python bgru_threshold.py --seed  $1

EOT