#!/bin/bash
STD="./std"
DATA_DIR="data"
TIME_LIMIT=1
for infile in "$DATA_DIR"/*.in; do
    base=$(basename "$infile" .in)
    echo "===== Timing $base ====="
    python - <<EOF
import subprocess, time
try:
    start=time.time()
    subprocess.run(["./std"], stdin=open("$infile"), stdout=subprocess.DEVNULL, timeout=1)
    elapsed=time.time()-start
    print(f"Time: {elapsed:.3f} s")
except subprocess.TimeoutExpired:
    print("Time: >1s (TLE)")
EOF
done
