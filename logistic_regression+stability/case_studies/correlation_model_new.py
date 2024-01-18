#%% code dataset
from sklearn.preprocessing import StandardScaler
from sklearn.feature_selection import VarianceThreshold

def get_preprocessed_code_feats(ds, feat_selection="VarianceThreshold", preprocessing="StandardScaler"):
    x = ds[[c for c in ds.columns if c.startswith("feat")]]
    y = ds["correct"]

    if feat_selection == "VarianceThreshold":
        sel = VarianceThreshold(threshold=(.1)).fit(x.to_numpy())
        feats_in = x.columns.tolist()
        feats_out = sel.get_feature_names_out(input_features=feats_in)
        print("removed feats:", list(sorted(set(feats_in) - set(feats_out))))
        x = x[feats_out]

    if preprocessing == "StandardScaler":
        x_values = x.to_numpy()

        scaler = StandardScaler()
        print("Before normalize:")
        print(x_values.mean(axis=0))
        print(x_values.std(axis=0))
        x_values = scaler.fit_transform(x_values)
        print("After normalize:")
        print(x_values.mean(axis=0))
        print(x_values.std(axis=0))

        x.loc[:] = x_values

    return x, y

#%%
from case_studies.code_feats import *
from data_sources.devign import *
from case_studies.get_lr_dataset import *
ds = get_dataset(devign_df, "test")
ds = get_code_feats(ds)
ds

#%%
x, y = get_preprocessed_code_feats(ds)

#%%
import statsmodels.api as sm

logit_mod = sm.Logit(y, x)
logit_res = logit_mod.fit()
print("Parameters:")
print(logit_res.params.sort_values())
margeff = logit_res.get_margeff()
print("Marginal effects:")
print(margeff.summary())

# %%
import io

result_df = pd.read_csv(io.StringIO(margeff.summary().tables[1].as_csv()))
result_df.columns = [c.strip() for c in result_df.columns]
result_df = result_df.sort_values("P>|z|")
result_df["name"] = result_df[""].str.strip()
result_df = result_df.set_index("name")
result_df = result_df.drop(columns=[""])
result_df = result_df.join(logit_res.params.rename("coeff"))
result_df

#%%
result_df[result_df["P>|z|"] <= 0.05]

#%%
result_df[result_df["P>|z|"] > 0.05].sort_values("coeff")

# %%
