# RQ6: Internals of Deep Learning

## data_collection

To run with Slurm:

```shell
    sbatch models/{model_name}/scripts/explainer_runner.sh
```

## analysis

We used these scripts:

- agreement.ipynb: This notebook is to find out the examples where many models report similar multiple lines as the important lines
- disagreement.ipynb: This notebook is to find out the examples where many models report different  lines as the important lines but predict the examples correctly
- analysis_line_score.ipynb: This notebook is to generate the tables VI and VII.
- feature_inspection.ipynb: This notebook is to generate the tables VIII.
