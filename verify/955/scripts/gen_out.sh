#!/bin/bash

# 从 Makefile 根目录调用：生成 data/*.out（用 std 对 data/*.in 求答案）
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
