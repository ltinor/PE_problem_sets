#!/bin/bash
DATA_DIR="../data"
[ ! -d "$DATA_DIR" ] && echo "Data directory missing!" && exit 1
for infile in "$DATA_DIR"/*.in; do
    outfile="${infile%.in}.out"
    .././std < "$infile" > "$outfile"
    echo "Generated $outfile"
done
