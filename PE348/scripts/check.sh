#!/bin/bash
cd "$(dirname "$0")/.."
echo "PE348 check: std vs brute (same algorithm)"
./std < data/01.in > std.txt
./brute < data/01.in > brute.txt
if diff std.txt brute.txt > /dev/null; then
    echo "AC - std and brute match on sample"
else
    echo "WA - mismatch"
    echo "Std:"; cat std.txt
    echo "Brute:"; cat brute.txt
fi
