#!/bin/bash

# 进入 Makefile 所在目录
cd "$(dirname "$0")/.."   # 进入根目录

i=1
while true
do
    echo "Test $i"

    ./gen 100 > input.txt
    ./std < input.txt > std.txt
    ./brute < input.txt > brute.txt

    # 浮点答案：绝对误差 < 1e-3 判 AC
    python3 -c "
import sys
s = float(open('std.txt').read().strip())
b = float(open('brute.txt').read().strip())
sys.exit(0 if abs(s - b) < 1e-3 else 1)
"
    if [ $? -eq 0 ]
    then
        echo "AC (std=$(cat std.txt), brute=$(cat brute.txt))"
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
