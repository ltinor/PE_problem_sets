#!/bin/bash

cd "$(dirname "$0")/.."

i=1
while true
do
    echo "Test $i"

    ./gen > input.txt
    ./std < input.txt > std.txt

    if ./spj input.txt std.txt > /dev/null
    then
        echo "AC"
    else
        echo "WA on test $i"
        echo "Input:"
        cat input.txt
        echo "Std output:"
        cat std.txt
        break
    fi

    i=$((i+1))
done