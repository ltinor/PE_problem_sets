#!/usr/bin/env python3
"""修复本会话生成的问题数据文件:
   - WA: 用实际 stdout 严格规范化(保留内部空行)重写 .out; 两次运行不一致者删点
   - TLE: 10s 复测, 仍超时删点
"""
import os, json, subprocess
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
GPP = r"F:\tools\mingw64\bin\g++.exe"
WORK = os.path.join(HERE, "gen")

def strict_norm(s):
    lines = [l.rstrip() for l in s.replace("\r\n", "\n").split("\n")]
    while lines and lines[-1] == "": lines.pop()
    return "\n".join(lines)

def read(p):
    return open(p, encoding="utf-8", errors="surrogateescape", newline="").read()

def process(item):
    rel, kind = item
    pid = rel.split("/")[0]
    in_p = os.path.join(ROOT, rel)
    out_p = in_p[:-3] + ".out"
    exe = os.path.join(WORK, f"{pid}.exe")
    if not os.path.exists(exe):
        c = subprocess.run([GPP, "-std=c++17", "-O2",
                            os.path.join(ROOT, pid, "code", "std.cpp"), "-o", exe],
                           capture_output=True, timeout=180)
        if c.returncode != 0:
            return rel, "compile_fail", None
    data = open(in_p, "rb").read()
    def run(t):
        try:
            p = subprocess.run([exe], input=data, capture_output=True, timeout=t)
            return strict_norm(p.stdout.decode("utf-8", "replace")), p.returncode
        except subprocess.TimeoutExpired:
            return None, -1
    if kind == "TLE":
        o1, rc1 = run(10)
        if rc1 == 0 and o1 is not None:
            o2, rc2 = run(10)
            if rc2 == 0 and o1 == o2 and o1 != "":
                open(out_p, "w", encoding="utf-8", newline="").write(o1 + "\n")
                return rel, "rewrote(10s-ok)", None
        os.remove(in_p); os.remove(out_p)
        return rel, "dropped(TLE)", None
    o1, rc1 = run(15)
    if rc1 != 0 or o1 is None:
        os.remove(in_p); os.remove(out_p)
        return rel, f"dropped(rc{rc1})", None
    o2, rc2 = run(15)
    if rc2 != 0 or o2 is None or o1 != o2 or o1 == "":
        os.remove(in_p); os.remove(out_p)
        return rel, "dropped(nondet)", None
    open(out_p, "w", encoding="utf-8", newline="").write(o1 + "\n")
    return rel, "rewrote", None

def main():
    bad = json.load(open(os.path.join(HERE, "bad_split.json")))
    mine = bad["mine"]
    print(f"fixing {len(mine)} files", flush=True)
    results = []
    with ThreadPoolExecutor(max_workers=6) as ex:
        for r in ex.map(process, mine):
            results.append(r)
    from collections import Counter
    cnt = Counter(s for _, s, _ in results)
    print(dict(cnt))

if __name__ == "__main__":
    main()
