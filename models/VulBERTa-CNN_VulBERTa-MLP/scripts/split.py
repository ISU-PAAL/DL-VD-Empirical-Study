import jsonlines
import os
import tqdm
import sys

if sys.argv[1] == "devign":
    data_source = "data/finetune/devign/Devign.jsonlines"
    trainfname = "data/finetune/devign/train.txt"
    validfname = "data/finetune/devign/valid.txt"
    testfname = "data/finetune/devign/test.txt"
if sys.argv[1] == "msr":
    data_source = "data/finetune/msr/MSR_data_cleaned.jsonlines"
    trainfname = "data/finetune/msr/train.txt"
    validfname = "data/finetune/msr/valid.txt"
    testfname = "data/finetune/msr/test.txt"

with jsonlines.open(data_source) as dataf, open(testfname) as testf, open(trainfname) as trainf, open(validfname) as validf:
    print(os.path.join(os.path.dirname(testfname), "test~.jsonlines"))
    print(os.path.join(os.path.dirname(trainfname), "train.jsonlines"))
    print(os.path.join(os.path.dirname(validfname), "valid.jsonlines"))
    with jsonlines.open(os.path.join(os.path.dirname(testfname), "test.jsonlines"), "w") as testof, jsonlines.open(os.path.join(os.path.dirname(trainfname), "train.jsonlines"), "w") as trainof, jsonlines.open(os.path.join(os.path.dirname(validfname), "valid.jsonlines"), "w") as validof:
        train = set([int(l) for l in trainf.readlines()])
        valid = set([int(l) for l in validf.readlines()])
        test = set([int(l) for l in testf.readlines()])
        for i, row in tqdm.tqdm(enumerate(dataf)):
            if "func_before" in row:
                row["func"] = row["func_before"]
            if "vul" in row:
                row["target"] = row["vul"]
            for k in list(row.keys()):
                if k not in ("func", "target"):
                    del row[k]
            row["example_index"] = i
            if i in train:
                trainof.write(row)
            elif i in valid:
                validof.write(row)
            elif i in test:
                testof.write(row)
