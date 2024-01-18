# for ds in data/finetune/combined/rqb4_1/fold_*_holdout
for i in bugtype_buffer_overflow bugtype_resource_allocation_free bugtype_input_validation bugtype_value_propagation_errors bugtype_privilege_escalation_authorization 
do
    for j in bugtype_buffer_overflow bugtype_resource_allocation_free bugtype_input_validation bugtype_value_propagation_errors bugtype_privilege_escalation_authorization 
    do
        ds="data/finetune/combined/rqa2/$i/test.jsonl"
        model="models_for_eval/VB-CNN_combined${j}_10102"
        bash evalCNN.sh 1 $ds $model
    done
done
