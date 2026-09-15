#!/bin/bash

cd "$(dirname "$0")/.."

i=1
while true
do
    echo "Test $i"

    ./std < /dev/null > std.txt
    ./brute < /dev/null > brute.txt

    if diff std.txt brute.txt > /dev/null
    then
        echo "AC"
    else
        echo "WA on test $i"

        echo "Std:"
        cat std.txt

        echo "Brute:"
        cat brute.txt

        break
    fi

    i=$((i+1))
done
