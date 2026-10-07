#!/bin/bash
# eval.sh — time std on each data input, must finish within 1s
STD="./std"
DATA_DIR="data"
TIME_LIMIT=1
for infile in "$DATA_DIR"/*.in; do
    base=$(basename "$infile" .in)
    echo "===== $base ====="
    start=$(python -c "import time; print(int(time.time()*1000))")
    python - <<EOF
import subprocess, time
try:
    start = time.time()
    subprocess.run(["$STD"], stdin=open("$infile"), stdout=subprocess.DEVNULL, timeout=$TIME_LIMIT)
    elapsed = time.time() - start
    print(f"Time: {elapsed:.3f} s")
except subprocess.TimeoutExpired:
    print("Time: >${TIME_LIMIT}s (TLE)")
EOF
done
