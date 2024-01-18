# %% 
import json
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib_venn import venn3
import seaborn as sns
import numpy as np

# %% Get data
dfs = []
for fold in [1, 2, 3]:
    with open(f"data/line_ggnn/devign/v{fold}/eval_export.json") as f:
        eval_data = json.load(f)
    df = pd.DataFrame(eval_data)
    df = df.set_index("index", drop=True)
    df["split"] = df["split"].astype(str)
    df["correct"] = df["correct"].astype(bool)
    df["prediction"] = df["prediction"].astype(int)
    df["target"] = df["target"].astype(int)
    df["prob"] = df["prob"].astype(float)
    df["fold"] = fold
    df = df.sort_index()
    # print(df)
    dfs.append(df)

# %% Make Venn diagram
sets = [set(df[df["correct"] == True].index) for df in dfs]
d = venn3(sets, [f"Fold {i}" for i in (1, 2, 3)])
"""
Order: {'100': 0, '010': 1, '110': 2, '001': 3, '101': 4, '011': 5, '111': 6}
"""
print([t._text for t in d.subset_labels])
# print(d.set_labels)
plt.savefig("venn.png")
plt.close()

abs(len(set(dfs[0].index.sort_values().tolist()) & set(dfs[1].index.sort_values().tolist())) - len(set(dfs[0].index.sort_values().tolist()))) < 5
abs(len(set(dfs[1].index.sort_values().tolist()) & set(dfs[2].index.sort_values().tolist())) - len(set(dfs[1].index.sort_values().tolist()))) < 5

all_correct = set.intersection(*[set(df[df["correct"] == True].index) for df in dfs])
all_incorrect = set.intersection(*[set(df[df["correct"] == False].index) for df in dfs])

# %% Get subsets
# https://github.com/konstantint/matplotlib-venn/blob/4e0d418ef9f7c9079aeb1139ae185b3b34fa2068/matplotlib_venn/_venn3.py#L259-L265
a, b, c = [set(df[df["correct"] == True].index) for df in dfs]
all_subsets = ((a - (b | c)),
        (b - (a | c)),
        ((a & b) - c),
        (c - (a | b)),
        ((a & c) - b),
        ((b & c) - a),
        (a & b & c))

"""
Check that counts line up:

length total dataframe: 26730

all correct: 11352
all incorrect: 1353
mixed: 14026
sum: mixed + all correct + all incorrect = 26731
"""
print(max(len(df.index) for df in dfs))
print("all_correct:", len(all_correct))
print("all_incorrect:", len(all_incorrect))
print("mixed:", list(map(len, all_subsets)))


#%% join all df and add code
with open("data/ggnn_input/devign_cfg_full_text_files.json") as f:
    cdf = pd.DataFrame(json.load(f))
# print(cdf)

labels = ['000', '100', '010', '110', '001', '101', '011', '111']
df = dfs[0]
df = df.join(dfs[1], lsuffix="_1", rsuffix="_2", how="left")
df = df.join(dfs[2].rename(columns={c: c + "_3" for c in dfs[2].columns}), lsuffix="_2", rsuffix="_3", how="left")
df = df.dropna()
df.index = df.index.astype(int)
df["prediction_2"] = df["prediction_2"].astype(int)
df["prediction_3"] = df["prediction_3"].astype(int)
df["fold_2"] = df["fold_2"].astype(int)
df["fold_3"] = df["fold_3"].astype(int)
# print(df.columns)
# print(df)
for subset, label in zip((all_incorrect,) + all_subsets, labels):
    subset = [idx for idx in subset if idx in df.index]
    df.loc[subset, "subset_label"] = label
df = df.join(cdf, how="left")
# print(df)

#%% plot code length percentile against subset label
df["code_pct"] = df["code"].str.len().rank(pct = True)
print(df.groupby("subset_label")["code_pct"].agg("mean"))
sns.barplot(data=df, y="code_pct", x="subset_label", estimator=np.mean, order=df.groupby("subset_label")["code_pct"].agg("mean").sort_values().index.tolist())
plt.title("Code length percentile by subset")
plt.xlabel("Subset label")
plt.xlabel("Code length percentile")
plt.tight_layout()
plt.savefig("code_pct_over_subset_label.png")
plt.show()
plt.close()

#%% plot code loop count against subset label
df["loop_count"] = df["code"].str.count("for") + df["code"].str.count("while")
# print(df["loop_count"])
sns.barplot(data=df, y="loop_count", x="subset_label", estimator=np.mean, order=df.groupby("subset_label")["loop_count"].agg("mean").sort_values().index.tolist())
plt.title("Loop count by subset")
plt.xlabel("Subset label")
plt.xlabel("Loop count percentile")
plt.tight_layout()
# plt.savefig("loop_count_over_subset_label.png")
plt.show()
plt.close()

#%% export statistics of each partition
def run_stat(fn):
    print(f"""success: {fn(df[df["subset_label"] == "111"]["code"])}
failure: {fn(df[df["subset_label"] == "000"]["code"])}
mixed: {fn(df[df["subset_label"].isin(("001", "010", "100", "011", "110", "101"))]["code"])}
""")
run_stat(lambda c: c.str.len().mean())
run_stat(lambda c: (c.str.count("for") + c.str.count("while")).mean())

def export_code(df, suffix=""):
    #%% export codes to file
    with open(f"codes_incorrect{suffix}.txt", "w") as of:
        dfset = df[df["subset_label"] == "000"]
        print(len(dfset), "all folds incorrect")
        print(len(dfset), "all folds incorrect", file=of)
        for i, c in dfset["code"].iteritems():
            print("CODE for index:", i, file=of)
            print("subset label:", df.loc[i]["subset_label"], file=of)
            print("label", df.loc[i]["label"], file=of)
            print("split (fold 1)", df.loc[i]["split_1"], file=of)
            print("split (fold 2)", df.loc[i]["split_2"], file=of)
            print("split (fold 3)", df.loc[i]["split_3"], file=of)
            print("prob (fold 1)", df.loc[i]["prob_1"], file=of)
            print("prob (fold 2)", df.loc[i]["prob_2"], file=of)
            print("prob (fold 3)", df.loc[i]["prob_3"], file=of)
            print("prediction (fold 1)", df.loc[i]["prediction_1"], file=of)
            print("prediction (fold 2)", df.loc[i]["prediction_2"], file=of)
            print("prediction (fold 3)", df.loc[i]["prediction_3"], file=of)
            print(c, file=of)
            print("\n", file=of)

    #%% export codes to file
    df["prob_1_strength"] = np.abs(df["prob_1"] - 0.5)
    df["prob_2_strength"] = np.abs(df["prob_2"] - 0.5)
    df["prob_3_strength"] = np.abs(df["prob_3"] - 0.5)
    with open(f"codes_hiprob_incorrect{suffix}.txt", "w") as of:
        dfset = df[((df["prob_1_strength"] > 0.495) | (df["prob_2_strength"] > 0.495) & (df["prob_3_strength"] > 0.495)) & (df["subset_label"] == "000")]
        print(len(dfset), "confident and incorrect")
        print(len(dfset), "confident and incorrect", file=of)
        for i, c in dfset["code"].iteritems():
            print("CODE for index:", i, file=of)
            print("subset label:", df.loc[i]["subset_label"], file=of)
            print("label", df.loc[i]["label"], file=of)
            print("split (fold 1)", df.loc[i]["split_1"], file=of)
            print("split (fold 2)", df.loc[i]["split_2"], file=of)
            print("split (fold 3)", df.loc[i]["split_3"], file=of)
            print("prob (fold 1)", df.loc[i]["prob_1"], file=of)
            print("prob (fold 2)", df.loc[i]["prob_2"], file=of)
            print("prob (fold 3)", df.loc[i]["prob_3"], file=of)
            print("prediction (fold 1)", df.loc[i]["prediction_1"], file=of)
            print("prediction (fold 2)", df.loc[i]["prediction_2"], file=of)
            print("prediction (fold 3)", df.loc[i]["prediction_3"], file=of)
            print(c, file=of)
            print("\n", file=of)

    #%% export codes to file
    df["prob_1_strength"] = np.abs(df["prob_1"] - 0.5)
    df["prob_2_strength"] = np.abs(df["prob_2"] - 0.5)
    df["prob_3_strength"] = np.abs(df["prob_3"] - 0.5)
    with open(f"codes_boundary{suffix}.txt", "w") as of:
        dfset = df[(df["prob_1_strength"] < 0.05) & (df["prob_2_strength"] < 0.05) & (df["prob_3_strength"] < 0.05)]
        print(len(dfset), "close to boundary")
        print(len(dfset), "close to boundary", file=of)
        for i, c in dfset["code"].iteritems():
            print("CODE for index:", i, file=of)
            print("subset label:", df.loc[i]["subset_label"], file=of)
            print("label", df.loc[i]["label"], file=of)
            print("split (fold 1)", df.loc[i]["split_1"], file=of)
            print("split (fold 2)", df.loc[i]["split_2"], file=of)
            print("split (fold 3)", df.loc[i]["split_3"], file=of)
            print("prob (fold 1)", df.loc[i]["prob_1"], file=of)
            print("prob (fold 2)", df.loc[i]["prob_2"], file=of)
            print("prob (fold 3)", df.loc[i]["prob_3"], file=of)
            print("prediction (fold 1)", df.loc[i]["prediction_1"], file=of)
            print("prediction (fold 2)", df.loc[i]["prediction_2"], file=of)
            print("prediction (fold 3)", df.loc[i]["prediction_3"], file=of)
            print(c, file=of)
            print("\n", file=of)
#%%
export_code(df)
export_code(df[(df["split_1"] == "train") & (df["split_2"] == "train") & (df["split_3"] == "train")].copy(deep=True), "_train")
export_code(df[(df["split_1"] == "test") & (df["split_2"] == "test") & (df["split_3"] == "test")].copy(deep=True), "_test")
# export_code(df[df["split"] == "test"], "_test")

#%%
fig, (ax0, ax1, ax2) = plt.subplots(3)
fig.suptitle('Correlation between predicted probabilities')
sns.heatmap(df[["prob_1", "prob_2", "prob_3"]].rename(columns={"prob_1": "fold 1", "prob_2": "fold 2", "prob_3": "fold 3"}).corr(), annot=True, linewidths=0.5, vmin=-1.0, vmax=1.0, ax=ax0)
ax0.set_title("Whole dataset")
sns.heatmap(df[df["subset_label"]=="111"][["prob_1", "prob_2", "prob_3"]].rename(columns={"prob_1": "fold 1", "prob_2": "fold 2", "prob_3": "fold 3"}).corr(), annot=True, linewidths=0.5, ax=ax1, vmin=-1.0, vmax=1.0)
ax1.set_title("All correct (111)")
sns.heatmap(df[df["subset_label"]=="000"][["prob_1", "prob_2", "prob_3"]].rename(columns={"prob_1": "fold 1", "prob_2": "fold 2", "prob_3": "fold 3"}).corr(), annot=True, linewidths=0.5, ax=ax2, vmin=-1.0, vmax=1.0)
ax2.set_title("All incorrect (000)")
plt.tight_layout()
plt.show()
plt.close()

# %%
