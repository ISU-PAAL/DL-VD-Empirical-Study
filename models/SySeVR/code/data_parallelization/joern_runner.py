import os
import subprocess

dataset = "NVD"

if dataset == "SARD":

    base_path = "<ANONYMOUS>/<ANONYMOUS>/sysevr/data/SARD"

    for folder   in  os.listdir(base_path):
        if folder == '000':
            continue
        if os.path.isfile(os.path.join(base_path, folder)):
            continue
        next_path = os.path.join(base_path, folder)
        os.chdir(next_path)
        subprocess.call(["java", "-jar", "<ANONYMOUS>/<ANONYMOUS>/joern-0.3.1/bin/joern.jar", "000"])

    print "Success"

else:
    base_path = "<ANONYMOUS>/<ANONYMOUS>/sysevr/data/NVD"
    os.chdir(base_path)
    subprocess.call(["java", "-jar", "<ANONYMOUS>/<ANONYMOUS>/joern-0.3.1/bin/joern.jar", "NVD_data"])
    print "Success"
