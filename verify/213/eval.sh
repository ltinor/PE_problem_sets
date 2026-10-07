#!/bin/bash
STD="./std"
DATA_DIR="data"
TIME_LIMIT=120
for infile in "$DATA_DIR"/*.in; do
    base=$(basename "$infile" .in)
    echo "===== Timing $base ====="
    python - <<EOF
import subprocess, time
try:
    start=time.time()
    subprocess.run(["$STD"], stdin=open("$infile"), stdout=subprocess.DEVNULL, timeout=$TIME_LIMIT)
    print(f"Time: {time.time()-start:.3f} s")
except subprocess.TimeoutExpired:
    print("Time: >${TIME_LIMIT}s (TLE)")
EOF
done
