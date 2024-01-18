You can find examples from the dataset in https://drive.google.com/drive/folders/1I9EnhWX8HrklghTBX2ZQ9fExrt6da8Vb?usp=sharing
Format: `codes_<filter><split>.txt`

`<filter>` denotes the criteria by which the codes were selected.
* `boundary` contains only the examples whose predicted probability is within 0.05 of the classification boundary (0.5).
* `incorrect` contains examples wihch the model on all 3 splits predicted incorrectly.
* `hiprob_incorrect` contains the `incorrect` examples which had high probability (predicted probability >= 0.995).

`<split>` denotes the dataset split (train/valid/test) from which the code came.
* `_train` means all examples came from the training dataset in all 3 folds.
* `_test` means all examples came from the test dataset in all 3 folds.
* _no split_ means the file contains examples from the whole dataset.

Each file contains some examples of code and metadata.
The entire file has a single line at the top that says how many examples are in the file.
Each example has a header starting with `CODE for index: ...`, followed by some metadata, then the actual source code.
Examples are separated by double line breaks.
