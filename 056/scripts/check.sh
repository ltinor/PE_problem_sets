#!/bin/bash

cd "$(dirname "$0")/.."  

for i in $(seq 1 10)
do
    echo "Test $i"

    ./gen small > input.txt
    ./std < input.txt > std.txt
    ./brute < input.txt > brute.txt

    if diff std.txt brute.txt > /dev/null
    then
        echo "AC"
    else
        echo "WA on test $i"

        echo "Input:"
        cat input.txt

        echo "Std:"
        cat std.txt

        echo "Brute:"
        cat brute.txt

        exit 1
    fi
done

echo "All 10 tests PASSED"
