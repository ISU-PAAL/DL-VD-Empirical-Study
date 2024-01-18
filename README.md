# Data package for "An Empirical Study of Deep Learning Models for Vulnerability Detection"

This repository contains the logs and scripts we used to perform the empirical study.
See details in [the paper](./paper.pdf).
See original data package release at https://doi.org/10.6084/m9.figshare.20791240.

# Citation

If you used our code in your research, please consider citing our paper:

> Benjamin Steenhoek, Md Mahbubur Rahman, Richard Jiles, and Wei Le. 2023. An Empirical Study of Deep Learning Models for Vulnerability Detection. In Proceedings of the 45th International Conference on Software Engineering (ICSE 2023). Association for Computing Machinery, New York, NY, USA. https://doi.org/10.1109/ICSE48619.2023.00188

## Organization

Below is an annotated map of the package's organization.

```
.
├── cross_sections......................... cross-sections of the Devign and MSR datasets used for RQ2, RQ4, and RQ5.
│   ├── code............................... scripts used to generate the data for the cross-sections.
│   ├── logs............................... logs from running the scripts.
│   ├── bug_type........................... dataset examples used for RQ2.
│   ├── cross-project...................... dataset examples used for RQ5.
│   ├── dataset_size....................... dataset examples used for RQ4.
│   ├── project_diversity.................. dataset examples used for RQ5.
│   └── README.md.......................... detailed explanation of the files in each cross-section.
│
├── datasets............................... the original datasets. The dataset files are not included for brevity, but a download link is provided.
│   ├── Devign............................. the Devign dataset link and CodeXGLUE splits.
│   └── MSR................................ the MSR dataset link (as splits are not provided by Fan et al, we used the splits from LineVul).
│   
├── interpretability....................... interpretability analysis presented in RQ6.
│   ├── analysis........................... used to analyze the results of the importance scores.
│   ├── data_collection.................... used to collect importance scores from the models.
│   └── examples........................... Devign test dataset examples which we annotated with importance scores and analyzed manually.
│   └── RQ6................................ full listings for the examples shown in RQ6.
│
├── logistic_regression+stability.......... scripts used to perform logistic regression in RQ3 and stability analysis in RQ1.
│   ├── easyhard_lr.py..................... script for logistic regression.
│   └── stability.py....................... script for stability analysis.
│   └── eval_exports....................... data input into logistic_regression and stability.
│
├── models................................. the code used to run the deep learning models.
│   └── <model>............................ the directory for each model.
│       ├── code........................... scripts used to generate the plots.
│       ├── logs........................... logs from running training on the cross-section and reproduction datasets.
│       └── scripts........................ scripts used as entry points into the code.
│
├── plots.................................. used to generate the plots shown in the paper.
│   ├── code............................... scripts used to generate the plots.
│   ├── data............................... data input into the scripts.
│   └── plots.............................. the resulting plots.
│
├── CWE Groupings.xlsx..................... the full list of CWE groups in Table V.
├── Model+ExplainabilityModel Survey.xlsx.. results of the model survey and explainablity tool surveys.
└── Empirical results.xlsx................. the main results of the model reproduction and RQs 2,3,4,5,6.
└── README.md
```

## Model overview

The code, scripts, and logs for the following models are included.

Full experiment data:
- Devign
- ReVeal
- ReGVD
- CodeBERT
- VulBERTa-CNN
- VulBERTa-MLP
- PLBART
- LineVul
- Code2Vec

Model reproduction data:
- SySeVR
- VulDeeLocator

Each model directory includes `code`, `scripts`, and `logs`.
- `code` contains the code distributed by the implementers of the model, plus our
  improvements to work on the MSR dataset and select cross-sections of the data.
- `scripts` contains the scripts we used to train/evaluate the models.
- `logs` contains the logged output from our reproduction and experiments.

The following models share parts of their implementation, and so are grouped in the same folder.
`VulBERTa-CNN` and `VulBERTa-MLP` are included in the directory named `VulBERTa-CNN_VulBERTa-MLP`.
`Devign` and `ReVeal` are included in the directory named `Devign_ReVeal`.

We reproduced the `CodeBERT` and the `VulBERTa` models on two different platforms during our experiments,
so these include two versions of the scripts which are mostly similar, except for minor implementation details.

We could not reproduce `VulDeeLocator` and `SySeVR`. VulDeeLocator requires the code to be compiled. Devign/MSR datasets contain many different real-world open-source projects; compiling all projects will not be practical. SySeVR needs to compute and label program slices. Labeling program slices correctly for large datasets like MSR and Devign is a real challenge. Their paper ([link](https://ieeexplore.ieee.org/document/9321538)) mentioned that the authors manually checked 2,605 examples and corrected 1,641 of the labels.

All models take as input the data in `datasets`; however, the file paths are different from the platforms we used,
so the training/evaluation will not be directly able to run.

Some models take as input a `jsonl` format, which can be generated with the script: `cross_sections/code/data_creator.ipynb`.

## Code overview

These programs take data as input, but the file paths and `PYTHONPATH` are different from our platform, so they may not be directly able to run.
We attempted to include basic data in the same location so that the input and outputs are observable.

## Dataset overview

Dataset sources:
- Devign: https://drive.google.com/file/d/1x6hoF7G-tSYxg8AFybggypLZgMGDNHfF/view?usp=sharing
  - We used the canonical splits provided by the CodeXGLUE project (https://github.com/microsoft/CodeXGLUE/tree/main/Code-Code/Defect-detection).
- MSR: https://drive.google.com/file/d/1-0VhnHBp9IGh90s2wCNjeCMuy70HPl8X/view?usp=sharing
  - As Fan et al. does not provide canonical dataset splits, we used the same splits generated by the LineVul authors.

## References

```
Devign dataset:
@article{zhou_devign_2019,
	title = {Devign: {Effective} vulnerability identification by learning comprehensive program semantics via graph neural networks},
	volume = {32},
	journal = {Advances in Neural Information Processing Systems},
	author = {Zhou, Yaqin and Liu, Shangqing and Siow, Jingkai and Du, Xiaoning and Liu, Yang},
	year = {2019},
	pages = {1--11},
	annote = {Graph NNFunction level},
}

MSR dataset:
@article{fan_cc_2020,
	title = {A {C}/{C}++ {Code} {Vulnerability} {Dataset} with {Code} {Changes} and {CVE} {Summaries}},
	issn = {9781450379571},
	doi = {10.1145/3379597.3387501},
	journal = {Proceedings - 2020 IEEE/ACM 17th International Conference on Mining Software Repositories, MSR 2020},
	author = {Fan, Jiahao and Li, Yi and Wang, Shaohua and Nguyen, Tien N.},
	year = {2020},
	keywords = {C/C++ Code, Code Changes, Common Vulnerabilities and Exposures},
	pages = {508--512},
}

CodeXGLUE:
@article{lu_codexglue_2021,
	title = {{CodeXGLUE}: {A} {Machine} {Learning} {Benchmark} {Dataset} for {Code} {Understanding} and {Generation}},
	url = {http://arxiv.org/abs/2102.04664},
	year = {2021},
	keywords = {machine learning, naturalness of software, program understanding},
}

tree-sitter:
@misc{https://doi.org/10.5281/zenodo.6326492,
  doi = {10.5281/ZENODO.6326492},
  url = {https://zenodo.org/record/6326492},
  author = {Brunsfeld,  Max and Thomson,  Patrick and Hlynskyi,  Andrew and Vera,  Josh and Turnbull,  Phil and Clem,  Timothy and Creager,  Douglas and Helwer,  Andrew and Rix,  Rob and Van Antwerpen,  Hendrik and Davis,  Michael and {,  Ika} and {Tuấn-Anh Nguyễn} and Brunk,  Stafford and {Niranjan Hasabnis} and {Bfredl} and {Mingkai Dong} and Panteleev,  Vladimir and {Ikrima} and Kalt,  Steven and Lampe,  Kolja and Pinkus,  Alex and Schmitz,  Mark and Krupcale,  Matthew and {Narpfel} and Gallegos,  Santos and Martí,  Vicent and {,  Edgar} and Fraser,  George},
  title = {tree-sitter/tree-sitter: v0.20.6},
  publisher = {Zenodo},
  year = {2022},
  copyright = {Open Access}
}

scikit-learn:
@article{10.5555/1953048.2078195,
author = {Pedregosa, Fabian and Varoquaux, Ga\"{e}l and Gramfort, Alexandre and Michel, Vincent and Thirion, Bertrand and Grisel, Olivier and Blondel, Mathieu and Prettenhofer, Peter and Weiss, Ron and Dubourg, Vincent and Vanderplas, Jake and Passos, Alexandre and Cournapeau, David and Brucher, Matthieu and Perrot, Matthieu and Duchesnay, \'{E}douard},
title = {Scikit-Learn: Machine Learning in Python},
year = {2011},
issue_date = {2/1/2011},
publisher = {JMLR.org},
volume = {12},
number = {null},
issn = {1532-4435},
journal = {J. Mach. Learn. Res.},
month = {nov},
pages = {2825–2830},
numpages = {6}
}
```
