#%%
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 13})

df = pd.read_csv(
    "data/ICSE23 Empirical study large-scale training results - bug type data export.csv"
)
# TODO: include all model results
df = df[df["Model"].isin(("LineVul", "ReGVD", "Devign", "ReVeal", "CodeBert", "PLBART", "Code2Vec"))]
df = df[["evaluation", "Model"] + [c for c in df.columns if c.endswith("_f1")]]
df = df.rename(columns={c: c[:-3] for c in df.columns if c.endswith("_f1")})
melt_df = pd.melt(
    df,
    id_vars="Model",
    value_vars=[c for c in df.columns if c not in ("evaluation", "Model")],
    ignore_index=False,
).rename(columns={"variable": "training", "value": "f1"})
df = melt_df.join(df[["evaluation"]])
df = df.replace({
    "BOF": "Buffer overflow",
    "input_validation": "Input validation error",
    "privilege_escalation_authorization": "Privilege escalation",
    "resource_allocation_free": "Resource error",
    "value_propagation": "Value error",
    "mixed": "All bug types",
})
df["f1"] *= 100
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
df["Model"] = df["Model"].apply(lambda x: f"{model_order[x]}{x}")
df = df.sort_values(["Model", "training", "evaluation"]).reset_index()
df = pd.concat((df, pd.DataFrame([{"Model": m, "training": "filler", "evaluation": "filler", "f1": float('-inf')} for m in df["Model"].unique()])))
df = pd.concat((df, pd.DataFrame([{"Model": m, "training": "filler", "evaluation": "filler2", "f1": float('-inf')} for m in df["Model"].unique()])))
df

#%%
df = df.sort_values(["Model", "training"]).reset_index(drop=True)
df["index"] = df.index.to_series()

lefts = []
widths = []
offset = 0
datas = []

sets = df["training"].dropna().drop_duplicates().sort_values().tolist()
sets.remove("All bug types")
sets.append("All bug types")
sets.remove("filler")
sets.append("filler")
sets.append("filler2")
palette = dict(zip(sets, sns.color_palette("tab10")))
plt.figure(figsize=(12, 4), dpi=80)
ax = plt.gca()
df["model_training"] = df["Model"].str.cat(df["training"])
sns.barplot(
    data=df[df["training"] == df["evaluation"]],
    x="model_training",
    y="f1",
    hue="training",
    palette=palette,
    linewidth=1,
    edgecolor="k",
    dodge=False,
    ax=ax,
)
sns.stripplot(
    data=df[(df["training"] != df["evaluation"]) & (df["evaluation"] != "All bug types")],
    x="model_training",
    y="f1",
    hue="evaluation",
    palette=palette,
    linewidth=1,
    edgecolor="k",
    ax=ax,
)
h, l = ax.get_legend_handles_labels()
# print(h)
# print(l)
h, l = h[-7:-1], l[-7:-1]  # include only items from barplot legend
# plt.legend(loc="center left", bbox_to_anchor=(1.04, 0.5))  # on the right
# plt.legend(loc="lower left", mode="expand", ncol=3, bbox_to_anchor=(0, 1.02, 1, 0.2))  # on top
plt.legend(
    h,
    l,
    title="Bug type",
    # loc="lower left",
    # mode="expand",
    # ncol=2,
    # bbox_to_anchor=(0, 1.12, 1, 0.2),
    loc="center left",
    bbox_to_anchor=(1.04, 0.5),
)

plt.ylim((0, 100))
plt.xlabel("Training dataset")
plt.ylabel("$F_1$ on test dataset")


labels = []
labels.append("")
models = df["Model"].dropna().drop_duplicates().sort_values().tolist()
models = [m for m in models if m]
for m in models:
    labels.append(m[1:])
    labels.append("")

num_bars = len(df.drop_duplicates(["Model", "training"]))-1
plt.xlim(-1, num_bars)
plt.xticks(np.linspace(-1, num_bars, len(labels)), labels)
plt.xlabel("Model")

plt.tight_layout()
plt.savefig(f"plot_bug_types.pdf")
plt.show()

#%%
samedf = df[df["training"] == df["evaluation"]]
samedf.join(samedf.sort_values(["Model", "training"]).groupby("Model")["f1"].rank(ascending=False).rename("rank").astype(int)).sort_values(["Model", "rank"])[["Model", "training", "f1", "rank"]]
