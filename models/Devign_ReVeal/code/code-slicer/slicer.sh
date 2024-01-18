if [[ $# -eq 3 ]]; then
    inpdir=$1;
    filename=$2;
    outdir=$3;
    rm -rf parsed tmp
    mkdir -p 'tmp'
    cp $inpdir'/'$filename 'tmp/'$filename
    ./joern/joern-parse tmp/
    cp -r parsed/* $outdir
else
  echo 'Wrong Argument!.'
  echo 'slicer.sh <Directory of the C File> <Name of the C File> <Line For Slice> <Output Directory> <DataFlowOnly(Optional, used if mentioned)>'
fi

# TS_SOCKET=/tmp/socket.devign tsp -L parse while read f; do bash slicer.sh ../data/MSR/raw_code $f ../data/MSR/parsed; done < <(ls ../data/MSR/raw_code)
