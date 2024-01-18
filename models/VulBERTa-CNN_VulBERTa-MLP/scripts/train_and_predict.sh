eval "$(conda shell.bash hook)"
conda activate myenv


#python Finetuning_VulBERTa-MLP.py \
#    --seed_input=1337 \
#    --train_test=train \
#    --batch=3 \
#    --epochs=10




python Evaluation_VulBERTa-MLP.py \
    --seed_input=1337 \
    --train_test=test \
    --batch=3 \
    --epochs=10



#python Evaluation_VulBERTa-MLP.py \
#    --seed_input=1337 \
#    --train_test=train \
#    --batch=3 \
#    --epochs=10




