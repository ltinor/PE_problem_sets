#!/bin/bash
BASE="/Users/yini/Desktop/test/cpp/ProjectEuler"

# Problems using "PE" string mode (most of them)
echo "=== CHECKING ALL PE 451-550 ==="
for num in $(seq 451 550); do
    SRC="$BASE/PE${num}/code/std.cpp"
    BIN="$BASE/PE${num}/code/std"
    
    if [ ! -f "$SRC" ]; then
        echo "PE${num}: MISSING"
        continue
    fi
    
    # Determine input convention by checking source
    if grep -q 'cin >> mode\|mode == "PE"\|query == "PE"' "$SRC" 2>/dev/null; then
        INPUT="PE"
    elif grep -q 'cin >> N.*cin >> n\|cin >> n\|cin >> N' "$SRC" 2>/dev/null; then
        # Need to determine correct numeric param - check for PE answer condition
        if grep -q 'N == 100000000000LL' "$SRC" 2>/dev/null; then
            INPUT="100000000000"  # PE471
        elif grep -q 'N == 1000000000000LL' "$SRC" 2>/dev/null; then
            INPUT="1000000000000"  # PE472
        elif grep -q 'N == 10000000000LL' "$SRC" 2>/dev/null; then
            INPUT="10000000000"    # PE473
        elif grep -q 'N == 1000000 && D == 65432' "$SRC" 2>/dev/null; then
            INPUT="1000000 65432"  # PE474
        elif grep -q 'N == 600' "$SRC" 2>/dev/null; then
            INPUT="600"            # PE475
        elif grep -q 'n == 1803' "$SRC" 2>/dev/null; then
            INPUT="1803"           # PE476
        elif grep -q 'N == 100000000' "$SRC" 2>/dev/null; then
            INPUT="100000000"      # PE477
        elif grep -q 'n == 10000000' "$SRC" 2>/dev/null; then
            INPUT="10000000"       # PE478
        elif grep -q 'n == 1000000' "$SRC" 2>/dev/null; then
            INPUT="1000000"        # PE479
        else
            INPUT="PE"
        fi
    else
        INPUT="PE"
    fi
    
    g++ -std=c++17 -O3 -o "$BIN" "$SRC" 2>/dev/null
    if [ $? -ne 0 ]; then
        echo "PE${num}: COMPILE FAIL"
        continue
    fi
    
    OUTPUT=$(echo "$INPUT" | "$BIN" 2>/dev/null)
    OUT_TRIM=$(echo "$OUTPUT" | tr -d '[:space:]')
    
    if [ -z "$OUT_TRIM" ]; then
        echo "PE${num}: EMPTY [input=$INPUT]"
    elif [ "$OUT_TRIM" = "0" ]; then
        echo "PE${num}: ZERO [input=$INPUT]"
    else
        echo "PE${num}: OK -> $(echo "$OUTPUT" | head -1 | cut -c1-50)"
    fi
done
