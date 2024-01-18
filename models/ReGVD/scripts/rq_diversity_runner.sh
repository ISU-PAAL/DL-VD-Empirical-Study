#!/bin/bash
sbatch << EOT
#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=16
#SBATCH --mem=128G
#SBATCH --time=10-00:00:00
#SBATCH --output="<ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/jobs/logs_rq_b4_2/model_trainer_"$1$2".out"
#SBATCH --error="<ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/jobs/logs_rq_b4_2/model_trainer_"$1$2".err"
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END
#SBATCH --job-name=$1$2

echo $1


source <ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/env/bin/activate

cd <ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/code

python run_rq_b4_2.py --dataset  $1 --fold $2

EOT