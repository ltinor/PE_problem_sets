#!/bin/bash

cd "$(dirname "$0")/.."

for infile in data/*.in; do
    outfile="${infile%.in}.out"
    ./std < "$infile" > "$outfile"
    echo "Generated $outfile"
done
