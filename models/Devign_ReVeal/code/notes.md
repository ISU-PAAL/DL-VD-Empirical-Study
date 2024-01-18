# Input/output study (single fold qualitative analysis on Devign, first run)

- [./train_devign.sh](./train_devign.sh) :: train model and export it to [./models/](./models/)
- [./eval_devign.sh](./eval_devign.sh) :: evaluate model on train/valid/test datasets. Save results to [./data/line_ggnn/devign/v1/eval_export.json](./data/line_ggnn/devign/v1/eval_export.json) in the same directory as the dataset fold.
- [./data/line_ggnn/pair_up.py](./data/line_ggnn/pair_up.py) :: pair items:
  [./data/ggnn_input/devign_cfg_full_text_files.json](./data/ggnn_input/devign_cfg_full_text_files.json) <-> [./data/line_ggnn/devign-line_ggnn.json](./data/line_ggnn/devign-line_ggnn.json) <-> [./data/line_ggnn/devign/v1/train_GGNNinput.json](./data/line_ggnn/devign/v1/train_GGNNinput.json)
  Output to csv in data directory.
- [./analyze_eval_export.py](./analyze_eval_export.py) :: analyze outputs recorded in [./data/line_ggnn/devign/v1/eval_export.json](./data/line_ggnn/devign/v1/eval_export.json) and output interesting statistics
