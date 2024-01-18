if [ "$1" == "ggnn" ]
then
    save_after_arg="--save_after_ggnn"
else
    save_after_arg=""
fi

python -u Devign/main.py --dataset devign --model_type $1 --input_dir data/line_ggnn/devign/v$2 \
    --node_tag node_features --graph_tag graph --label_tag targets \
    --batch_size 1024 --eval_export $save_after_arg
