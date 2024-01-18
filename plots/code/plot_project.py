#%%
import pandas as pd

import seaborn as sns
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 13})

df = pd.read_csv("data/ICSE23 Empirical study large-scale training results - cross project data export.csv")
# df = df.dropna(how="all")
melt_df = pd.melt(df, id_vars='Model', value_vars=["Diverse", "Nondiverse", "Cross project", "Mixed project"], ignore_index=False)
melt_df = melt_df.dropna()
df = melt_df.join(df[["Fold"]])
df["value"] *= 100
df

#%%
models = [
    # GNN
    "Devign",
    "ReVeal",
    "ReGVD",
    # Transformer
    "CodeBert",
    "VulBERTa-CNN",
    "VulBERTa-MLP",
    "PLBART",
    "LineVul",
    # MLP
    "Code2Vec",
]
model_order = dict(zip(models, range(len(models))))

#%%
df["Model_order"] = df["Model"].apply(model_order.get)

# %%
import itertools
def make_plot(df, variables, name, palette, ascending):
    sns.boxplot(data=df[df["variable"].isin(variables)].sort_values(by=["Model_order", "variable"], ascending=[True, ascending]), x="Model", hue="variable", y="value", palette=palette)
    plt.ylim((0, 100))
    plt.ylabel("$F_1$ on held-out set")
    plt.xlabel("Training dataset")
    plt.legend(title="Dataset")
    plt.tight_layout()
    plt.savefig(f"plot_{name}.pdf")
    plt.show()
palette = itertools.cycle(sns.color_palette())
make_plot(df[~df["Model"].isin(["VulBERTa-CNN", "Code2Vec"])], ["Diverse", "Nondiverse"], "project_diversity", palette, True)
make_plot(df[~df["Model"].isin(["VulBERTa-CNN", "Code2Vec"])], ["Cross project", "Mixed project"], "cross_project", palette, False)
