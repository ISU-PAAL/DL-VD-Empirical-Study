
#!/bin/bash
 
# Declare an array of string with type
declare -a StringArray=( "fold_0_" "fold_1_" "fold_2_" "fold_3_" "fold_4_")
i=350
# Iterate the string array using for loop
for val in ${StringArray[@]}; do
    let "i+=1"
   python Finetuning+evaluation_VulBERTa-CNN_cross_project.py \
    --seed_input=$i \
    --data_folder=$val \
    --train_test=train \
    --batch=3 \
    --epochs=10 \
    --dataset=combined \
    --generate_json=False
done


    
 