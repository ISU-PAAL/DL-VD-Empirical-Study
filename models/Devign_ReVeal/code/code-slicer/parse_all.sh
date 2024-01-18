dir=$1

(\
    while read f
    do
        bash slicer.sh $dir/raw_code $f $dir/parsed
    done < <(ls $dir/raw_code)\
) | tqdm >> /dev/null
