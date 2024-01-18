## coding: utf-8
import os
import pickle

# path = "<ANONYMOUS>/<ANONYMOUS>/sysevr/data/SARD/delete_list/"


# for file in os.listdir(path):
#     if "api" not in file:
#         continue
#     f = open(os.path.join(path, file), "rb")
#     data = pickle.load(f)
#     f.close()
#     print(file, " ", len(data), data)
#     break

path = "<ANONYMOUS>/<ANONYMOUS>/sysevr/data/SARD/corpus/"
total = 0
array = 0
integer = 0
pointer = 0
api = 0
for folder in os.listdir(path):
    for file in os.listdir(os.path.join(path, folder)):
        f = open(os.path.join(path, folder, file), 'rb')
        # print(os.path.join(path, folder, file), file in  os.listdir(os.path.join(path, folder)))
        data = pickle.load(f)
        f.close()
        total +=  len(data[1])
        # print(data[1])
        if "array" in file:
            array += len(data[1])
        elif "integer" in file:
            integer += len(data[1])
        elif "pointer" in file:
            pointer += len(data[1])
        else:
            api += len(data[1])


print("Total", total, " Array ", array, " Integer ", integer, " Pointer ", pointer, " Api ", api)


path = "<ANONYMOUS>/<ANONYMOUS>/sysevr/data/SARD/vector/"
total = 0
array = 0
integer = 0
pointer = 0
api = 0
for folder in os.listdir(path):
    for file in os.listdir(os.path.join(path, folder)):
        f = open(os.path.join(path, folder, file), 'rb')
        # print(os.path.join(path, folder, file), file in  os.listdir(os.path.join(path, folder)))
        data = pickle.load(f)
        f.close()
        total +=  len(data[1])
        # print(data[1])
        if "array" in file:
            array += len(data[1])
        elif "integer" in file:
            integer += len(data[1])
        elif "pointer" in file:
            pointer += len(data[1])
        else:
            api += len(data[1])


print("Total", total, " Array ", array, " Integer ", integer, " Pointer ", pointer, " Api ", api)


