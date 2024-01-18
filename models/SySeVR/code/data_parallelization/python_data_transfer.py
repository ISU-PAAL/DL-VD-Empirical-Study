import os
import shutil

src_folder = '<ANONYMOUS>/<ANONYMOUS>/sysevr/data/SARD/000'
destination = '<ANONYMOUS>/<ANONYMOUS>/sysevr/data/SARD/'

lower = 000
upper = 100

def mkdirs(current_path, dir_list):
    next_path = current_path[:]
    for folder in dir_list:
        next_path = os.path.join(next_path, folder)
        if not os.path.exists(next_path):
            os.mkdir(next_path)

def recursion(current_path):
    if os.path.isfile(current_path):
        folders = current_path.split("/")
        num = folders[-2]

        if num == '000':
            next_dir = "SARD000"
        else:
            next_dir = "SARD" + num[0]
        next_path = destination[:] + next_dir
        if not os.path.exists(next_path):
            os.mkdir(next_path)
        
        index = folders.index('000')
        dir_list = folders[index: -1]
        for folder in dir_list:
            next_path = os.path.join(next_path, folder)
            if not os.path.exists(next_path):
                os.mkdir(next_path)
        folders = folders[:8] + [next_dir] + folders[8:]
        # folders[8] += num[0]
        print(current_path)
        des_path = '/'.join(folders)
        print(des_path)
        shutil.copyfile(current_path, des_path)
        return
    

    for f in os.listdir(current_path):
        if f == '.DS_Store':
            continue
        recursion(os.path.join(current_path, f))


recursion(src_folder)

