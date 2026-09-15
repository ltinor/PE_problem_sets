#!/bin/bash
BASE="/Users/yini/Desktop/test/cpp/ProjectEuler"

check_pe() {
    local num=$1
    local input=$2
    local SRC="$BASE/PE${num}/code/std.cpp"
    local BIN="$BASE/PE${num}/code/std"
    
    if [ ! -f "$SRC" ]; then
        echo "PE${num}: MISSING"
        return
    fi
    
    g++ -std=c++17 -O3 -o "$BIN" "$SRC" 2>&1
    if [ $? -ne 0 ]; then
        echo "PE${num}: COMPILE FAIL"
        return
    fi
    
    echo "PE${num}: $input -> $(echo "$input" | "$BIN" 2>&1 | head -1 | cut -c1-60)"
}

check_pe 461 "PE"
check_pe 471 "100000000000"
check_pe 472 "1000000000000"
check_pe 473 "10000000000"
check_pe 474 "1000000 65432"
check_pe 475 "600"
check_pe 476 "1803"
check_pe 477 "100000000"
check_pe 478 "10000000"
check_pe 479 "1000000"
