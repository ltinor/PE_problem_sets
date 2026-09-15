#!/bin/bash

# 进入 Makefile 所在目录（与 check.sh 保持一致）
cd "$(dirname "$0")/.."

DATA_DIR="data"

if [ ! -d "$DATA_DIR" ]; then
    echo "Data directory $DATA_DIR does not exist!"
    exit 1
fi

for infile in "$DATA_DIR"/*.in; do
    outfile="${infile%.in}.out"
    ./std < "$infile" > "$outfile"
    echo "Generated $outfile from $infile"
done
