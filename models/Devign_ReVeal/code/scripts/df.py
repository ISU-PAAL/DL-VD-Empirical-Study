#%%
import pandas as pd

df1 = pd.DataFrame(data=[
    ["A", "B", "C"],
    ["D", "E", "F"],
    ["G", "h", "I"],
])
df1["split"] = "train"
df2 = pd.DataFrame(data=[
    ["AA", "AB", "AC"],
    ["AD", "AE", "AF"],
    ["AG", "Ah", "AI"],
])
df2["split"] = "valid"

# %%
dfc = pd.concat((df1, df2), ignore_index=True)
dfc
