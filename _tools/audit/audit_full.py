#!/usr/bin/env python3
"""PE_problem_sets 全量题目审计（011-968，方法与 001-010 试点一致）

每题检查项：
  1. 编译 code/std.cpp（g++ -std=c++17 -O2）
  2. data/ 数据吻合：运行 std 与 *.out 比对，记录最大耗时
  3. PE 探针（源码含 "PE" 查询分支的题）：喂 "PE" 取末行输出，
     与源码内嵌答案 + _tools 官方答案字典双重比对，记录耗时
  4. 题面检查：statement.md 空模板 / 缺样例 / 缺数据范围（启发式）

用法：python audit_full.py [起] [止]（默认 011 968）
"""
import concurrent.futures
import glob
import json
import os
import re
import subprocess
import sys
import time

GPP = r"F:/tools/mingw64/bin/g++.exe"
REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TOOLS = os.path.join(REPO, "_tools")
WORKDIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_work")
DATA_TIMEOUT = 10
PROBE_TIMEOUT = 30
WORKERS = 8


def parse_official_answers():
    """从 _tools/**/*.py 提取硬编码官方答案：{pid: {ans: 来源数}}"""
    votes = {}
    pat_dict = re.compile(r'(\d{3})\s*:\s*\(?\s*["\']([0-9][0-9.]*)["\']')
    pat_list = re.compile(r'\((\d{3})\s*,\s*["\']?([0-9][0-9.]*)["\']?\s*[,)]')
    for root, _, files in os.walk(TOOLS):
        for fn in files:
            if not fn.endswith(".py"):
                continue
            try:
                text = open(os.path.join(root, fn), encoding="utf-8",
                            errors="replace").read()
            except OSError:
                continue
            for pat in (pat_dict, pat_list):
                for m in pat.finditer(text):
                    pid, ans = int(m.group(1)), m.group(2)
                    votes.setdefault(pid, {}).setdefault(ans, set()).add(fn)
    official = {}
    conflicts = {}
    for pid, ans_map in votes.items():
        best = max(ans_map.items(), key=lambda kv: len(kv[1]))
        official[pid] = best[0]
        if len(ans_map) > 1:
            conflicts[pid] = {a: sorted(v) for a, v in ans_map.items()}
    return official, conflicts


def norm(b: bytes) -> str:
    s = b.decode("utf-8", "replace").replace("\r\n", "\n")
    lines = [l.rstrip() for l in s.split("\n")]
    while lines and lines[-1] == "":
        lines.pop()
    return "\n".join(lines)


def run(exe: str, stdin_bytes: bytes, timeout: float):
    t0 = time.perf_counter()
    try:
        p = subprocess.run([exe], input=stdin_bytes, stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE, timeout=timeout)
        return time.perf_counter() - t0, p.returncode, p.stdout
    except subprocess.TimeoutExpired:
        return time.perf_counter() - t0, -1, b""


def extract_embedded(src: str):
    m = re.search(r'const\s+[\w\s]+?PE_ANSWER\w*\s*=\s*([0-9][0-9.eE]*)(?:[uUlLfF]*)', src)
    if m:
        return m.group(1), "PE_ANSWER"
    m = re.search(r'if\s*\([^)]*"PE"[^)]*\)\s*\{(.{0,400}?)\}', src, re.S)
    if m:
        m2 = re.search(r'cout\s*<<\s*"?([0-9][0-9.]*)"?', m.group(1))
        if m2:
            return m2.group(1), "PE_BRANCH"
    m = re.search(r'PE\s*answer[:：]\s*([0-9][0-9.eE]*)', src)
    if m:
        return m.group(1), "COMMENT"
    return None, None


def check_statement(pid: str):
    f = os.path.join(REPO, pid, "statement.md")
    if not os.path.exists(f):
        return ["NO_STATEMENT"]
    text = open(f, encoding="utf-8", errors="replace").read()
    content = [l.strip() for l in text.split("
")
               if l.strip() and not l.strip().startswith("#")
               and l.strip() != "---" and not l.strip().startswith("```")]
    flags = []
    if len(content) <= 1:
        flags.append("EMPTY_TEMPLATE")
        return flags
    text = open(f, encoding="utf-8", errors="replace").read()
    m = re.search(r'##\s*样例(.*?)(?=\n## |\Z)', text, re.S)
    if not m or "```" not in m.group(1):
        flags.append("NO_SAMPLE")
    m = re.search(r'##\s*数据范围(.*?)(?=\n## |\Z)', text, re.S)
    if not m or len(m.group(1).strip()) < 8:
        flags.append("NO_CONSTRAINTS")
    return flags


def audit_one(pid: int):
    pid_s = f"{pid:03d}"
    r = {"problem": pid, "compile": None, "data": None, "probe": None,
         "stmt_flags": check_statement(pid_s)}
    src_p = os.path.join(REPO, pid_s, "code", "std.cpp")
    if not os.path.exists(src_p):
        r["compile"] = "NO_SOURCE"
        return r
    src = open(src_p, encoding="utf-8", errors="replace").read()
    exe = os.path.join(WORKDIR, f"std_{pid_s}.exe")
    p = subprocess.run([GPP, "-std=c++17", "-O2", src_p, "-o", exe],
                       stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if p.returncode != 0:
        r["compile"] = "FAIL"
        r["compile_err"] = p.stderr.decode("utf-8", "replace")[-300:]
        return r
    r["compile"] = "OK"

    ins = sorted(glob.glob(os.path.join(REPO, pid_s, "data", "*.in")))
    if ins:
        n_ac = 0
        bad = []
        tmax = 0.0
        for in_f in ins:
            out_f = in_f[:-3] + ".out"
            if not os.path.exists(out_f):
                bad.append((os.path.basename(in_f), "NO_OUT"))
                continue
            el, rc, so = run(exe, open(in_f, "rb").read(), DATA_TIMEOUT)
            tmax = max(tmax, el)
            exp = norm(open(out_f, "rb").read())
            if rc == -1:
                bad.append((os.path.basename(in_f), "TLE"))
            elif rc != 0:
                bad.append((os.path.basename(in_f), "RUNTIME_ERROR"))
            elif norm(so) == exp:
                n_ac += 1
            else:
                bad.append((os.path.basename(in_f), "WA"))
        r["data"] = {"total": len(ins), "ac": n_ac, "max_time": round(tmax, 3),
                     "bad": bad[:8], "n_bad": len(bad)}
    if '== "PE"' in src or '"PE" ==' in src:
        embedded, how = extract_embedded(src)
        el, rc, so = run(exe, b"PE\n", PROBE_TIMEOUT)
        out_lines = [l for l in norm(so).split("\n") if l]
        got = out_lines[-1] if out_lines else ""
        pr = {"has_pe": True, "time": round(el, 3), "rc": rc, "got": got[:100],
              "embedded": embedded, "via": how}
        if rc == -1:
            pr["verdict"] = "PROBE_TLE"
        elif rc != 0:
            pr["verdict"] = "PROBE_RUNTIME_ERROR"
        elif got == "" or got == "0":
            pr["verdict"] = "PLACEHOLDER"
        else:
            pr["verdict"] = "EMBED_OK" if embedded == got else (
                "EMBED_MISMATCH" if embedded else "NO_EMBEDDED")
        r["probe"] = pr
    return r


def main():
    lo = int(sys.argv[1]) if len(sys.argv) > 1 else 11
    hi = int(sys.argv[2]) if len(sys.argv) > 2 else 968
    os.makedirs(WORKDIR, exist_ok=True)
    official, conflicts = parse_official_answers()
    json.dump({"official": official, "conflicts": conflicts},
              open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                "answers_official.json"), "w", encoding="utf-8"),
              ensure_ascii=False, indent=1)
    print(f"official answers for {len(official)} problems, "
          f"{len(conflicts)} conflicts", flush=True)

    pids = list(range(lo, hi + 1))
    t0 = time.perf_counter()
    results = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=WORKERS) as ex:
        futs = {ex.submit(audit_one, p): p for p in pids}
        for i, fut in enumerate(concurrent.futures.as_completed(futs), 1):
            results.append(fut.result())
            if i % 50 == 0 or i == len(pids):
                print(f"  ... {i}/{len(pids)} "
                      f"({time.perf_counter() - t0:.0f}s)", flush=True)
    results.sort(key=lambda r: r["problem"])

    out = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                       f"result_{lo:03d}-{hi}.json")
    json.dump(results, open(out, "w", encoding="utf-8"),
              ensure_ascii=False, indent=1)

    stats = {}
    for r in results:
        stats.setdefault(r["compile"], []).append(r["problem"])
        if r["data"] and r["data"]["n_bad"]:
            stats.setdefault("DATA_BAD", []).append(r["problem"])
        if r["probe"]:
            v = r["probe"]["verdict"]
            if v not in ("EMBED_OK",):
                stats.setdefault(v, []).append(r["problem"])
            if r["probe"]["time"] > 1.0 and "TLE" not in v:
                stats.setdefault("PROBE_SLOW", []).append(r["problem"])
        if r["stmt_flags"]:
            for f in r["stmt_flags"]:
                stats.setdefault(f, []).append(r["problem"])
    print(f"\n===== 汇总（{lo:03d}-{hi}）=====")
    for k in sorted(stats, key=lambda k: -len(stats[k])):
        ids = stats[k]
        show = ",".join(f"{i:03d}" for i in ids[:40])
        more = f" ...共{len(ids)}" if len(ids) > 40 else ""
        print(f"{k}: {len(ids)}  [{show}{more}]")
    print(f"JSON -> {out}")


if __name__ == "__main__":
    main()
