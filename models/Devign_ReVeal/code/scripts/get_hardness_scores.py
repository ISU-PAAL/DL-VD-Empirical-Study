import glob
import os
import sys
import re

dir = sys.argv[1]

files = glob.glob(os.path.join(dir, "hardset_*.log"))
print(files)
for f in files:
    if "normalized" not in f:
        continue
    difficulty_name = []
    difficulty = []
    score = []
    length = []
    for line in open(f).readlines():
        m = re.search(r"difficulty: difficulty/(\w+)", line)
        if m:
            difficulty_name.append(m.group(1))
            difficulty_name.append(m.group(1))
            difficulty_name.append(m.group(1))
        m = re.search(r"(\w+) score: ([0-9.]+) len: ([0-9.]+)", line)
        if m:
            difficulty.append(m.group(1))
            score.append(float(m.group(2)))
            length.append(int(m.group(3)))
    # print(f, difficulty_name, difficulty, score, length)
    assert len(difficulty_name) == len(difficulty)
    assert len(difficulty) == len(score)
    assert len(score) == len(length)
    m = re.search(r".*/hardset_(GNN-ReGVD|devign|devign_msr|codebert|vulberta)_(train|valid|test)_(normalized_easiness|easiness)(_testafter)?\.log", f)
    assert m is not None, f
    for n, d, s, l in zip(difficulty_name, difficulty, score, length):
        print(*m.groups(), n, d, s, l, sep=",")
