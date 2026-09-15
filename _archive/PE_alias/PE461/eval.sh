#!/bin/bash
cd "$(dirname "$0")"
mkdir -p ../data
for f in ../data/*.in; do
    base=$(basename "$f" .in)
    ../std < "$f" > "../data/$base.out"
done
