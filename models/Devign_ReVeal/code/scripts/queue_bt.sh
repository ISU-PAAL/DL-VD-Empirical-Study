# bugtype_buffer_overflow bugtype_privilege_escalation_authorization bugtype_value_propagation_errors bugtype_input_validation bugtype_resource_allocation_free

for bt1 in bugtype_buffer_overflow bugtype_privilege_escalation_authorization bugtype_value_propagation_errors bugtype_input_validation bugtype_resource_allocation_free
do
    for bt2 in bugtype_buffer_overflow bugtype_privilege_escalation_authorization bugtype_value_propagation_errors bugtype_input_validation bugtype_resource_allocation_free
    do
        # tsp bash hpc/teval_devign_MSR2.sh $bt1 1 models/MSR/devign/v$bt2/1
        tsp bash hpc/teval_reveal_MSR2.sh $bt1 1 models/MSR/ggnn/v$bt2/1 models/devign/reveal/v$bt2/1 v$bt2
    done
done
