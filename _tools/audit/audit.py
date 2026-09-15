#!/usr/bin/env python3
"""PE_problem_sets 题目审计（试点 001-010）

自动检查项：
  1. 编译 code/std.cpp（g++ -std=c++17 -O2）
  2. data/ 数据吻合：对每个 data/*.in 运行 std，与 *.out 比对（忽略行尾空白/结尾空行）
  3. 耗时：记录 data 上单点最大耗时
  4. 专项复核（仅静态分析发现疑点的题）：在题面约束边界上补测，验证疑点

用法：python audit.py 001 010
"""
import glob
import json
import os
import subprocess
import sys
import time

GPP = r"F:/tools/mingw64/bin/g++.exe"
REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TIMEOUT = 10  # data 单点超时上限（秒）

# 专项复核：静态分析疑点 -> 边界输入。label 用于报告标注。
EXTRA_CASES = {
    "006": [("K=1e5 上界（疑 long long 溢出）", b"1\n100000\n", 15,
             "exact", "100000")],
    "007": [("K=1e7 上界（疑筛表 1.9e8 超时/内存）", b"1\n10000000\n", 60,
             "none", None)],
}


def norm(b: bytes) -> str:
    s = b.decode("utf-8", "replace").replace("\r\n", "\n")
    lines = [l.rstrip() for l in s.split("\n")]
    while lines and lines[-1] == "":
        lines.pop()
    return "\n".join(lines)


def run_exe(exe: str, stdin_bytes: bytes, timeout: float):
    t0 = time.perf_counter()
    try:
        p = subprocess.run([exe], input=stdin_bytes, stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE, timeout=timeout)
        return time.perf_counter() - t0, p.returncode, p.stdout
    except subprocess.TimeoutExpired:
        return time.perf_counter() - t0, -1, b""


def compile_cpp(src: str, exe: str):
    p = subprocess.run([GPP, "-std=c++17", "-O2", src, "-o", exe],
                       stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return p.returncode == 0, p.stderr.decode("utf-8", "replace")


def truth_006(K: int) -> int:
    s = K * (K + 1) // 2
    sq = K * (K + 1) * (2 * K + 1) // 6
    return s * s - sq


def check_extra(pid: str, exe: str):
    """专项复核。truth 模式：exact=与 Python 大整数真值比对；none=只测耗时。"""
    out = []
    for label, inp, tmo, mode, arg in EXTRA_CASES.get(pid, []):
        el, rc, so = run_exe(exe, inp, tmo)
        item = {"label": label, "input": inp.decode(), "time": round(el, 3),
                "returncode": rc, "output": norm(so)[:200]}
        if mode == "exact":
            K = int(arg)
            item["expected"] = str(truth_006(K))
            item["match"] = (rc == 0 and norm(so) == item["expected"])
        out.append(item)
    return out


def audit_one(pid: str, workdir: str):
    r = {"problem": pid, "compile": "SKIP", "data": [], "data_max_time": None,
         "extra": []}
    src = os.path.join(REPO, pid, "code", "std.cpp")
    if not os.path.exists(src):
        r["compile"] = "NO_SOURCE"
        return r
    exe = os.path.join(workdir, f"std_{pid}.exe")
    ok, err = compile_cpp(src, exe)
    if not ok:
        r["compile"] = "FAIL"
        r["compile_err"] = err[-500:]
        return r
    r["compile"] = "OK"

    ins = sorted(glob.glob(os.path.join(REPO, pid, "data", "*.in")))
    times = []
    for in_f in ins:
        out_f = in_f[:-3] + ".out"
        if not os.path.exists(out_f):
            r["data"].append({"case": os.path.basename(in_f), "result": "NO_OUT"})
            continue
        with open(in_f, "rb") as f:
            stdin_bytes = f.read()
        with open(out_f, "rb") as f:
            expected = norm(f.read())
        el, rc, so = run_exe(exe, stdin_bytes, TIMEOUT)
        times.append(el)
        if rc == -1:
            res = "TLE"
        elif rc != 0:
            res = "RUNTIME_ERROR"
        else:
            res = "AC" if norm(so) == expected else "WA"
        r["data"].append({"case": os.path.basename(in_f), "result": res,
                          "time": round(el, 3)})
    r["data_max_time"] = round(max(times), 3) if times else None
    r["extra"] = check_extra(pid, exe)
    return r


def main():
    lo, hi = (sys.argv[1], sys.argv[2]) if len(sys.argv) > 2 else ("001", "010")
    pids = [f"{i:03d}" for i in range(int(lo), int(hi) + 1)]
    workdir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_work")
    os.makedirs(workdir, exist_ok=True)

    results = [audit_one(p, workdir) for p in pids]

    out_json = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                            f"result_{lo}-{hi}.json")
    with open(out_json, "w", encoding="utf-8") as f:
        json.dump(results, f, ensure_ascii=False, indent=1)

    for r in results:
        n_ac = sum(1 for d in r["data"] if d["result"] == "AC")
        flags = []
        if r["compile"] != "OK":
            flags.append(r["compile"])
        bad = [d["result"] for d in r["data"] if d["result"] != "AC"]
        if bad:
            flags.append("/".join(sorted(set(bad))))
        for e in r["extra"]:
            if e.get("match") is False:
                flags.append("EXTRA_MISMATCH")
            elif e["returncode"] == -1:
                flags.append("EXTRA_TLE")
        print(f'{r["problem"]}: compile={r["compile"]} '
              f'data={n_ac}/{len(r["data"])} '
              f'max_time={r["data_max_time"]}s '
              f'{"[" + ",".join(flags) + "]" if flags else "[OK]"}')
        for e in r["extra"]:
            print(f'    extra: {e["label"]} time={e["time"]}s rc={e["returncode"]}'
                  + (f' expected={e.get("expected")} got={e["output"]}'
                     if "expected" in e else f' out={e["output"][:60]}'))
    print(f"\nJSON -> {out_json}")


if __name__ == "__main__":
    main()
