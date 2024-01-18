
#!/bin/bash
 
val="$1"


   python Finetuning+evaluation_VulBERTa-CNN_cross_project.py \
    --seed_input=10102 \
    --data_folder=$val \
    --train_test=train \
    --batch=3 \
    --epochs=10 \
    --dataset=combined \
    --generate_json=False



    
 