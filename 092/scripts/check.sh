#!/bin/bash

cd "$(dirname "$0")/.."

i=1
while true
do
    echo "Test $i"

    ./gen > input.txt
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

        break
    fi

    i=$((i+1))
done
