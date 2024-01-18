# %% hypothesis test
from case_studies.manual_analysis import *

from scipy.stats import ttest_ind, probplot, mannwhitneyu
import matplotlib.pyplot as plt
from pathlib import Path
import sys

#%%
import argparse
p = argparse.ArgumentParser()
p.add_argument("--output_dir")
args, _ = p.parse_known_args()

output_dir = Path(args.output_dir)

#%%
def hyp_test_feat(featname, output_dir=None):
    if output_dir is not None:
        output_dir = Path(output_dir)
        output_dir.mkdir(exist_ok=True)
        output_file = open(output_dir/"log.txt", "a")
    else:
        output_file = sys.stdout

    print(featname, file=output_file)
    if featname in ("offset", "example_index"):
        print("skipped", file=output_file)
        return
    inc_x = [d[featname] for d in inc]
    c_x = [d[featname] for d in c]

    # assess normality - QQ
    fig, ax = plt.subplots(2)
    ax[0].set_title(f"QQ plot {featname} for correct")
    probplot(inc_x, dist="norm", plot=ax[0])
    ax[1].set_title(f"QQ plot {featname} for correct")
    probplot(c_x, dist="norm", plot=ax[1])
    plt.tight_layout()
    if output_dir is not None:
        plt.savefig(output_dir/f"qq_{featname}.png")
    # else:
    #     plt.show()
    plt.close()
    
    # assess normality - histogram
    fig, ax = plt.subplots(2)
    ax[0].set_title(f"distribution of {featname} for incorrect")
    sns.histplot(inc_x, ax=ax[0])
    ax[1].set_title(f"distribution of {featname} for correct")
    sns.histplot(c_x, ax=ax[1])
    plt.tight_layout()
    if output_dir is not None:
        plt.savefig(output_dir/f"hist_{featname}.png")
    # else:
    #     plt.show()
    plt.close()

    # hypothesis test
    print(featname, "inc head:", inc_x[:5], file=output_file)
    print(featname, "c head:", c_x[:5], file=output_file)
    inc_x_mean = np.mean(inc_x)
    c_x_mean = np.mean(c_x)
    print(featname, "inc mean value:",inc_x_mean, file=output_file)
    print(featname, "c mean value:",c_x_mean, file=output_file)
    inc_x_std = np.std(inc_x)
    c_x_std = np.std(c_x)
    print(featname, "inc std value:",inc_x_std, file=output_file)
    print(featname, "c std value:",c_x_std, file=output_file)
    ttest,pval = ttest_ind(inc_x,c_x)
    print(featname, "t p-value",pval, file=output_file)
    if pval < 0.05:
        print("we reject null hypothesis", file=output_file)
    else:
        print("we accept null hypothesis", file=output_file)
    test,pval = mannwhitneyu(inc_x,c_x)
    print(featname, "MWU p-value",pval, file=output_file)
    if pval < 0.05:
        print("we reject null hypothesis", file=output_file)
    else:
        print("we accept null hypothesis", file=output_file)

hyp_test_feat("num_pointer", None)

#%%

featnames = sorted(set(inc[0].keys()) | set(c[0].keys()))
if (output_dir/"log.txt").exists():
    (output_dir/"log.txt").unlink()
for featname in featnames:
    hyp_test_feat(featname, output_dir)

# %%
