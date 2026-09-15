#!/bin/bash
cd "$(dirname "$0")/.."
i=1
while true; do
    echo "Test $i"
    ./gen small > input.txt
    ./std < input.txt > std.txt
    ./brute < input.txt > brute.txt
    # Use awk for approximate comparison (tolerance 0.05)
    std_val=$(cat std.txt)
    brute_val=$(cat brute.txt)
    diff=$(echo "$std_val - $brute_val" | bc -l | sed 's/^-//')
    if (( $(echo "$diff < 0.05" | bc -l) )); then
        echo "AC (diff=$diff)"
    else
        echo "WA on test $i"
        echo "Input:"; cat input.txt
        echo "Std: $std_val"
        echo "Brute: $brute_val"
        break
    fi
    i=$((i+1))
done
