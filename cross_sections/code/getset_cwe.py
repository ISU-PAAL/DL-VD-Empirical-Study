# %%
import pandas as pd
import numpy as np
from getset_root import msr_df

#%%
keepcols = ["dataset", "example_index", "project", "commit_id", "target", "CWE ID"]
source_df = msr_df[keepcols]

#%%
# RQ.A2
# Gather groups of similar bugs

"""
LOG:
"""

# vc = source_df.value_counts("CWE ID")
# vc

# %%
# RQ.A2
# Divide the dataset by bug type into relatively equal, sufficiently large subsets
# all_df = df
# all_df.name = "all examples"
# vc = all_df.value_counts("CWE ID").to_frame().rename(columns={0: "Count"})
# print(vc.to_csv())

#%%
from lxml import etree

import networkx as nx

# G = nx.DiGraph()
tree = etree.parse("/home/<ANONYMOUS>/code/linevd/storage/external/1000.xml")

# i = 0
# q = [(tree.getroot().xpath("//c:Weaknesses", namespaces={'c': 'http://cwe.mitre.org/cwe-6',})[0], None)]
# while q:
#     n, p = q.pop(0)
#     i += 1
#     node = G.add_node(i, xml_node=n)
#     if p is not None:
#         G.add_edge(p, i)
#     q.extend([(c, i) for c in n.getchildren()])
# print(G)

vc = source_df.value_counts("CWE ID").to_dict()

from matplotlib import pyplot as plt
weaknesses = tree.getroot().xpath("//c:Weakness", namespaces={'c': 'http://cwe.mitre.org/cwe-6',})
len(weaknesses)
count_0 = []
G = nx.DiGraph()
for w in weaknesses:
    related = w.xpath(".//c:Related_Weakness", namespaces={'c': 'http://cwe.mitre.org/cwe-6',})
    parents = [r for r in related if r.attrib["Nature"] == "ChildOf"]
    children = [r for r in related if r.attrib["Nature"] == "ParentOf"]
    if "CWE_ID" not in w.attrib and "ID" not in w.attrib:
        print(w.attrib)
    w_id = int(w.attrib.get("CWE_ID", w.attrib.get("ID")))
    c_ids = [int(c.attrib.get("CWE_ID", c.attrib.get("ID"))) for c in children]
    p_ids = [int(p.attrib.get("CWE_ID", p.attrib.get("ID"))) for p in parents]
    G.add_edges_from([(w_id, c_id) for c_id in c_ids if not G.has_edge(w_id, c_id)])
    G.add_edges_from([(p_id, w_id) for p_id in p_ids if not G.has_edge(p_id, w_id)])
    desc = w.attrib["Name"]
    G.nodes[w_id]["desc"] = desc
    count = vc.get(f"CWE-{w_id}", 0)
    G.nodes[w_id]["label"] = f"CWE-{w_id} ({count}):\n{desc}"
    G.nodes[w_id]["count"] = count
    G.nodes[w_id]["fillcolor"] = "red" if count == 0 else "white"
    G.nodes[w_id]["style"] = "filled"
    if count == 0:
        count_0.append(w_id)

G = nx.transitive_closure(G)
G.remove_nodes_from(count_0)

# #%%
# descendant_graphs = {}
# for n, attr in G.nodes(data=True):
#     descendant_graph = G.subgraph(list(nx.descendants(G, n)) + [n]).copy()
#     descendant_graph.nodes[n]["fillcolor"] = "lightblue"
#     all_count = sum(attr["count"] for n, attr in descendant_graph.nodes(data=True))
#     cwe = attr["desc"]
#     if len(list(G.predecessors(n))) == 0:
#         from networkx.drawing.nx_agraph import to_agraph
#         with open(f"graph_{n}_{cwe}_{all_count}.dot", "w") as f:
#             f.write(str(to_agraph(descendant_graph)))
#         print(n, attr["desc"])
#         print("\n".join([str(i) + " " + iattr["desc"] for i, iattr in descendant_graph.nodes(data=True) if i != n]))
#         print()
#         descendant_graphs[n] = descendant_graph

# #%%
# mapping = {
#     "Security": [754, 74, 693, 284],
#     "BOF": [119],
# }
# for k, v in mapping.items():
#     group_nodes = set()
#     group_count = 0
#     for i in v:
#         group_nodes.update(descendant_graphs[i].nodes())
#         group_count += sum(attr["count"] for n, attr in descendant_graphs[i].nodes(data=True))
#     print(k, group_count, ",".join([str(i) for i in sorted(group_nodes)]), sep=",")

#%%

# %%bash
# for f in graph_*_*.dot; do sfdp -x -Goverlap=scale -Efontsize=600 -Tsvg "$f" > "${f}.svg";done

#%%
groups = {}
# outgoing information flow/taint or access ring violations
groups["privilege_escalation_authorization"] = """
693 Protection Mechanism Failure
327 Use of a Broken or Risky Cryptographic Algorithm
330 Use of Insufficiently Random Values
331 Insufficient Entropy
311 Missing Encryption of Sensitive Data
358 Improperly Implemented Security Check for Standard

352 Cross-Site Request Forgery (CSRF)

918 Server-Side Request Forgery (SSRF)

1021 Improper Restriction of Rendered UI Layers or Frames

668 Exposure of Resource to Wrong Sphere

284 Improper Access Control
269 Improper Privilege Management

285 Improper Authorization
862 Missing Authorization

732 Incorrect Permission Assignment for Critical Resource
281 Improper Preservation of Permissions

287 Improper Authentication
290 Authentication Bypass by Spoofing
295 Improper Certificate Validation
522 Insufficiently Protected Credentials

200 Exposure of Sensitive Information to an Unauthorized Actor
209 Generation of Error Message Containing Sensitive Information
532 Insertion of Sensitive Information into Log File

345 Insufficient Verification of Data Authenticity
346 Origin Validation Error
347 Improper Verification of Cryptographic Signature
"""

# ingoing information flow/taint
groups["input_validation"] = """
354 Improper Validation of Integrity Check Value

134 Use of Externally-Controlled Format String
20 Improper Input Validation
426 Untrusted Search Path
59 Improper Link Resolution Before File Access ('Link Following')
706 Use of Incorrectly-Resolved Name or Reference
601 URL Redirection to Untrusted Site ('Open Redirect')
494 Download of Code Without Integrity Check
502 Deserialization of Untrusted Data

22 Improper Limitation of a Pathname to a Restricted Directory ('Path Traversal')
74 Improper Neutralization of Special Elements in Output Used by a Downstream Component ('Injection')
77 Improper Neutralization of Special Elements used in a Command ('Command Injection')
78 Improper Neutralization of Special Elements used in an OS Command ('OS Command Injection')
79 Improper Neutralization of Input During Web Page Generation ('Cross-site Scripting')
89 Improper Neutralization of Special Elements used in an SQL Command ('SQL Injection')
90 Improper Neutralization of Special Elements used in an LDAP Query ('LDAP Injection')
93 Improper Neutralization of CRLF Sequences ('CRLF Injection')
94 Improper Control of Generation of Code ('Code Injection')
611 Improper Restriction of XML External Entity Reference
"""

groups["resource_allocation_free"] = """
664 Improper Control of a Resource Through its Lifetime

415 Double Free
416 Use After Free
770 Allocation of Resources Without Limits or Throttling
772 Missing Release of Resource after Effective Lifetime
909 Missing Initialization of Resource
400 Uncontrolled Resource Consumption
404 Improper Resource Shutdown or Release
665 Improper Initialization
824 Access of Uninitialized Pointer
763 Release of Invalid Pointer or Reference

476 NULL Pointer Dereference
"""

groups["value_propagation_errors"] = """
704 Incorrect Type Conversion or Cast
682 Incorrect Calculation
369 Divide By Zero
190 Integer Overflow or Wraparound
191 Integer Underflow (Wrap or Wraparound)
674 Uncontrolled Recursion
835 Loop with Unreachable Exit Condition ('Infinite Loop')
617 Reachable Assertion
252 Unchecked Return Value
172 Encoding Error
"""

# 436 Interpretation Conflict
# 362 Concurrent Execution using Shared Resource with Improper Synchronization ('Race Condition')

# 755 Improper Handling of Exceptional Conditions
# 754 Improper Check for Unusual or Exceptional Conditions


# 834 Excessive Iteration

groups["buffer_overflow"] = """
129 Improper Validation of Array Index
119 Improper Restriction of Operations within the Bounds of a Memory Buffer
787 Out-of-bounds Write
125 Out-of-bounds Read
120 Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
"""

# NOTE: some settings
include_extra = True
use_metagroups = False

extras = {
    "privilege_escalation_authorization": """
254 CWE CATEGORY: 7PK - Security Features
255 CWE CATEGORY: Credentials Management Errors
264 CWE CATEGORY: Permissions, Privileges, and Access Controls
310 CWE CATEGORY: Cryptographic Issues
320 CWE CATEGORY: Key Management Errors
""",
    "resource_allocation_free": """
399 CWE CATEGORY: Resource Management Errors
769 DEPRECATED: Uncontrolled File Descriptor Consumption
""",
    "value_propagation_errors": """
19 CWE CATEGORY: Data Processing Errors
189 CWE CATEGORY: Numeric Errors
""",
# 388 CWE CATEGORY: 7PK - Errors
# 361 CWE CATEGORY: 7PK - Time and State
}
if include_extra:
    for groupname, extratext in extras.items():
        groups[groupname] += "\n" + extratext

metagroups = {
    "General general_programming_errors": ["general_programming_errors", "resource_allocation_free"],
    "General security": ["input_validation", "security"],
}
if use_metagroups:
    for metagroup_name, subgroups in metagroups.items():
        groups[metagroup_name] = "\n".join([groups[s] for s in subgroups])
        for s in subgroups:
            del groups[s]

import collections

for groupname, group in groups.items():
    group = [l.split(" ", maxsplit=1) for l in group.splitlines() if l]
    ids, descs = zip(*group)
    ids = list(map(int, ids))
    groups[groupname] = (ids, descs)
    # print(groupname, "\n".join(str(i) for i in group), sep="\n")

all_grouped_cwes = set()
groupnames = list(sorted(groups.keys()))
for groupname1_idx in range(len(groupnames)):
    groupname1 = groupnames[groupname1_idx]
    group1 = groups[groupname1]

    duplicates = [item for item, count in collections.Counter(group1[0]).items() if count > 1]
    if len(duplicates) > 0:
        print("duplicate:", groupname1, duplicates)

    count = sum(vc[f"CWE-{i}"] for i in group1[0])
    print(groupname1, count)

    all_grouped_cwes.update([f"CWE-{i}" for i in group1[0]])

    for groupname2_idx in range(groupname1_idx, len(groupnames)):
        groupname2 = groupnames[groupname2_idx]
        group2 = groups[groupname2]
        if groupname1 == groupname2 or groupname1 in metagroups or groupname2 in metagroups:
            continue
        intersect = set(group1[0]).intersection(set(group2[0]))
        if len(intersect) > 0:
            print(groupname1, "<->", groupname2, intersect)

all_cwes = set(source_df["CWE ID"].unique().tolist())
# print("not grouped:", *all_cwes.difference(all_grouped_cwes), sep="\n")
print("not grouped:")
for i in sorted(all_cwes.difference(all_grouped_cwes), key=lambda s: str(s)):
    if pd.isna(i):
        print(i, int(np.sum(source_df["CWE ID"].isna())))
    else:
        print(i, vc[i])
#%%
datas = []
for groupname, group in groups.items():
    ids, descs = group
    ids = list(map(int, ids))
    for i, d in zip(ids, descs):
        datas.append({"group": groupname, "id": f"CWE-{i}", "description": d})
import pandas as pd
df = pd.DataFrame(data=datas)
df = df.sort_values(["group", "id"])
df.to_clipboard()
df

#%%
import tqdm
for groupname, (cwe_nums, cwe_descriptions) in tqdm.tqdm(sorted(list(groups.items()), key=lambda p: p[0])):
    cwe_ids = set(cwe_nums)
    cwe_df = source_df[source_df["CWE ID"].apply(lambda s: int(s.split("-")[1]) if not pd.isna(s) else s).isin(cwe_ids)]

    def split(df):
        rs = np.random.RandomState(seed=0)
        ten_percent = len(df)//10
        test_num = ten_percent
        val_num = ten_percent
        split = pd.Series(range(len(df)), index=rs.permutation(df.index)).apply(lambda i: "test" if i < test_num else ("valid" if i < test_num + val_num else "train"))
        return split
    cwe_df = cwe_df.assign(split=split(cwe_df))
    cwe_df.sort_values("example_index").to_csv(f"data/subsets/bug_type/bugtype_{groupname}.csv")

#%%
import pandas as pd
import glob
sets = []
sets_cwe = []
for fname in sorted(glob.glob("data/subsets/bug_type/bugtype_*.csv")):
    bt_df = pd.read_csv(fname, index_col=0)
    # print(bt_df.value_counts("split", normalize=True))
    print("file:", fname)
    print("label distribution:")
    print(bt_df.value_counts("target", normalize=True))
    print("unique projects:", bt_df["project"].nunique())
    print("examples:", len(bt_df))
    sets.append(set(bt_df["example_index"]))
    sets_cwe.append(set(bt_df["CWE ID"].unique()))
print(len(sets), "sets", len(sets_cwe), "CWE sets")
for i in range(len(sets)):
    for j in range(i, len(sets)):
        if i != j:
            assert len(sets[i].intersection(sets[j])) == 0
for i in range(len(sets_cwe)):
    for j in range(i, len(sets_cwe)):
        if i != j:
            assert len(sets_cwe[i].intersection(sets_cwe[j])) == 0

# #%%
# for w, attr in G.nodes(data=True):
#     descendants = nx.algorithms.descendants(G, w)
#     descendant_ids = ["CWE-" + str(n) for n in descendants]
#     dag_ids = ["CWE-" + str(w)] + descendant_ids
#     dag_ids = [i for i in dag_ids if i in vc.index]
#     count = int(vc.loc[dag_ids].sum())
#     desc = attr["desc"]
#     attr["label"] = f"CWE-{w} ({count}): {desc}"
# print(G)
# in_ds = set([int(s.split("-")[1]) for s in all_df["CWE ID"].drop_duplicates().dropna().tolist()])
# import itertools
# in_ds_parents = set(itertools.chain(*(nx.ancestors(G, n) for n in in_ds if n in G)))
# G.remove_nodes_from(set(G.nodes).difference(in_ds.union(in_ds_parents)))
# print(G)
# from networkx.drawing.nx_agraph import to_agraph

# # for i, c in enumerate(nx.strongly_connected_components(G)):
# #     S = G.subgraph(c)
# #     A = to_agraph(S)
# #     print(A)
# #     A.layout('dot')
# #     A.draw(f"graphslice_{i}.png")

# A = to_agraph(G)
# print(A)
# A.layout('dot')
# A.draw("graph.png")
# # nx.draw(G, with_labels=True)

# #%%
# print(G)
# roots = [n for n in G.nodes if len(list(G.predecessors(n))) == 0]
# print(len(roots))

# datas = []
# for i, r in enumerate(roots):
#     descendants = nx.algorithms.descendants(G, r)
#     descendant_ids = ["CWE-" + str(n) for n in descendants]
#     dag_ids = ["CWE-" + str(r)] + descendant_ids
#     count = vc.loc[[i for i in dag_ids if i in vc.index]].sum()
#     S = nx.induced_subgraph(G, [r] + list(descendants))
#     # print(S)
#     A = to_agraph(S)
#     # print(A)
#     A.layout('dot')
#     A.draw(f"graphslice_{i}.png")
#     datas.append({"root": r, "root_label": G.nodes[r]["label"], "num_examples": int(count)})
# result_df = pd.DataFrame(data=datas).sort_values("num_examples", ascending=False).reset_index(drop=True)
# result_df.to_clipboard()
# result_df

# %%





#%%
import glob
for f in glob.glob("data/subsets/bug_type/bugtype_*.csv"):
    print(f)
    df = pd.read_csv(f, index_col=0)
    # print(df)
    print(len(df))

#%%
groups = {}
groups["security"] = """
693 Protection Mechanism Failure
327 Use of a Broken or Risky Cryptographic Algorithm
330 Use of Insufficiently Random Values
331 Insufficient Entropy
311 Missing Encryption of Sensitive Data
346 Origin Validation Error
347 Improper Verification of Cryptographic Signature
358 Improperly Implemented Security Check for Standard

352 Cross-Site Request Forgery (CSRF)
918 Server-Side Request Forgery (SSRF)

284 Improper Access Control
290 Authentication Bypass by Spoofing
295 Improper Certificate Validation
522 Insufficiently Protected Credentials
269 Improper Privilege Management
281 Improper Preservation of Permissions
732 Incorrect Permission Assignment for Critical Resource
285 Improper Authorization
862 Missing Authorization
287 Improper Authentication
209 Generation of Error Message Containing Sensitive Information

1021 Improper Restriction of Rendered UI Layers or Frames
532 Insertion of Sensitive Information into Log File
668 Exposure of Resource to Wrong Sphere
200 Exposure of Sensitive Information to an Unauthorized Actor
"""

# ingoing information flow/taint
groups["input_validation"] = """
354 Improper Validation of Integrity Check Value

134 Use of Externally-Controlled Format String
20 Improper Input Validation
426 Untrusted Search Path
59 Improper Link Resolution Before File Access ('Link Following')
706 Use of Incorrectly-Resolved Name or Reference
601 URL Redirection to Untrusted Site ('Open Redirect')
345 Insufficient Verification of Data Authenticity
494 Download of Code Without Integrity Check
502 Deserialization of Untrusted Data

22 Improper Limitation of a Pathname to a Restricted Directory ('Path Traversal')
74 Improper Neutralization of Special Elements in Output Used by a Downstream Component ('Injection')
77 Improper Neutralization of Special Elements used in a Command ('Command Injection')
78 Improper Neutralization of Special Elements used in an OS Command ('OS Command Injection')
79 Improper Neutralization of Input During Web Page Generation ('Cross-site Scripting')
89 Improper Neutralization of Special Elements used in an SQL Command ('SQL Injection')
90 Improper Neutralization of Special Elements used in an LDAP Query ('LDAP Injection')
93 Improper Neutralization of CRLF Sequences ('CRLF Injection')
94 Improper Control of Generation of Code ('Code Injection')
611 Improper Restriction of XML External Entity Reference
"""

groups["resource_allocation_free"] = """
664 Improper Control of a Resource Through its Lifetime

415 Double Free
416 Use After Free
770 Allocation of Resources Without Limits or Throttling
772 Missing Release of Resource after Effective Lifetime
909 Missing Initialization of Resource
400 Uncontrolled Resource Consumption
404 Improper Resource Shutdown or Release
665 Improper Initialization
824 Access of Uninitialized Pointer
763 Release of Invalid Pointer or Reference
"""

groups["general_programming_errors"] = """
704 Incorrect Type Conversion or Cast
362 Concurrent Execution using Shared Resource with Improper Synchronization ('Race Condition')
682 Incorrect Calculation
369 Divide By Zero
190 Integer Overflow or Wraparound
191 Integer Underflow (Wrap or Wraparound)
172 Encoding Error
754 Improper Check for Unusual or Exceptional Conditions
476 NULL Pointer Dereference
252 Unchecked Return Value
617 Reachable Assertion
674 Uncontrolled Recursion
755 Improper Handling of Exceptional Conditions
834 Excessive Iteration
835 Loop with Unreachable Exit Condition ('Infinite Loop')
436 Interpretation Conflict
"""

groups["BOF"] = """
129 Improper Validation of Array Index
119 Improper Restriction of Operations within the Bounds of a Memory Buffer
787 Out-of-bounds Write
125 Out-of-bounds Read
120 Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
"""

datas = []
for groupname, group in groups.items():
    group = [l.split(" ", maxsplit=1) for l in group.splitlines() if l]
    ids, descs = zip(*group)
    ids = list(map(int, ids))
    for i, d in zip(ids, descs):
        datas.append({"group": groupname, "id": f"CWE-{i}", "description": d})
import pandas as pd
df = pd.DataFrame(data=datas)
df
