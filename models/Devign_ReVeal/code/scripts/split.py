#%%
import pandas as pd
import numpy as np
import sys
# df = pd.read_csv("data/subsets/project/set_A.csv", index_col=0).reset_index(drop=True)

#%%
def split(df):
    rs = np.random.RandomState(seed=0)
    train_end = int(len(df) * 0.8)
    valid_end = int(len(df) * 0.9)
    split = pd.Series(range(len(df)), index=rs.permutation(df.index)).apply(lambda i: "train" if i <= train_end else ("valid" if i <= valid_end else "test"))
    # print(df.value_counts("split", normalize=True))
    return split

#%%
if __name__ == "__main__":
    df = pd.read_csv(sys.argv[1], index_col=0).reset_index(drop=True)
    df["split"] = split(df)
    df.to_csv(sys.argv[2])
