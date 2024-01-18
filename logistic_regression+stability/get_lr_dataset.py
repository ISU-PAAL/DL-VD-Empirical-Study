# %%
from collections import defaultdict
from analysis.util import is_notebook

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
def tryout():
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
# tryout()

#%%
def process_group(code, print_ast=False):
    counts = defaultdict(int)
    
    tree = parse(code)
    q = [(tree.root_node, 0)]
    while q:
        n, indent = q.pop()
        if n.is_named:
            counts[n.type] += 1
            if print_ast:
                code_short = n.text.decode()
                code_short_lines = code_short.splitlines()
                if len(code_short_lines) > 1:
                    code_short = code_short_lines[0].rstrip() + "..."
                print("\t" * indent + n.type, code_short)
        q.extend([(c, indent+1) for c in n.children])
    
    return counts

def get_counts(select_df):
    ds = []
    for tup in select_df.sort_values("model").drop_duplicates("example_index").itertuples():
        example_info = {
            "example_index": tup.example_index,
            "code": tup.code,
        }
        counts = process_group(tup.code)
        example_info.update(dict(counts))
        ds.append(example_info)

    return ds

#%%
def get_counts_new(code_df):
    ds = []
    for tup in code_df.itertuples():
        example_info = {
            "example_index": tup.example_index,
            "code": tup.code,
        }
        counts = process_group(tup.code)
        example_info.update(dict(counts))
        ds.append(example_info)

    df = pd.DataFrame(data=ds)
    return df

#%%
import pandas as pd
def get_dataset(df, split):
    if split is not None:
        df = df[df["split"] == split]
    correct = df[df["num_correct"] == df["num_correct"].max()]
    incorrect = df[df["num_correct"] == 0]

    inc = get_counts(incorrect)
    c = get_counts(correct)
    inc_df = pd.DataFrame(data=inc).assign(correct=False)
    c_df = pd.DataFrame(data=c).assign(correct=True)
    ds = pd.concat((inc_df, c_df))
    ds = ds.fillna(0).astype({col: int for col in ds.columns if col not in ("correct", "code",)})
    return ds

#%%
# from analysis.data_sources.devign import *

# ds = get_dataset(devign_df, "test")
# ds
