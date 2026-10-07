#!/usr/bin/env python3
"""从题面样例收割数据点: 提取 样例 输入/输出 对, std 实跑验证一致后写为 data 点。
只处理还没有数据或数据点 <3 的题; 输入=="PE" 或输出重复的跳过。
"""
import os, re, sys, json, subprocess
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
GPP = r"F:\tools\mingw64\bin\g++.exe"
WORK = os.path.join(HERE, "gen")

def norm(s):
    return "\n".join(l.rstrip() for l in s.replace("\r\n", "\n").split("\n") if l.strip())

def read(p):
    return open(p, encoding="utf-8", errors="surrogateescape", newline="").read()

def parse_samples(txt):
    """样例提取(行状态机, 兼容 CRLF): 样例节止于下一个 '## ' 二级头, 内部 ### 输入/输出 + ``` 围栏对。"""
    txt = txt.replace("\r\n", "\n")
    sm = re.search(r"##+\s*样例(.*?)(?=\n## |\Z)", txt, re.S)
    if not sm: return []
    lines = sm.group(1).split("\n")
    pairs, kind, buf, fence = [], None, [], False
    for ln in lines:
        s = ln.strip()
        if s.startswith("###") and not fence:
            if kind and buf: pairs.append((kind, "\n".join(buf).strip("\n")))
            kind = "in" if "输入" in s else ("out" if "输出" in s else None)
            buf, fence = [], False
        elif s == "```":
            if fence:  # 围栏闭合
                if kind and buf: pairs.append((kind, "\n".join(buf).strip("\n")))
                kind, buf, fence = None, [], False
            else:
                fence = True  # 围栏打开
        elif fence and kind is not None:
            buf.append(ln)
    if fence and kind and buf: pairs.append((kind, "\n".join(buf).strip("\n")))
    ins = [c for k, c in pairs if k == "in"]
    outs = [c for k, c in pairs if k == "out"]
    return list(zip(ins, outs))

def run_exe(exe, inp_bytes, timeout=20):
    try:
        p = subprocess.run([exe], input=inp_bytes, capture_output=True, timeout=timeout)
        return norm(p.stdout.decode("utf-8", "replace")), p.returncode
    except subprocess.TimeoutExpired:
        return None, -1

def process(pid):
    r = {"pid": pid, "added": 0, "why": []}
    sp = os.path.join(ROOT, pid, "statement.md")
    ddir = os.path.join(ROOT, pid, "data")
    if not os.path.exists(sp):
        r["why"].append("no_stmt"); return r
    samples = parse_samples(read(sp))
    if not samples:
        r["why"].append("no_sample"); return r
    exe = os.path.join(WORK, f"{pid}.exe")
    if not os.path.exists(exe):
        c = subprocess.run([GPP, "-std=c++17", "-O2",
                            os.path.join(ROOT, pid, "code", "std.cpp"), "-o", exe],
                           capture_output=True, timeout=180)
        if c.returncode != 0:
            r["why"].append("compile_fail"); return r
    existing = sorted(f[:-3] for f in os.listdir(ddir) if f.endswith(".in"))
    if len(existing) >= 4:
        r["why"].append("enough"); return r
    seen = set()
    for e in existing:
        o = os.path.join(ddir, e + ".out")
        if os.path.exists(o): seen.add(norm(read(o)))
    for si, so in samples:
        if len(existing) >= 4: break
        inp_txt, want = si.strip("\n"), so.strip()
        if norm(inp_txt) == "PE": r["why"].append("sample=PE"); continue
        got, rc = run_exe(exe, (inp_txt + "\n").encode())
        if rc != 0 or got is None:
            r["why"].append(f"rc={rc}"); continue
        if got != norm(want):
            r["why"].append(f"sample_mismatch got={got[:24]!r} want={want[:24]!r}"); continue
        if got in seen or got == "":
            r["why"].append("dup_or_empty"); continue
        seen.add(got)
        idx = len(existing) + 1
        existing.append(f"{idx:02d}")
        open(os.path.join(ddir, f"{idx:02d}.in"), "w", newline="").write(inp_txt + "\n")
        open(os.path.join(ddir, f"{idx:02d}.out"), "w", newline="").write(got + "\n")
        r["added"] += 1
    return r

def main():
    lo, hi = sys.argv[1], sys.argv[2]
    targets = []
    for d in sorted(os.listdir(ROOT)):
        if not re.fullmatch(r"\d{3}", d) or not (lo <= d <= hi): continue
        dd = os.path.join(ROOT, d, "data")
        n = len([f for f in os.listdir(dd) if f.endswith(".in")]) if os.path.isdir(dd) else 0
        if n < 4:
            targets.append(d)
    print(f"harvest targets: {len(targets)}", flush=True)
    res = []
    with ThreadPoolExecutor(max_workers=6) as ex:
        for r in ex.map(process, targets):
            res.append(r)
    got = sum(r["added"] for r in res)
    print(f"harvested points: {got}")
    from collections import Counter
    why = Counter(w for r in res for w in r["why"] if r["added"] == 0)
    print("no-add reasons:", dict(why.most_common(8)))
    for r in res:
        if r["added"] == 0 and any("mismatch" in w for w in r["why"]):
            print(f"  MISMATCH {r['pid']}: {r['why'][:1]}")
    json.dump(res, open(os.path.join(WORK, "harvest_report.json"), "w", encoding="utf-8"),
              ensure_ascii=False, indent=1)

if __name__ == "__main__":
    main()
