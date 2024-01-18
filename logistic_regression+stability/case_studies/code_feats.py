#%%
import collections
import itertools
from util import *

def get_code_feats(ds):
    # define group selectors
    nonfeature_columns = [
        'ERROR',
        'example_index',
        'code',
        'translation_unit',
        'function_definition',
        'function_declarator',
        'correct',
        'compound_statement',
        "parameter_list",
        "argument_list",
        "declaration_list",
        "field_declaration_list",
        "comma_expression",
        "parenthesized_expression",
        "system_lib_string",
        'enumerator',
        'enumerator_list',
    ]
    declarations = [
        c for c in ds.columns if
            (c.endswith("_declarator") and c not in ("init_declarator", "function_declarator"))
            or c.endswith("declaration")
            ]
    macros = [
        c for c in ds.columns if
            (
                c.startswith("preproc_") and c not in ("preproc_include",)
            )
            or
            (
                c.startswith("macro_") and c not in ("macro_type_specifier")
            )
            ]
    pointers = [
        "field_expression",
        "pointer_expression",
    ]
    arrays = [
        "subscript_designator",
        "subscript_expression",
    ]
    update_expressions = [
        "update_expression", "assignment_expression"
    ]
    nonupdate_expressions = [
        c for c in ds.columns if
            c.endswith("_expression") and c not in ("comma_expression", "parenthesized_expression", "call_expression", "compound_literal_expression", "update_expression", "assignment_expression") and c not in pointers
            ]
    literals = [
        'false',
        'null',
        'true',
        'concatenated_string',
        'number_literal',
        'string_literal',
        'char_literal',
    ]
    initializations = [
        c for c in ds.columns if
            (c.endswith("_designator") and c not in pointers)
            or c.startswith("initializer_")
            or c in (
                "variadic_parameter",
                "init_declarator",
                "compound_literal_expression",
            )]
    identifiers = [
        c for c in ds.columns if
            (c == "identifier" or c.endswith("identifier") and c not in ("type_identifier"))
            ]
    types = [
        'primitive_type',
        'macro_type_specifier',
        'type_identifier',
        'storage_class_specifier',
        'sized_type_specifier',
        'type_descriptor',
        'type_qualifier',
    ]
    specifiers = [
        c for c in ds.columns if
            (
                c.endswith("_specifier")
                and c not in (
                    "macro_type_specifier",
                    'storage_class_specifier',
                    'sized_type_specifier'
                )
            )]

    # aggregate groups
    feature_sets = {
        "feat.declarations": declarations,
        "feat.macros": macros,
        # "feat.assignment_expressions": update_expressions,
        # "feat.nonassignment_expressions": nonupdate_expressions,
        "feat.literals": literals,
        # "feat.initializations": initializations,
        "feat.identifiers": identifiers,
        "feat.pointers": pointers,
        "feat.arrays": arrays,
        "feat.while_dowhile": ["while_statement", "do_statement"],
        "feat.jumps": ["break_statement", "continue_statement", "return_statement"],
        "feat.unstructured": ["labeled_statement", "goto_statement"],
        "feat.switch_case": ["switch_statement", "case_statement"],
        "feat.types": types,
        "feat.specifiers": specifiers,
    }
    # get singles
    singles = [c for c in ds.columns if not any(c in s for s in [nonfeature_columns, *feature_sets.values()])]
    for f in singles:
        feature_sets[f'feat.single.{f}'] = [f]
    # get misc features not possible to extract by tree-sitter
    ds["feat.__asm__"] = ds["code"].str.count("__asm__")
    ds["feat.lexical.num_chars"] = ds["code"].apply(lambda s: len(s))
    # ds["feat.lexical.num_tokens"] = ds["code"].apply(lambda s: len(s.split()))
    # ds["feat.lexical.num_lines"] = ds["code"].apply(lambda s: len(s.splitlines()))
    # assert mutually exclusive categories
    combined = list(itertools.chain(*feature_sets.values()))
    non_uniq_cols = [item for item, count in collections.Counter(combined).items() if count > 1]
    assert len(non_uniq_cols) == 0, non_uniq_cols
    # Add columns for feature groups
    for setname, columns in feature_sets.items():
        columns = [c for c in columns if c in ds.columns]
        ds[setname] = ds[columns].sum(axis=1).fillna(0).astype(int)
    return ds

#%%
# if is_notebook():
#     from data_sources.devign import *
#     from case_studies.get_lr_dataset import *
#     ds = get_dataset(devign_df, "test")
#     print(ds)

#%%
code_feats_to_observe = [
    "feat.macros",
    "feat.__asm__",
    "feat.lexical.num_chars",
    "feat.pointers",
    "feat.arrays",
    "feat.single.for_statement",
    "feat.single.call_expression",
    "feat.single.if_statement",
    "feat.while_dowhile",
    "feat.jumps",
    "feat.unstructured",
    "feat.switch_case",
    "feat.single.comment",
]
