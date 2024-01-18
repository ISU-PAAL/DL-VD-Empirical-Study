#!/bin/bash
sbatch << EOT
#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=16
#SBATCH --mem=128G
#SBATCH --time=10-00:00:00
#SBATCH --output="<ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/jobs/logs_reproduction/model_trainer_"$1$2$4".out"
#SBATCH --error="<ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/jobs/logs_reproduction/model_trainer_"$1$2$4".err"
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END
#SBATCH --job-name=$2$4

echo $1


source <ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/env/bin/activate

cd <ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/code

python run_reproduction.py --dataset  $1 --seed $2 --batch_size $3 --test_split $4

EOT