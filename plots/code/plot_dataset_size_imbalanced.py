#%%
import pandas as pd

import seaborn as sns
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 17})

df = pd.read_csv("data/ICSE23 Empirical study large-scale training results - dataset size data export imbalanced.csv")
df = df[~df["Model"].isin(["VulBERTa-CNN", "VulBERTa-MLP"])]
# df = df.dropna(how="all")
percentages = ["1%", "5%"] + [f'{i}%' for i in range(10, 101, 10)]
melt_df = pd.melt(df, id_vars='Model', value_vars=percentages)
melt_df["variable"] = melt_df["variable"].apply(lambda x: int(x[:-1])/100)
melt_df = melt_df.dropna()
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
df = pd.merge(melt_df, df[["Model"]], on="Model")
df["model_order"] = df["Model"].apply(model_order.get)
df = df.sort_values(["model_order", "variable"])
df["value"] = df["value"]*100
df

# %%
nrows = df["Model"].nunique()
# ax = plt.gca()
plt.figure(figsize=(8, 6), dpi=80)
model_order
palette = dict(zip(models, sns.color_palette("tab10")))
# marker_map = dict(zip(df["Model"].sort_values().drop_duplicates().tolist(), ["o", "s", "v", "P", "^", "*", "D", "X"]))
g = sns.lineplot(data=df.dropna(), x="variable", y="value", errorbar=None, hue="Model", legend=False, palette=palette)
g = sns.scatterplot(data=df.dropna(), x="variable", y="value", hue="Model", style="Model", s=100, palette=palette)
# g = sns.scatterplot(data=df[df.isna().any()], x="variable", y="value", ci=None, hue="Model", style="Model", ax=ax)
# plt.xlim((0, 100))
# plt.legend(loc="center left", bbox_to_anchor=(1.04, 0.5))  # on the right

handles, labels = plt.gca().get_legend_handles_labels()
order = [labels.index(x) for x in model_order if x in labels]
plt.legend([handles[idx] for idx in order],[labels[idx] for idx in order], loc="lower left", mode="expand", ncol=3, bbox_to_anchor=(0, 1.02, 1, 0.2))  # on top

plt.ylim((0, 100))
plt.ylabel("$F_1$ on held-out test set")
plt.xlabel("Portion of Imbalanced-dataset")
labels = [x[:-1] + "%" for x in percentages]
# labels = labels[:1] + [""] + labels[2:]
# labels = [labels[0] + "  "] + labels[1:]
plt.gca().set_xticks([int(x[:-1])/100 for x in percentages])
# labels[0] = f"{labels[0]}\nlen(imbalanced)=19,428\nlen(balanced)=4,563"
# labels[-1] = f"{labels[-1]}\ndataset size=194,285"
# plt.text(0, -10, "len(imbalanced)=19,428\nlen(balanced)=4,563")
# plt.title("dataset size=194,285")
props = dict(boxstyle='round', facecolor="white", alpha=0.5)

# place a text box in upper left in axes coords
plt.gca().text(0.55, 0.12, "100% dataset size=194,285", transform=plt.gca().transAxes, fontsize=14,
        verticalalignment='top', bbox=props)
plt.gca().set_xticklabels(labels, rotation=90, ha='center', va="top")

plt.tight_layout()
plt.savefig("plot_dataset_size_imbalanced.pdf")
plt.show()

# %%
