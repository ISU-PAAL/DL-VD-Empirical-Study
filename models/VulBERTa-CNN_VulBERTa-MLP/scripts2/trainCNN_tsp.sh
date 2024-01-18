
#!/bin/bash
 
val="$1"


   python Finetuning+evaluation_VulBERTa-CNN.py \
    --seed_input=10101 \
    --data_folder=$val \
    --train_test=train \
    --batch=3 \
    --epochs=10 \
    --dataset=combined \
    --generate_json=False



    
 