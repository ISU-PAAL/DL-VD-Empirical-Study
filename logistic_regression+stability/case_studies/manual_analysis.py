# %%
from collections import defaultdict


from data_sources.devign import *
from data_sources.devign_msr import *
from data_sources.regvd import *
from data_sources.codebert import *
from data_sources.random_data import *
from data_sources.random_values import *
from data_sources.vulberta import *

# %%
"""
Setup:
1. git clone https://github.com/tree-sitter/tree-sitter-c in the same directory
2. pip3 install tree_sitter to install dependencies
3. Parse code using this one liner tree = c_parser.parse(bytes(code, "utf8")). The resulting object tree is an AST of the program. Access the root node with tree.root_node. Walk children of a single node using node.children, get text of a single node using node.text.decode().
"""
from tree_sitter import Language, Parser

Language.build_library(
  # Store the library in the `build` directory
  'build/my-languages.so',

  # Include one or more languages
  [
    'tree-sitter-c',
  ]
)

C_LANGUAGE = Language('build/my-languages.so', 'c')
c_parser = Parser()
c_parser.set_language(C_LANGUAGE)

def parse(code):
    """Return AST representation of code"""
    return c_parser.parse(bytes(code, "utf8"))

def convert_result(result):
    if isinstance(result, int):
        return result
    elif isinstance(result, bool) and result:
        return 1
    else:
        return None

def walk(node, fn):
    """Do BFS and apply fn to each node"""
    result = convert_result(fn(node))
    for c in node.children:
        child_result = convert_result(walk(c, fn))
        if child_result is not None:
            result += child_result
    return result

#%% sandbox for parsing code
tree = parse("""int main(int argc)
{
    switch (argc)
    {
        case 0:
            break;
    }
    return 1;
}
""")
walk(tree.root_node, lambda n: print(n.type, n.text.decode()))

# %%
# select_split = "train"
# df = df[df["split"] == select_split]

# all_seeds_incorrect_df = devign_reveal_df[devign_reveal_df["num_correct"] == 0]
# all_seeds_correct_df = devign_reveal_df[devign_reveal_df["num_correct"] == 3]

# all_models_incorrect = all_seeds_incorrect_df[all_seeds_incorrect_df.groupby("example_index")["model"].transform(lambda g: g.nunique()) == 3]
# all_models_correct = all_seeds_correct_df[all_seeds_correct_df.groupby("example_index")["model"].transform(lambda g: g.nunique()) == 3]

# other = devign_reveal_df[devign_reveal_df["num_correct"].isin((0, 3))]
# other = other[~other.index.isin(all_models_incorrect.index)]

# devign_incorrect = all_seeds_incorrect_df[(all_seeds_incorrect_df["model"] == "devign")]
# devign_correct = all_seeds_correct_df[(all_seeds_correct_df["model"] == "devign")]

# regvd_correct = regvd_df[(regvd_df["model"] == "GNN-ReGVD") & (regvd_df["num_correct"] == 3)]
# regvd_incorrect = regvd_df[(regvd_df["model"] == "GNN-ReGVD") & (regvd_df["num_correct"] == 0)]

# select_df = devign_incorrect

# select_df

#%%

def get_suspicious(select_df):
    # merge_df = pd.merge(select_df, code_df.reset_index(), how="left", left_on="example_index", right_on="index")
    all_suspicious = defaultdict(int)

    # TODO: detect this expression: 
    """
    k->read_block_from_card = sdhci_read_block_from_card;
    k->write_block_to_card = sdhci_write_block_to_card;
    k->bdata_read = sdhci_read_dataport;
    k->bdata_write = sdhci_write_dataport;
    """

    def process_group(group):
        suspicious = defaultdict(int)
        suspicious["example_index"] = group.iloc[0].example_index
        code = group.iloc[0].code
        
        tree = parse(code)

        num_expressions = walk(tree.root_node, lambda n: n.type.endswith("_expression"))
        suspicious["num_expressions"] = num_expressions

        num_call_expressions = walk(tree.root_node, lambda n: n.type == ("call_expression"))
        suspicious["num_call_expressions"] = num_call_expressions
        if num_call_expressions >= ((num_expressions // 5) * 4):
            # print("ALL CALL", file=of)
            suspicious["> 80% call"] += 1

        num_field = walk(tree.root_node, lambda n: n.type in ("field_expression",))
        num_subscript = walk(tree.root_node, lambda n: n.type in ("subscript_expression"))
        num_pointer = walk(tree.root_node, lambda n: n.type in ("pointer_expression"))
        num_indirect = num_field + num_subscript + num_pointer
        suspicious["num_field"] = num_field
        suspicious["num_subscript"] = num_subscript
        suspicious["num_pointer"] = num_pointer
        if num_indirect >= ((num_expressions // 2)):
            # print("ALL INDIRECT", file=of)
            suspicious["> 50% indirect"] = 1

        suspicious["percent_call_expressions"] = num_call_expressions / num_expressions if num_expressions > 0 else 0
        suspicious["percent_field"] = num_field / num_expressions if num_expressions > 0 else 0
        suspicious["percent_subscript"] = num_subscript / num_expressions if num_expressions > 0 else 0
        suspicious["percent_pointer"] = num_pointer / num_expressions if num_expressions > 0 else 0

        if num_call_expressions + num_indirect >= ((num_expressions // 5) * 4):
            # print("ALL INDIRECT OR CALL", file=of)
            suspicious["all_indirect_or_call"] = 1
        
        suspicious["num_asm"] = code.count("__asm__")
        if "__asm__" in code:
            # print("ASM", file=of)
            suspicious["asm"] = 1
        
        num_switches = walk(tree.root_node, lambda n: n.type == "switch_statement")
        suspicious["num_switches"] = num_switches
        if num_switches > 0:
            # print("SWITCH", file=of)
            suspicious["switch"] = 1

        num_cases = walk(tree.root_node, lambda n: n.type == "case")
        suspicious["num_cases"] = num_cases
        if num_cases > 10:
            # print(">10 CASES", file=of)
            suspicious["> 10 cases"] = 1

        num_macros = walk(tree.root_node, lambda n: n.type.startswith("preproc"))
        suspicious["num_macros"] = num_macros
        if num_macros > 0:
            # print("MACRO", file=of)
            suspicious["has_macro"] = 1
        
        suspicious["len"] = len(code.split())
        if len(code.split()) > 300:
            # print("LONG", file=of)
            suspicious["long"] = 1

        num_gotos = walk(tree.root_node, lambda n: n.type ==("goto"))
        suspicious["num_gotos"] = num_gotos
        if num_gotos > 0:
            # print("GOTO", file=of)
            suspicious["has_goto"] = 1

        num_ifs = walk(tree.root_node, lambda n: n.type == "if_statement")
        suspicious["num_ifs"] = num_ifs
        num_whiles = walk(tree.root_node, lambda n: n.type in ("while_statement", "do_statement"))
        suspicious["num_whiles"] = num_whiles
        num_fors = walk(tree.root_node, lambda n: n.type == "for_statement")
        suspicious["num_fors"] = num_fors
        
        # print("FAILURES:", group.model.unique().tolist(), file=of)
        # for tup in group.itertuples():
        #     print(f"{tup.example_index=} {tup.model=} {tup.seed=} {tup.prediction=} {tup.target=}", file=of)
        # print(code, file=of)
        # print("\n", file=of)
        return suspicious
    # 
    ds = []
    # with open("code.txt", "w") as of:
    for _, group in select_df.sort_values("model").groupby("example_index"):
        suspicious = process_group(group)

        for key, val in suspicious.items():
            if key not in ("example_index",):
                all_suspicious[key] += val
        ds.append(suspicious)

    # codes_written = select_df["example_index"].nunique()
    # print(codes_written, "codes written.")
    # for sus_item in sorted(all_suspicious):
    #     count = all_suspicious[sus_item]
    #     print(sus_item, "=", count, f"({count / codes_written*100:.2f}%)")
    return ds

#%%
from util import is_notebook

print("running as notenook:", is_notebook())
if is_notebook():
    # hardcoded
    select_split = "test"
    nn_model_type = "devign"
else:
    import argparse
    p = argparse.ArgumentParser()
    p.add_argument("--select_split", choices=["train", "valid", "test"])
    p.add_argument("--nn_model_type", choices=["GNN-ReGVD", "devign", "devign_msr", "codebert", "vulberta", "random_data", "random_values"])
    args, _ = p.parse_known_args()
    print("arguments:", args)
    select_split = args.select_split
    nn_model_type = args.nn_model_type
if nn_model_type == "GNN-ReGVD":
    select_df = regvd_df
elif nn_model_type == "devign":
    select_df = devign_df[devign_df["model"] == nn_model_type]
elif nn_model_type == "devign_msr":
    select_df = devign_msr_df
elif nn_model_type == "codebert":
    select_df = codebert_df
elif nn_model_type == "vulberta":
    select_df = vulberta_df
elif nn_model_type == "random_data":
    select_df = random_data_df
elif nn_model_type == "random_values":
    select_df = random_values_df
else:
    raise NotImplementedError(nn_model_type)
select_df = select_df[select_df["split"] == select_split]
correct = select_df[select_df["num_correct"] == select_df["num_correct"].max()]
incorrect = select_df[select_df["num_correct"] == 0]

features = [
    "num_expressions",
    "num_call_expressions",
    "num_field",
    "num_subscript",
    "num_pointer",
    # "percent_call_expressions",
    # "percent_field",
    # "percent_subscript",
    # "percent_pointer",
    "num_asm",
    # "num_switches",
    "num_cases",
    "num_macros",
    "num_gotos",
    "num_ifs",
    "num_whiles",
    "num_fors",
    "len",
]
inc = get_suspicious(incorrect)
inc_ds = [[d[f] for f in features] for d in inc]
c = get_suspicious(correct)
c_ds = [[d[f] for f in features] for d in c]

