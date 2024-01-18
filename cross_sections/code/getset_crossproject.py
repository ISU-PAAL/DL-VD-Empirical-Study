# %%
import pandas as pd
import numpy as np
from getset_root import msr_df


#%% RQb4 cross project setting
keepcols = ["dataset", "example_index", "project", "commit_id"]
source_df = msr_df[keepcols].sort_values("example_index")
source_df

#%%
import numpy as np
rs = np.random.RandomState(seed=0)

exclude_from_holdout = source_df.value_counts("project").head(2).index.tolist()
holdout_source = source_df[~source_df["project"].isin(exclude_from_holdout)]
holdout_source = holdout_source.rename_axis('index').sort_values(["project", "index"])
holdout_source

#%%
# holdout_size_goal = len(source_df) // 10
groups = [df for _, df in holdout_source.groupby('project')]
rs.shuffle(groups)
holdout_source = pd.concat(groups, ignore_index=False)

holdout_size_goal = 10000
source_projects = holdout_source["project"].drop_duplicates().tolist()
holdout_project_lists = []
while len(source_projects) > 0:
    holdout_projects = []
    holdout_size = 0
    broke = False
    while holdout_size < holdout_size_goal:
        if len(source_projects) == 0:
            broke = True
            break
        project = source_projects.pop(0)
        holdout_projects.append(project)
        holdout_size += len(holdout_source[holdout_source["project"] == project])
    if broke:
        break
    print(len(holdout_projects), holdout_size, holdout_size / len(source_df), len(source_df))
    holdout_project_lists.append(holdout_projects)
for i in range(len(holdout_project_lists)):
    for j in range(len(holdout_project_lists)):
        if i != j:
            assert len(set(holdout_project_lists[i]).intersection(set(holdout_project_lists[j]))) == 0, "sets should be mutually exclusive"

#%%


vcs = []
vcs2 = []
for i, pl in enumerate(holdout_project_lists):
    # export cross-project
    def split1(df, holdout_df):
        rs = np.random.RandomState(seed=0)
        test_num = len(holdout_df)
        val_num = holdout_size_goal
        split = pd.Series(range(len(df)), index=rs.permutation(df.index)).apply(lambda i: "test" if i < test_num else ("valid" if i < test_num + val_num else "train"))
        return split
    is_heldout = source_df["project"].isin(pl)
    holdout_df = source_df[is_heldout]
    rest_df = source_df[~is_heldout]
    assert len(set(holdout_df["example_index"]).intersection(rest_df["example_index"])) == 0, "sets should be mutually exclusive"
    holdout_df = holdout_df.assign(split="holdout")
    rest_df = rest_df.assign(split=split1(rest_df, holdout_df))
    holdout_df.sort_values("example_index").to_csv(f"data/subsets/cross_project/fold_{i}_holdout.csv")
    rest_df.sort_values("example_index").to_csv(f"data/subsets/cross_project/fold_{i}_dataset.csv")
    assert len(rest_df[rest_df["split"] == "test"]) == len(holdout_df), "test set should be the same size as holdout set"
    vcs.append(pd.concat((rest_df.value_counts("split").to_frame(), holdout_df.value_counts("split").to_frame())))

    # export project-diversity
    def split2(df):
        rs = np.random.RandomState(seed=0)
        valid_num = holdout_size_goal
        split = pd.Series(range(len(df)), index=rs.permutation(df.index)).apply(lambda i: "valid" if i < valid_num else "train")
        return split

    if i == 0:
        # Export nondiverse set separately
        A_projects = (
            source_df
                .value_counts("project")
                .sort_values(ascending=False)
                .head(1)
                .index.tolist()
            )
        # A_projects = ["linux"]
        A = source_df[source_df["project"].isin(A_projects)]
        A = A.assign(split=split2(A), subset="non-diverse")
        A.sort_values("example_index").to_csv(f"data/subsets/project_diversity/nondiverse.csv")
        A_vc = A.value_counts(["subset", "split"]).to_frame()

    assert len(set(holdout_df["example_index"]).intersection(A["example_index"])) == 0, "sets should be mutually exclusive"
    holdout_df.sort_values("example_index").to_csv(f"data/subsets/project_diversity/fold_{i}_holdout.csv")

    rs2 = np.random.RandomState(seed=0)
    B = rest_df[~rest_df["project"].isin(A_projects)].sample(n=len(A), random_state=rs2)
    assert len(set(B["example_index"]).intersection(holdout_df["example_index"])) == 0, "sets should be mutually exclusive"
    assert len(set(B["example_index"]).intersection(A["example_index"])) == 0, "sets should be mutually exclusive"
    B = B.assign(split=split2(B), subset="diverse")
    B.sort_values("example_index").to_csv(f"data/subsets/project_diversity/fold_{i}_diverse.csv")
    vcs2.append(pd.concat((A_vc, B.value_counts(["subset", "split"]).to_frame(), holdout_df.value_counts("split").to_frame())))

# %% print value counts of different splits
vcs_df = pd.concat(vcs, axis=1, ignore_index=True)
print("cross-project split counts:")
print(vcs_df)
print("cross-project split counts (normalized):")
print(vcs_df / vcs_df.sum(axis=0))

vcs2_df = pd.concat(vcs2, axis=1, ignore_index=True)
print("project-diversity split counts:")
print(vcs2_df)
print("project-diversity split counts (normalized):")
print(vcs2_df / vcs2_df.sum(axis=0))

#%%
def get_label_counts(df):
    df = df.join(msr_df[["vul"]])
    df["target"] = df["vul"].apply(lambda vul: [1, 0] if vul == 1 else [0])
    df = df.explode("target")
    print("total:", len(df))
    print(df.value_counts("target", normalize=True))
    for splitname, group in df.groupby("split"):
        print(splitname, len(group))
        print(group.value_counts("target", normalize=True))

import glob
import pandas as pd
import tqdm
import os
for cross_project_fpath in tqdm.tqdm(glob.glob("data/subsets/cross_project/fold_*_holdout.csv"), desc="check folds"):
    diversity_fpath = os.path.join("data/subsets/project_diversity", os.path.basename(cross_project_fpath))
    cross_project_holdout = pd.read_csv(cross_project_fpath, index_col=0)
    diversity_holdout = pd.read_csv(diversity_fpath, index_col=0)
    pd.testing.assert_frame_equal(cross_project_holdout, diversity_holdout)

    cross_project_dataset_fname = os.path.join(os.path.dirname(cross_project_fpath), os.path.basename(cross_project_fpath).replace("_holdout", "_dataset"))
    cross_project_dataset = pd.read_csv(cross_project_dataset_fname, index_col=0)
    assert len(set(cross_project_holdout["example_index"].tolist()).intersection(cross_project_dataset["example_index"].tolist())) == 0, "sets should be distinct"

    diverse_fname = os.path.join(os.path.dirname(diversity_fpath), os.path.basename(diversity_fpath).replace("_holdout", "_diverse"))
    diverse_dataset = pd.read_csv(diverse_fname, index_col=0)
    nondiverse_fname = os.path.join(os.path.dirname(diversity_fpath), "nondiverse.csv")
    nondiverse_dataset = pd.read_csv(nondiverse_fname, index_col=0)
    assert len(set(diverse_dataset["example_index"].tolist()).intersection(diversity_holdout["example_index"].tolist())) == 0, "sets should be distinct"
    assert len(set(nondiverse_dataset["example_index"].tolist()).intersection(diversity_holdout["example_index"].tolist())) == 0, "sets should be distinct"
    assert len(set(nondiverse_dataset["example_index"].tolist()).intersection(diverse_dataset["example_index"].tolist())) == 0, "sets should be distinct"

    print("cross_project_dataset")
    get_label_counts(pd.concat((cross_project_dataset, cross_project_holdout)))
    print("diverse_dataset")
    get_label_counts(pd.concat((diverse_dataset, diversity_holdout)))
    print("nondiverse_dataset")
    get_label_counts(pd.concat((nondiverse_dataset, diversity_holdout)))

#%%
import glob
import pandas as pd

for fname in sorted(glob.glob("data/subsets/project_diversity/*.csv")):
    df = pd.read_csv(fname)
    print(fname, df["project"].nunique())
