`devign_MSR_dataset_export.zip` holds the dataset input files.

`devign_MSR_dataset_source_export.zip` holds the source code which can be linked to the records in `devign_MSR_dataset_export.zip`.

`devign_weights.zip` holds the model checkpoints.

`devign_Word2Vec_weights.zip` holds the checkpoints of the Word2Vec model used to generate the node features.

Run `data_export/hpc/train_devign.sh` to train on devign dataset.

Run `data_export/hpc/train_devign_MSR.sh` to train on MSR dataset.

Please use this version of the project because it takes the dataset format which I am sending you and fixes some bugs in performance reporting and dataset processing: https://git.las.iastate.edu/<ANONYMOUS>/ReVeal
