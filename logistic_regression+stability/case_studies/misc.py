# %%
from data_sources.devign import *
import seaborn as sns
from matplotlib import pyplot as plt

# %% correlation between probability and predict positive
all_df["all_same"] = all_df["num_predict_positive"].isin((0, 3)).astype(int)
fig, ax = plt.subplots(3, 1)
for i, (model, group) in enumerate(all_df.groupby("model")):
    corr = group[["all_same", "prob strength"]].corr()
    sns.heatmap(corr, vmax=1.0, vmin=-1.0, annot=True, ax=ax[i])
    ax[i].set_title(model)
    plt.title(model)
fig.suptitle("correlation between # positive predictions and probability")
plt.savefig("positive_prob.png")
plt.tight_layout()
plt.show()

#%% bar chart of num correct
sns.histplot(
    data=all_df, x="num_correct", hue="model",
    multiple="dodge",
    discrete=True,
    shrink=.8,
    # binwidth=1,
    stat="percent",
    )
plt.xticks([0, 1, 2, 3])
plt.xlabel("# seeds correct by example")
plt.ylabel("% examples")
plt.savefig("num_correct.png")
plt.show()
plt.close()
