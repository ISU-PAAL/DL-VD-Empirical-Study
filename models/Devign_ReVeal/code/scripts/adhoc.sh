fold=codexglue
seed=1
python Devign/main.py --dataset devign --input_dir data/devign/full_experiment_real_data_processed --fold $fold --seed $seed \
    --model_type ggnn --node_tag node_features --graph_tag graph --label_tag targets --batch_size 256 --eval_export --save_after_ggnn 2>&1 | tee "train_then_eval_reveal_devign.sh_ggnn_${fold}_${seed}.log"

fold=codexglue
seed=1
python -m cProfile -o "train_reveal_devign.sh_reveal_${fold}_${seed}.pstat" Vuld_SySe/representation_learning/api_test.py --input_dir data/devign/full_experiment_real_data_processed --fold $fold --seed $seed --features ggnn  --train 2>&1 | tee "train_reveal_devign.sh_reveal_${fold}_${seed}.log"
