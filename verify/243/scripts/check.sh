#!/bin/bash
cd "$(dirname "$0")/.."
i=1
while true; do
    echo "Test $i"
    ./gen small > input.txt
    ./std < input.txt > std.txt
    ./brute < input.txt > brute.txt
    if diff std.txt brute.txt > /dev/null; then echo "AC"; else echo "WA"; break; fi
    i=$((i+1))
done
