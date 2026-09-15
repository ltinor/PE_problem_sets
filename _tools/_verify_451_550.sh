#!/bin/bash
BASE="/Users/yini/Desktop/test/cpp/ProjectEuler"
LOG="$BASE/_verify_451_550.log"
> "$LOG"

echo "=== PE 451-550 VERIFICATION ===" | tee -a "$LOG"
echo "Started: $(date)" | tee -a "$LOG"

TOTAL=0; PASS=0; FAIL=0; MISSING=0; COMPILE_FAIL=0

for num in $(seq 451 550); do
    SRC="$BASE/PE${num}/code/std.cpp"
    BIN="$BASE/PE${num}/code/std"
    
    if [ ! -f "$SRC" ]; then
        echo "PE${num}: MISSING (no std.cpp)" | tee -a "$LOG"
        MISSING=$((MISSING + 1))
        TOTAL=$((TOTAL + 1))
        continue
    fi
    
    TOTAL=$((TOTAL + 1))
    
    # Compile
    COMPILE_OUT=$(g++ -std=c++17 -O3 -o "$BIN" "$SRC" 2>&1)
    if [ $? -ne 0 ]; then
        echo "PE${num}: COMPILE FAIL" | tee -a "$LOG"
        echo "  $COMPILE_OUT" | tee -a "$LOG"
        COMPILE_FAIL=$((COMPILE_FAIL + 1))
        FAIL=$((FAIL + 1))
        continue
    fi
    
    # Run
    OUTPUT=$(echo "PE" | "$BIN" 2>&1)
    RC=$?
    OUT_TRIM=$(echo "$OUTPUT" | tr -d '[:space:]')
    
    if [ $RC -ne 0 ]; then
        echo "PE${num}: RUNTIME ERROR (exit $RC)" | tee -a "$LOG"
        FAIL=$((FAIL + 1))
    elif [ -z "$OUT_TRIM" ]; then
        echo "PE${num}: EMPTY OUTPUT" | tee -a "$LOG"
        FAIL=$((FAIL + 1))
    elif [ "$OUT_TRIM" = "0" ]; then
        echo "PE${num}: ZERO OUTPUT (suspicious)" | tee -a "$LOG"
        FAIL=$((FAIL + 1))
    else
        SHORT=$(echo "$OUTPUT" | head -1 | cut -c1-60)
        echo "PE${num}: OK -> $SHORT" | tee -a "$LOG"
        PASS=$((PASS + 1))
    fi
done

echo "" | tee -a "$LOG"
echo "=== RESULTS ===" | tee -a "$LOG"
echo "Total: $TOTAL | Pass: $PASS | Fail: $FAIL | Missing: $MISSING | CompileFail: $COMPILE_FAIL" | tee -a "$LOG"
echo "Finished: $(date)" | tee -a "$LOG"
