#!/bin/bash
# Verify PE 551-650: compile → echo "PE参数" | ./std → check output
WORKDIR="/Users/yini/Desktop/test/cpp/ProjectEuler"
cd "$WORKDIR"

echo "=== PE 551-650 Verification ==="
echo "Started at $(date)"
echo ""

TOTAL=0
PASS=0
FAIL=0
COMPILE_FAIL=0
NO_SRC=0
STDOUT_ISSUE=0
RESULTS=""

for num in $(seq 551 650); do
    DIR="PE${num}"
    SRC="${DIR}/code/std.cpp"
    if [ ! -f "$SRC" ]; then
        NO_SRC=$((NO_SRC + 1))
        continue
    fi
    TOTAL=$((TOTAL + 1))

    # Compile
    BIN="/tmp/pe${num}_verify"
    COMPILE_OUT=$(g++ -std=c++17 -O2 -o "$BIN" "$SRC" 2>&1)
    COMPILE_RC=$?

    if [ $COMPILE_RC -ne 0 ]; then
        COMPILE_FAIL=$((COMPILE_FAIL + 1))
        RESULTS="${RESULTS}\n[FAIL] PE${num} - COMPILE ERROR: $(echo "$COMPILE_OUT" | head -5 | tr '\n' ' ')"
        echo "[COMPILE FAIL] PE${num}"
        continue
    fi

    # Run with echo "PE{num}" | ./std, 60s timeout
    OUTPUT=$(echo "PE${num}" | timeout 60 "$BIN" 2>&1)
    RUN_RC=$?
    rm -f "$BIN"

    if [ $RUN_RC -eq 124 ]; then
        FAIL=$((FAIL + 1))
        RESULTS="${RESULTS}\n[FAIL] PE${num} - TIMEOUT (>60s)"
        echo "[TIMEOUT] PE${num}"
        continue
    fi

    if [ $RUN_RC -ne 0 ]; then
        FAIL=$((FAIL + 1))
        RESULTS="${RESULTS}\n[FAIL] PE${num} - RUNTIME ERROR (rc=$RUN_RC): $(echo "$OUTPUT" | head -3 | tr '\n' ' ')"
        echo "[RUNTIME FAIL] PE${num}"
        continue
    fi

    # Check output: should be a single non-empty line (the answer)
    OUTPUT=$(echo "$OUTPUT" | xargs)  # trim whitespace
    LINES=$(echo "$OUTPUT" | wc -l | xargs)

    if [ -z "$OUTPUT" ]; then
        FAIL=$((FAIL + 1))
        RESULTS="${RESULTS}\n[FAIL] PE${num} - EMPTY OUTPUT"
        echo "[EMPTY] PE${num}"
        continue
    fi

    if [ "$LINES" -gt 1 ]; then
        STDOUT_ISSUE=$((STDOUT_ISSUE + 1))
        # Multi-line output — check if last line is the answer
        LAST=$(echo "$OUTPUT" | tail -1 | xargs)
        RESULTS="${RESULTS}\n[WARN] PE${num} - MULTI-LINE OUTPUT (${LINES} lines), last line: '$LAST'"
        echo "[MULTI-LINE] PE${num}: ${LINES} lines, last='$LAST'"
        PASS=$((PASS + 1))
    else
        PASS=$((PASS + 1))
        echo "[OK] PE${num}: $OUTPUT"
    fi
done

echo ""
echo "=== SUMMARY ==="
echo "Total PE dirs with code: $TOTAL"
echo "Missing source files: $NO_SRC"
echo "Compile failures: $COMPILE_FAIL"
echo "Runtime failures/timeouts: $((FAIL - STDOUT_ISSUE))"
echo "Multi-line output warnings: $STDOUT_ISSUE"
echo "Passed: $PASS"
echo ""

if [ $COMPILE_FAIL -gt 0 ] || [ $FAIL -gt 0 ]; then
    echo "=== DETAILS ==="
    echo -e "$RESULTS"
fi

echo ""
echo "Finished at $(date)"
