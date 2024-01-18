import os
import pickle


base_dir = "<ANONYMOUS>/<ANONYMOUS>/sysevr/data/SARD/"


def load_pkl(path):
    fin = open(path, 'rb')
    dict_ = pickle.load(fin)
    fin.close()
    return dict_


def merge_dicts(dict_list):
    _dict = None
    for ele in dict_list:
        if _dict is None:
            _dict = ele
        else:
            _dict.update(ele)
    return _dict



array = []
integer = []
point = []
sensifunc = []
for folder in sorted(os.listdir(base_dir)):
    if "SARD" not in folder:
        continue
    print(folder)
    next_path = os.path.join(base_dir, folder)

    array.append(load_pkl(os.path.join(next_path, "arrayuse_slice_points.pkl")))
    integer.append(load_pkl(os.path.join(next_path, "integeroverflow_slice_points_new.pkl")))
    point.append(load_pkl(os.path.join(next_path, "pointuse_slice_points.pkl")))
    sensifunc.append(load_pkl(os.path.join(next_path, "sensifunc_slice_points.pkl")))


# print(type(sensifunc[0]))

_dict = merge_dicts(sensifunc)
f = open("./syvcs/sensifunc_slice_points.pkl", 'wb')
pickle.dump(_dict, f, True)
f.close()
# print _dict

_dict = merge_dicts(point)
f = open("./syvcs/pointuse_slice_points.pkl", 'wb')
pickle.dump(_dict, f, True)
f.close()
# print _dict 

_dict = merge_dicts(array)
f = open("./syvcs/arrayuse_slice_points.pkl", 'wb')
pickle.dump(_dict, f, True)
f.close()
# print _dict

_dict = merge_dicts(integer)
f = open("./syvcs/integeroverflow_slice_points_new.pkl", 'wb')
pickle.dump(_dict, f, True)
f.close()



