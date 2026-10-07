#!/usr/bin/env python3
"""重试生成失败的题目: 低并发 + 微尺度候选 + 放宽限制。
仅处理 gen_report.json 中 added==0 的题; P2 (原空 data) 题在全部失败时接受 "0" 输出点。
"""
import os, re, sys, json, subprocess
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
GPP = r"F:\tools\mingw64\bin\g++.exe"
WORK = os.path.join(HERE, "gen")
TIMEOUT = 20
MAX_OUT = 100_000
P2 = set("049 059 142 144 147 170 181 194 196 201 221 236 240 250 257 263 288 289 298 316 322 326 327 336 348 365 412 706 708 709 710 941 943 949 950 952 966".split())

def norm(s):
    return "\n".join(l.rstrip() for l in s.replace("\r\n", "\n").split("\n") if l.strip())

def read(p):
    return open(p, encoding="utf-8", errors="surrogateescape", newline="").read()

def run_exe(exe, inp, timeout=TIMEOUT):
    try:
        p = subprocess.run([exe], input=(inp + "\n").encode(), capture_output=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return None, -1
    return p.stdout.decode("utf-8", "replace"), p.returncode

def extra_micro_candidates(n):
    """微尺度: 全2 / 2,3,4递增 / 全3 / 小质数"""
    cands = []
    cands.append(" ".join(["2"] * n))
    cands.append(" ".join(str(2 + i) for i in range(n)))
    cands.append(" ".join(["3"] * n))
    cands.append(" ".join(str(2 * (i + 1)) for i in range(n)))
    cands.append(" ".join(["5"] * n))
    return cands

def process(item):
    pid, cat = item
    pdir = os.path.join(ROOT, pid)
    ddir = os.path.join(pdir, "data")
    os.makedirs(ddir, exist_ok=True)
    src = read(os.path.join(pdir, "code", "std.cpp"))
    r = {"pid": pid, "added": 0, "reason": [], "cat": cat}
    exe = os.path.join(WORK, f"{pid}.exe")
    if not os.path.exists(exe):
        c = subprocess.run([GPP, "-std=c++17", "-O2", os.path.join(pdir, "code", "std.cpp"),
                            "-o", exe], capture_output=True, timeout=180)
        if c.returncode != 0:
            r["reason"].append("COMPILE_FAIL")
            return r
    existing = sorted(f[:-3] for f in os.listdir(ddir) if f.endswith(".in"))
    empty = len(existing) == 0
    # 已有输出集合
    seen = set()
    for e in existing:
        o = os.path.join(ddir, e + ".out")
        if os.path.exists(o): seen.add(norm(read(o)))
    # 候选: 微尺度优先, 再常规阶梯
    m = re.search(r'int\s+main\s*\(', src)
    is_mode = 'getline' in src and not re.search(r'(?:stringstream|istringstream)\s', src) \
              and not re.search(r'\bsto(?:ll|i)\b', src) and not re.search(r'cin\s*>>', src)
    if is_mode:
        ms = set(re.findall(r'==\s*"([A-Za-z_]+)"', src))
        cands = [x for x in ["verify", "compute", "test", "analyze"] if x in ms]
    else:
        # 参数个数: 探测(1..4 个数) —— 黑盒
        cands = []
        for n in (1, 2, 3, 4):
            cands += [" ".join(["2"] * n), " ".join(str(2 + i) for i in range(n)),
                      " ".join(["10"] * n), " ".join(str(10 * (i + 1)) for i in range(n))]
    relax_zero = empty and pid in P2
    kept = 0
    for inp in cands:
        if kept >= 3: break
        out1, rc1 = run_exe(exe, inp)
        if out1 is None or rc1 != 0:
            r["reason"].append(f"[{inp[:16]}]fail_rc{rc1}"); continue
        out2, rc2 = run_exe(exe, inp)
        if out2 is None or norm(out1) != norm(out2):
            r["reason"].append(f"[{inp[:16]}]nondet"); continue
        o = norm(out1)
        if o == "": r["reason"].append(f"[{inp[:16]}]empty"); continue
        if o == "0" and not relax_zero:
            r["reason"].append(f"[{inp[:16]}]zero"); continue
        if len(o) > MAX_OUT: r["reason"].append(f"[{inp[:16]}]big"); continue
        if o in seen: continue
        seen.add(o)
        kept += 1
        idx = kept + len(existing)
        open(os.path.join(ddir, f"{idx:02d}.in"), "w", newline="").write(inp + "\n")
        open(os.path.join(ddir, f"{idx:02d}.out"), "w", newline="").write(o + "\n")
        r["added"] += 1
    return r

def main():
    rep = json.load(open(os.path.join(WORK, "gen_report.json"), encoding="utf-8"))
    targets = [(r["pid"], r.get("cat", "?")) for r in rep if r["added"] == 0]
    print(f"retry targets: {len(targets)}", flush=True)
    results = []
    with ThreadPoolExecutor(max_workers=3) as ex:
        for r in ex.map(process, targets):
            results.append(r)
    got = [r for r in results if r["added"] > 0]
    still = [r for r in results if r["added"] == 0]
    print(f"recovered: {len(got)}  still-zero: {len(still)}")
    for r in still:
        print(f"  STILL {r['pid']} ({r['cat']}): {r['reason'][:3]}")
    json.dump(results, open(os.path.join(WORK, "retry_report.json"), "w", encoding="utf-8"),
              ensure_ascii=False, indent=1)

if __name__ == "__main__":
    main()
