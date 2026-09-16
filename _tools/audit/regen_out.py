#!/usr/bin/env python3
"""重新生成题目 data/*.out：运行 std 于每个 *.in，写出 *.out。

用法：python regen_out.py 058 [059 ...]
- 默认单点超时 120s；TLE/运行错误的点保留原 .out（若无则留缺）并报告。
- 生成完成后自动复跑一遍 std-vs-.out 一致性校验。
"""
import glob
import os
import subprocess
import sys

GPP = r"F:/tools/mingw64/bin/g++.exe"
REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
WORK = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_work")
TIMEOUT = 120


def norm(b):
    s = b.decode("utf-8", "replace").replace("\r\n", "\n")
    ls = [l.rstrip() for l in s.split("\n")]
    while ls and ls[-1] == "":
        ls.pop()
    return "\n".join(ls)


def main():
    for pid_s in sys.argv[1:]:
        exe = os.path.join(WORK, f"std_{pid_s}.exe")
        p = subprocess.run([GPP, "-std=c++17", "-O2",
                            os.path.join(REPO, pid_s, "code", "std.cpp"),
                            "-o", exe], capture_output=True)
        if p.returncode != 0:
            print(f"{pid_s}: COMPILE FAIL")
            continue
        ok = bad = 0
        for in_f in sorted(glob.glob(os.path.join(REPO, pid_s, "data", "*.in"))):
            try:
                r = subprocess.run([exe], stdin=open(in_f, "rb"),
                                   stdout=subprocess.PIPE, timeout=TIMEOUT)
                if r.returncode != 0:
                    print(f"{pid_s}/{os.path.basename(in_f)}: RUNTIME_ERROR rc={r.returncode}")
                    bad += 1
                    continue
                with open(in_f[:-3] + ".out", "wb") as f:
                    f.write(r.stdout.replace(b"\n", b"\n"))
                ok += 1
            except subprocess.TimeoutExpired:
                print(f"{pid_s}/{os.path.basename(in_f)}: TLE >{TIMEOUT}s, 保留原状")
                bad += 1
        # 复跑校验
        mism = []
        for in_f in sorted(glob.glob(os.path.join(REPO, pid_s, "data", "*.in"))):
            out_f = in_f[:-3] + ".out"
            if not os.path.exists(out_f):
                continue
            try:
                r = subprocess.run([exe], stdin=open(in_f, "rb"),
                                   stdout=subprocess.PIPE, timeout=TIMEOUT)
                if norm(r.stdout) != norm(open(out_f, "rb").read()):
                    mism.append(os.path.basename(in_f))
            except subprocess.TimeoutExpired:
                mism.append(os.path.basename(in_f) + "(TLE)")
        print(f"{pid_s}: generated={ok} failed={bad} verify_mismatch={mism}")


if __name__ == "__main__":
    main()
