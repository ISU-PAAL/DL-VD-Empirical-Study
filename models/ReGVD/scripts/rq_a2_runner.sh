#!/bin/bash
sbatch << EOT
#!/bin/bash
#SBATCH --nodes=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=64G
#SBATCH --time=2-00:00:00
#SBATCH --partition=biocrunch
#SBATCH --output="<ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/jobs/logs_rq_a2/model_trainer_"$1"_"$2_$3".out"
#SBATCH --error="<ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/jobs/logs_rq_a2/model_trainer_"$1"_"$2_$3".err"
#SBATCH --mail-user=<ANONYMOUS>@iastate.edu
#SBATCH --mail-type=FAIL,END
#SBATCH --job-name=$1

echo $1


source <ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/env/bin/activate

cd <ANONYMOUS>/<ANONYMOUS>/GNN-ReGVD/code

python run_rq_a2.py --dataset  $1 --test $2 --seed $3

EOT