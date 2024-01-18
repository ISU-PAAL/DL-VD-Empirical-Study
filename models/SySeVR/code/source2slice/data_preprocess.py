## coding:utf-8

import pickle
import os

slice_path = '<ANONYMOUS>/<ANONYMOUS>/sysevr/data/NVD/slice_files/'
label_path = '<ANONYMOUS>/<ANONYMOUS>/sysevr/data/NVD/slice_labels/'
folder_path = '<ANONYMOUS>/<ANONYMOUS>/sysevr/data/NVD/labeled_slices/'
for filename in os.listdir(slice_path):
    if filename.endswith('.txt') is False:
        continue
    print(filename)
    filepath = os.path.join(slice_path,filename)
    f = open(filepath,'r')
    slicelists = f.read().split('------------------------------')
    f.close()
    labelpath = os.path.join(label_path,filename[:-4]+'.pkl')
    f = open(labelpath,'rb')
    labellists = pickle.load(f)
    f.close()
	
    if slicelists[0] == '':
        del slicelists[0]
    if slicelists[-1] == '' or slicelists[-1] == '\n' or slicelists[-1] == '\r\n':
        del slicelists[-1]

    print(len(labellists))

    file_path = os.path.join(folder_path,filename)
    f = open(file_path,'a+')
    for slicelist in slicelists:
        sentences = slicelist.split('\n')
        if sentences[0] == '\r' or sentences[0] == '':
            del sentences[0]
        if sentences == []:
            continue
        if sentences[-1] == '':
            del sentences[-1]
        if sentences[-1] == '\r':
            del sentences[-1]
        key = int(sentences[0].split()[0]) - 1
        label = labellists[key]
        for sentence in sentences:
            f.write(str(sentence)+'\n')
        f.write(str(label)+'\n')
        f.write('------------------------------'+'\n')
    f.close()
print('\success!')
        
            
    
    
