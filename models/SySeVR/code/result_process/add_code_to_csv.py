## -*- coding: utf-8 -*-

import os
import pandas as pd



base_path = '<ANONYMOUS>/<ANONYMOUS>/sysevr/data/result/result4324/'


df = pd.read_csv(os.path.join(base_path, "seed_result.csv"))
print(df['code_path'][10077])

def read_file(path):
    try:
        f = open(path, 'r', encoding='unicode_escape')
        result = f.read()
        f.close()
    except Exception as e:
        print(str(e), path)
    return result


df['code'] = df['code_path'].apply(read_file)
del df['code_path']

df.to_csv(os.path.join(base_path, "seed_result_with_code.csv"))


