#!/bin/bash
# Floating-point aware check for PE 235

cd "$(dirname "$0")/.."  

i=1
while true
do
    echo "Test $i"

    ./gen small > input.txt
    ./std < input.txt > std.txt
    ./brute < input.txt > brute.txt

    # Floating-point comparison with tolerance
    std_val=$(cat std.txt)
    brute_val=$(cat brute.txt)

    python3 -c "
s = float('$std_val')
b = float('$brute_val')
if abs(s - b) < 1e-8:
    exit(0)
else:
    exit(1)
"

    if [ $? -eq 0 ]; then
        echo "AC"
    else
        echo "WA on test $i"
        echo "Input:"
        cat input.txt
        echo "Std:"
        cat std.txt
        echo "Brute:"
        cat brute.txt
        break
    fi

    i=$((i+1))
done
