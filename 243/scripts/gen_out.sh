#!/bin/bash
DATA_DIR="../data"
if [ ! -d "$DATA_DIR" ]; then exit 1; fi
for infile in "$DATA_DIR"/*.in; do
    outfile="${infile%.in}.out"
    .././std < "$infile" > "$outfile"
    echo "Generated $outfile"
done
