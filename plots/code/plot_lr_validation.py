#%%
import pandas as pd

import seaborn as sns
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 14})

df = pd.read_csv("data/ICSE23 Empirical study large-scale training results - LR data export.csv")
df = pd.melt(df, "model")
df = df.dropna(subset=["value"])
df = df.rename(columns={"variable": "Dataset", "model": "Model"})
dataset_order = {
    "difficult": 0,
    "original": 1,
    "easy": 2,
}
df["Dataset_order"] = df["Dataset"].apply(dataset_order.get)
models = [
    # GNN
    "Devign",
    "ReVeal",
    "ReGVD",
    # Transformer
    "CodeBERT",
    "VulBERTa-CNN",
    "VulBERTa-MLP",
    "PLBART",
    "LineVul",
    # MLP
    "Code2Vec",
]
model_order = dict(zip(models, range(len(models))))
df["Model_order"] = df["Model"].apply(model_order.get)
df = df.sort_values(["Dataset_order", "Model_order"])
df["value"] *= 100
sns.barplot(data=df, x="Model", y="value", hue="Dataset", edgecolor="k", linewidth=1)
plt.legend(title="Evaluation dataset", loc="lower left", mode="expand", ncol=3, bbox_to_anchor=(0, 1.02, 1, 0.2))  # on top
plt.xticks(rotation=45, ha='right', rotation_mode='anchor')
plt.ylabel("$F_1$ score")
plt.tight_layout()
plt.savefig("plot_lr_validation.pdf")
plt.show()
