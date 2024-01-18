
#!/bin/bash
 



   python Finetuning_VulBERTa-CNN.py \
    --seed_input=10102 \
    --data_folder="$1" \
    --save_folder="$2" \
    --train_test=train \
    --batch=16 \
    --epochs=10 \
    --dataset=combined \
    --generate_json=False



    
 