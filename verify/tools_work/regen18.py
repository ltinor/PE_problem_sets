#!/usr/bin/env python3
"""为格式错配/UB 嫌疑的 18 题按真实输入格式重新造数。
稳定性协议: 同 exe 双跑 + 换一个新编译 exe 再跑, 三者一致且非空/非0/rc=0/≤10s 才落盘。
"""
import os, re, json, subprocess
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
GPP = r"F:\tools\mingw64\bin\g++.exe"

CANDS = {
 "007": ["3 2 3 5", "4 1 2 3 4 5", "2 10 1000"],
 "015": ["2 3 5 4 7", "1 10 5", "2 8 3 6 4"],
 "024": ["2 10 3 20 5", "1 30 7", "2 12 4 15 6"],
 "096": ["1 534678912672195348198342567859761423426853791713924856961537284287419635345286179",
         "1 53007000060019500000800006000800190000600087000040050000030004008000003000020070004"],
 "102": ["1 0 0 5 0 5", "1 1 1 2 2 3", "2 0 0 5 5 0 1 1 1 2 2 3 3"],
 "114": ["5 3", "10 5"],
 "124": ["100 5", "1000 3", "50 10"],
 "207": ["2 3", "10 7", "6 9"],
 "215": ["3 4", "10 10", "6 7"],
 "222": ["5 3", "10 4", "8 6"],
 "282": ["2 3 100", "3 4 1000", "5 5 100000"],
 "320": ["10 5", "30 7", "100 10"],
 "356": ["10 3 1000000007", "20 5 998244353", "8 2 1000000007"],
 "446": ["10", "100", "1000"],
 "514": ["10 1", "20 2"],
 "824": ["verify"],
 "827": ["verify"],
 "938": ["3 3", "10 5", "6 4"],
}

def strict_norm(s):
    lines = [l.rstrip() for l in s.replace("\r\n", "\n").split("\n")]
    while lines and lines[-1] == "": lines.pop()
    return "\n".join(lines)

def mkexe(pid, tag):
    exe = os.path.join(HERE, f"rg_{pid}_{tag}.exe")
    c = subprocess.run([GPP, "-std=c++17", "-O2", os.path.join(ROOT, pid, "code", "std.cpp"),
                        "-o", exe], capture_output=True, timeout=180)
    return (exe if c.returncode == 0 else None)

def run(exe, inp, t=10):
    try:
        p = subprocess.run([exe], input=(inp + "\n").encode(), capture_output=True, timeout=t)
        return strict_norm(p.stdout.decode("utf-8", "replace")), p.returncode
    except subprocess.TimeoutExpired:
        return None, -1

def process(pid):
    r = {"pid": pid, "added": 0, "why": []}
    e1 = mkexe(pid, "a")
    if not e1:
        r["why"].append("compile_fail"); return r
    ddir = os.path.join(ROOT, pid, "data")
    os.makedirs(ddir, exist_ok=True)
    existing = sorted(f[:-3] for f in os.listdir(ddir) if f.endswith(".in"))
    empty = len(existing) == 0
    src = open(os.path.join(ROOT, pid, "code", "std.cpp"), encoding="utf-8", errors="replace").read()
    if empty and re.search(r'==\s*"PE"', src):
        o1, rc1 = run(e1, "PE"); o2, rc2 = run(e1, "PE")
        if rc1 == 0 and o1 is not None and o1 == o2 and o1:
            open(os.path.join(ddir, "01.in"), "w", newline="").write("PE\n")
            open(os.path.join(ddir, "01.out"), "w", newline="").write(o1 + "\n")
            r["added"] += 1
            existing = ["01"]
        else:
            r["why"].append("probe_fail")
    seen = set()
    for e in existing:
        op = os.path.join(ddir, e + ".out")
        if os.path.exists(op): seen.add(strict_norm(open(op, encoding="utf-8", errors="replace").read()))
    kept = 0
    for inp in CANDS.get(pid, []):
        if kept >= 2: break
        o1, rc1 = run(e1, inp)
        if rc1 != 0 or o1 is None or o1 == "" or o1 == "0":
            r["why"].append(f"[{inp[:14]}]bad_rc{rc1}"); continue
        o2, rc2 = run(e1, inp)
        if rc2 != 0 or o2 != o1:
            r["why"].append(f"[{inp[:14]}]nondet_same_exe"); continue
        e2 = mkexe(pid, "b")
        o3, rc3 = run(e2, inp)
        if rc3 != 0 or o3 != o1:
            r["why"].append(f"[{inp[:14]}]nondet_recompile"); continue
        if o1 in seen:
            r["why"].append(f"[{inp[:14]}]dup"); continue
        seen.add(o1)
        kept += 1
        idx = len(existing) + kept
        open(os.path.join(ddir, f"{idx:02d}.in"), "w", newline="").write(inp + "\n")
        open(os.path.join(ddir, f"{idx:02d}.out"), "w", newline="").write(o1 + "\n")
        r["added"] += 1
    return r

def main():
    pids = list(CANDS.keys())
    res = []
    with ThreadPoolExecutor(max_workers=6) as ex:
        res = list(ex.map(process, pids))
    for r in res:
        line = f"{r['pid']}: +{r['added']}"
        if r["why"]: line += "  why=" + "; ".join(r["why"][:2])
        print(line)

if __name__ == "__main__":
    main()
