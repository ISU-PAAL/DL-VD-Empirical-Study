


def change_first_line(path, destination):
    print(path)
    f = open(path, 'r')
    slicelists = f.read().split('------------------------------')[:-1]
    f.close()
    
    labels = []
    if slicelists[0] == '':
        del slicelists[0]
    if slicelists[-1] == '' or slicelists[-1] == '\n' or slicelists[-1] == '\r\n':
        del slicelists[-1]
    
    f = open(destination, 'a')
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
            
        head_ = sentences[0]
        rest_ = sentences[1:]

        heads = head_.split(" ")
        cng = heads[-2]
        if cng[0] == '[':
            heads[-2] = cng[2:-1] 
        f.write(" ".join(heads) + "\n")
        for sentence in rest_:
            f.write(sentence + "\n")
        f.write('------------------------------' + '\n')     
    f.close()


    # return labels

base_dir = "<ANONYMOUS>/<ANONYMOUS>/sysevr/data/SARD/"
change_first_line(base_dir + "slice_files_1/" + "arraysuse_slices.txt", base_dir + "slice_files/" + "arraysuse_slices.txt")