#%%
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
# plt.rcParams.update({'font.size': 12})

df = pd.read_csv("data/ICSE23 Empirical study large-scale training results - LR coeff data export.csv", index_col=0)
# df.columns = pd.MultiIndex.from_tuples([(c.split("_")[0], c.split("_")[1]) for c in df.columns])
# df = df.pivot(index="name", values="coeff", columns="")
df

#%%
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

#%%

feature_names = [
"while",
"for",
"if",
"goto",
"call",
"switch",
"jumps",
"pointers",
"arrays",
"comment",
"asm",
"macro",
]
feature_names_replace = {
"feat.while_dowhile": "while",
"feat.single.for_statement": "for",
"feat.single.if_statement": "if",
"feat.unstructured": "goto",
"feat.single.call_expression": "call",
"feat.switch_case": "switch",
"feat.jumps": "jump",
"feat.pointers": "pointer",
"feat.arrays": "arrays",
"feat.single.comment": "comment",
"feat.macros": "macro",
"feat.lexical.num_chars": "length",
}


#%%

# names = sorted(df["name"].iloc[0].unique())
rows = []
for i, row in df.iterrows():
    pairs = list(row.items())
    for i in range(0, len(pairs), 2):
        pname = pairs[i]
        pcoeff = pairs[i+1]
        _, model = pname[0].split("_")
        rows.append({"model": model, "coeff": pname[1], "value": pcoeff[1]})
rows_df = pd.DataFrame(rows)
rows_df["model_order"] = rows_df["model"].apply(model_order.get)
rows_df = rows_df.sort_values(["coeff", "model_order"])
rows_df["coeff"] = rows_df["coeff"].apply(feature_names_replace.get)
# rows_df["coeff"] = [c.replace("feat.", "").replace("single.", "").replace("lexical.", "") for c in rows_df["coeff"]]
rows_df

#%%
import numpy as np
import random
random.seed(0)

def jitter(x):
    range = 0.25
    return x + (random.uniform(0.05, range) * random.choice([-1, 1]))

coeff_ids = {c: i for i, c in enumerate(sorted(rows_df["coeff"].unique()))}
rows_df['coeff_id'] = rows_df['coeff'].apply(lambda x: coeff_ids[x])

def should_jitter(row):
    group = rows_df.groupby("coeff").get_group(row["coeff"])
    group = group[group["model"] != row["model"]]
    differences = group["value"] - row["value"]
    abs_differences = np.abs(differences)
    return np.any(abs_differences < 0.005)
rows_df["coeff_jitter"] = rows_df.apply(should_jitter, axis=1)
rows_df['jittered_coeff'] = rows_df.apply(lambda x: jitter(x['coeff_id']) if x["coeff_jitter"] else x['coeff_id'], axis=1)

plt.figure(figsize=(7.5, 5), dpi=100)
# rows_df['jittered_coeff'] = rows_df['coeff_id'].apply(lambda x: jitter(x))
# model	coeff	value	model_order	coeff_id	coeff_jitter	jittered_coeff
# 3	CodeBert	while	-0.3292	3	11	False	11.0
# 5	VulBERTa-MLP	while	-0.1363	5	11	False	11.0
# rows_df = rows_df.append({'model': 'Code', 'coeff': 89, 'value': 93}, ignore_index = True)
point_1 = rows_df[(rows_df["coeff"] == "while") & (rows_df["value"] < -0.1) & (rows_df["model"] == "CodeBERT")]
rows_df.loc[point_1.index, "value"] = -0.065
rows_df.loc[point_1.index, "jittered_coeff"] -= 0.5
point_2 = rows_df[(rows_df["coeff"] == "while") & (rows_df["value"] < -0.1) & (rows_df["model"] == "VulBERTa-MLP")]
rows_df.loc[point_2.index, "value"] = -0.0775
rows_df.loc[point_2.index, "jittered_coeff"] -= 0.5

plt.gca().annotate(f'    = {-0.33}\n    = {-0.14}', xy=(11, -0.1), xytext=(0, 20), 
            textcoords='offset points', ha='center', va='bottom',
            bbox=dict(boxstyle='round,pad=0.3', fc="w", ec="k", alpha=1.0),
            arrowprops=dict(arrowstyle='simple', fc="k", ec="k", relpos=(0.5, 0.5)), zorder=3)

# plt.figure(figsize=(12, 10), dpi=80)
# sns.lineplot(data=rows_df, x="coeff", y="value", hue="model")#, style="model", markers=True)
# sns.catplot(data=rows_df, x="coeff", y="value", hue="model", kind="point", linestyles=[":"] * rows_df["model"].nunique(), legend=False, aspect=1.5)
sns.scatterplot(data=rows_df, x="jittered_coeff", y="value", hue="model", style="model", s=100, zorder=3)
plt.gca().set_xticks(list(coeff_ids.values()))
plt.gca().set_xticklabels(list(coeff_ids.keys()))

# import matplotlib.ticker as mticker
# ax = plt.gca()
# ax.yaxis.set_minor_locator(mticker.FixedLocator((-0.1, 0.1)))
# ax.yaxis.set_minor_formatter(mticker.FixedFormatter(("Label A", "Label B")))
# plt.setp(ax.yaxis.get_minorticklabels(), rotation=90, size=15, va="center")
# ax.tick_params("y",which="minor",pad=25, left=False)
# secax = plt.gca().secondary_xaxis('top', functions=(deg2rad, rad2deg))

left, width = -0.1, .5
bottom, height = 0.0, 1.0
right = left + width
top = bottom + height
# left += 0.02
ax = plt.gca()
ax.text(left, top, r'easy $\rightarrow$',
        horizontalalignment='right',
        verticalalignment='top',
        transform=ax.transAxes, rotation=90)

ax.text(left-0.0025, bottom-0.06, '$\leftarrow$ difficult',
        horizontalalignment='right',
        verticalalignment='bottom',
        transform=ax.transAxes, rotation=90)

handles, labels = plt.gca().get_legend_handles_labels()
order = [labels.index(x) for x in model_order if x in labels]
handles, labels = [handles[idx] for idx in order], [labels[idx] for idx in order]
plt.legend(handles, labels, title="Model", loc="lower left", mode="expand", ncol=3, bbox_to_anchor=(0, 1.02, 1, 0.2), prop={"size": 12})  # on top
# plt.legend(loc="center left", bbox_to_anchor=(1.04, 0.5))  # on the right
# plt.xticks(rotation=45, ha='right', rotation_mode='anchor')

plt.ylabel("Coefficient value", fontsize=12)
plt.xlabel("Code feature", fontsize=12)
plt.ylim(-0.1, 0.1)
plt.grid(zorder=0)
plt.tight_layout()
plt.savefig("plot_lr_coeff.pdf")
plt.show()

#%%
rows_df[(rows_df["coeff"] == "while") & (rows_df["value"] < -0.1)]

# %%
