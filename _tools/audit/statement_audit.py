#!/usr/bin/env python3
# 题面全量自审: 章节完整性 / 样例与 std 实跑核对 / 题面-数据-PE答案一致性
# 用法: python _tools/audit/statement_audit.py [起] [止]
import os, re, sys, json, subprocess, tempfile
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
GPP = r"F:\tools\mingw64\bin\g++.exe"
pe_answers = json.load(open(os.path.join(ROOT, "_tools", "audit", "pe_answers.json")))

def parse_statement(txt):
    """返回 dict: skeleton, sections, samples=[(inp,out)], pe_answer_line"""
    r = {"skeleton": bool(re.search(r"待人工|待补充|自动生成的骨架", txt)),
         "sections": {}, "samples": [], "pe_line": None}
    for sec in ["输入格式", "输出格式", "样例", "数据范围"]:
        m = re.search(r"##+\s*" + sec, txt)
        r["sections"][sec] = m is not None
    m = re.search(r"PE\s*答案[::]\s*([^\n]+)", txt)
    if m: r["pe_line"] = m.group(1).strip()
    # 样例区内的 输入/输出 代码块对
    sm = re.search(r"##+\s*样例(.*?)(?=\n##+\s*[^#\n]|\Z)", txt, re.S)
    if sm:
        body = sm.group(1)
        ins = re.findall(r"###\s*输入[\s\S]*?```\n(.*?)```", body)
        outs = re.findall(r"###\s*输出[\s\S]*?```\n(.*?)```", body)
        for a, b in zip(ins, outs):
            r["samples"].append((a, b))
        if len(ins) != len(outs):
            r["samples_mismatch"] = (len(ins), len(outs))
    return r

def norm(tok):
    return tok.split()

def compare(got, want):
    g, w = norm(got), norm(want)
    if len(g) != len(w): return False, f"token count {len(g)} vs {len(w)}"
    for a, b in zip(g, w):
        if a == b: continue
        try:
            fa, fb = float(a), float(b)
            if abs(fa - fb) <= 1e-6 * max(1.0, abs(fb)): continue
        except ValueError:
            pass
        return False, f"'{a}' vs '{b}'"
    return True, ""

def check_problem(pid):
    pdir = os.path.join(ROOT, pid)
    res = {"id": pid, "issues": [], "info": []}
    spath = os.path.join(pdir, "statement.md")
    if not os.path.exists(spath):
        res["issues"].append("NO_STATEMENT"); return res
    txt = open(spath, encoding="utf-8", errors="replace").read()
    st = parse_statement(txt)
    res["skeleton"] = st["skeleton"]
    if st["skeleton"]: res["info"].append("SKELETON")
    for sec, ok in st["sections"].items():
        if not ok: res["issues"].append("NO_SECTION:" + sec)
    if st.get("samples_mismatch"): res["issues"].append(f"SAMPLE_PAIRS_MISMATCH {st['samples_mismatch']}")
    # PE 答案行 vs 官方表
    if st["pe_line"] and str(int(pid)) in pe_answers:
        off = pe_answers[str(int(pid))]
        if off.strip() not in st["pe_line"]:
            res["issues"].append(f"PE_ANSWER_MISMATCH stmt='{st['pe_line']}' official='{off}'")
    # data 完整性
    ddir = os.path.join(pdir, "data")
    has_data = os.path.isdir(ddir)
    ins = sorted(f for f in os.listdir(ddir) if f.endswith(".in")) if has_data else []
    for f in ins:
        if not os.path.exists(os.path.join(ddir, f[:-3] + ".out")):
            res["issues"].append("DATA_NO_OUT:" + f)
    if not has_data: res["info"].append("NO_DATA")
    # 样例实跑
    if st["samples"]:
        src = os.path.join(pdir, "code", "std.cpp")
        if not os.path.exists(src):
            res["issues"].append("SAMPLE_NO_STD")
            return res
        exe = os.path.join(tempfile.gettempdir(), f"saudit_{pid}.exe")
        c = subprocess.run([GPP, "-std=c++17", "-O2", src, "-o", exe],
                           capture_output=True, timeout=120)
        if c.returncode != 0:
            res["issues"].append("STD_COMPILE_FAIL"); return res
        for i, (si, so) in enumerate(st["samples"]):
            try:
                r = subprocess.run([exe], input=si.encode(), capture_output=True, timeout=20)
                if r.returncode != 0:
                    res["issues"].append(f"SAMPLE{i+1}_RUNTIME_FAIL rc={r.returncode}")
                else:
                    ok, msg = compare(r.stdout.decode("utf-8", "replace"), so)
                    if not ok: res["issues"].append(f"SAMPLE{i+1}_WRONG: {msg}")
            except subprocess.TimeoutExpired:
                res["issues"].append(f"SAMPLE{i+1}_TLE")
        try: os.remove(exe)
        except OSError: pass
    elif has_data:
        res["info"].append("NO_SAMPLE_IN_STATEMENT")
    return res

def main():
    lo, hi = sys.argv[1] if len(sys.argv) > 1 else "001", sys.argv[2] if len(sys.argv) > 2 else "968"
    pids = [d for d in os.listdir(ROOT) if re.fullmatch(r"\d{3}", d) and lo <= d <= hi]
    pids.sort()
    results = []
    with ThreadPoolExecutor(max_workers=8) as ex:
        for r in ex.map(check_problem, pids):
            results.append(r)
    bad = [r for r in results if r["issues"]]
    print(f"total={len(results)} with_issues={len(bad)}")
    from collections import Counter
    cnt = Counter(i.split(":")[0].split("_")[0] for r in bad for i in r["issues"])
    print("issue types:", dict(cnt))
    for r in results:
        if r["issues"]:
            print(f"[{r['id']}] " + " | ".join(r["issues"]))
    json.dump(results, open(os.path.join(ROOT, "_tools", "audit", "statement_audit.json"), "w"), ensure_ascii=False, indent=1)
    # 汇总统计
    skel = sum(1 for r in results if r.get("skeleton"))
    nosample = sum(1 for r in results if "NO_SAMPLE_IN_STATEMENT" in r["info"])
    print(f"skeletons={skel} with_data_but_no_sample={nosample}")

if __name__ == "__main__":
    main()
