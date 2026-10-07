#!/usr/bin/env python3
"""P1/P2: 为单点题追加参数化数据点, 为空 data 题生成数据。

候选输入来源:
  - 静态解析 main() 的 cin>>/stringstream>> 参数链 (数量+守卫上限)
  - 解析失败则黑盒阶梯探测 (1~3 个参数 × 多档数值)
候选校验 (全部通过才落盘):
  rc==0, <15s, 跑两遍输出一致(确定性), 输出非空/非"0"/≠PE探针输出, 输出间去重
模式切换题 (mode_only): 依次尝试 verify/compute/test/analyze 等内置模式
空 data 题 (P2): 先补 01=PE 探针点, 参数用缩小阶梯, 并在题面数据范围标注
"""
import os, re, sys, json, subprocess
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
GPP = r"F:\tools\mingw64\bin\g++.exe"
WORK = os.path.join(HERE, "gen")
os.makedirs(WORK, exist_ok=True)
TIMEOUT = 15
MAX_POINTS = 3
MAX_OUT = 100_000

def norm(s):
    return "\n".join(l.rstrip() for l in s.replace("\r\n", "\n").split("\n") if l.strip())

def read(p):
    return open(p, encoding="utf-8", errors="surrogateescape", newline="").read()

def brace_block(src, i):
    depth = 0
    for j in range(i, len(src)):
        if src[j] == "{": depth += 1
        elif src[j] == "}":
            depth -= 1
            if depth == 0: return src[i:j+1], i, j+1
    return src[i:], i, len(src)

def parse_params(src):
    """返回 (nparams, caps) 或 None。"""
    m = re.search(r'int\s+main\s*\(', src)
    if not m: return None
    body, _, _ = brace_block(src, src.find('{', m.start()))
    # 截取 PE 分支之后的主体: 找 == "PE" 分支结束位置
    pe = re.search(r'==\s*"PE"', body)
    seg = body[pe.end():] if pe else body
    vars_ = []
    # stoll/stoi 令牌风格: first token 即数值参数
    tok_var = None
    m2 = re.search(r'(?:ll|int|long long)\s+(\w+)\s*=\s*sto(?:ll|i)\s*\(\s*(\w+)\s*\)', seg)
    if m2:
        tok_var = m2.group(2)
        vars_.append(tok_var)
    for cm in re.finditer(r'\b(?:cin|ss|is|iss)\s*((?:\s*>>\s*[A-Za-z_]\w*)+)\s*;', seg):
        for vm in re.finditer(r'>>\s*([A-Za-z_]\w*)', cm.group(1)):
            v = vm.group(1)
            if v != tok_var and v not in vars_:
                vars_.append(v)
    if not vars_: return None
    # 守卫上限: v > NUM / v >= NUM (取最小约束), 或 NUM < v
    caps = {}
    for v in vars_:
        c = None
        for gm in re.finditer(rf'{v}\s*(?:>|>=)\s*([0-9][0-9_a-fA-FxX.]*)[uUlL]*', body):
            num = gm.group(1).rstrip(".")
            try:
                if "x" in num or "X" in num:
                    val = float(int(num.replace("_",""), 16))
                else:
                    val = float(num.replace("_","").split("e")[0].split("E")[0])
            except ValueError: continue
            c = val if c is None else min(c, val)
        for gm in re.finditer(rf'([0-9][0-9_.eE]*)[uUlL]*\s*<\s*{v}\b', body):
            try: val = float(gm.group(1).replace("_",""))
            except ValueError: continue
            c = val if c is None else min(c, val)
        caps[v] = c
    return len(vars_), caps

def candidates_for(pid, src):
    """生成候选输入行 (按 质量 顺序)。"""
    pp = parse_params(src)
    cands = []
    if pp:
        n, caps = pp
        names = list(caps.keys())
        def val_for(idx, scale):
            c = caps.get(names[idx]) if idx < len(names) else None
            base = scale * (10 ** idx)
            if c and c >= 4:
                return max(1, min(base, int(c * 0.5)))
            return base
        cands.append(" ".join(["1"] * n))
        cands.append(" ".join(str(val_for(i, 10)) for i in range(n)))
        cands.append(" ".join(str(val_for(i, 1000)) for i in range(n)))
        if any((caps.get(nm) or 0) >= 10 for nm in names):
            cands.append(" ".join(
                str(min(int(caps.get(nm) or 100000) - 1, 10_000_000))
                if (caps.get(nm) or 0) >= 10 else "3" for nm in names))
    else:
        # 黑盒阶梯: 1~3 参数
        for k in (1, 2, 3):
            for scale in (10, 1000, 100000):
                cands.append(" ".join(str(scale // (10 ** j) or 1) for j in range(k)))
    return cands

MODE_ORDER = ["verify", "compute", "test", "analyze", "describe", "search", "sim", "brute", "small"]

def candidates_modes(src):
    ms = set(re.findall(r'==\s*"([A-Za-z_]+)"', src))
    return [m for m in MODE_ORDER if m in ms]

def run_exe(exe, inp, timeout=TIMEOUT):
    try:
        p = subprocess.run([exe], input=(inp + "\n").encode(),
                           capture_output=True, timeout=timeout)
    except subprocess.TimeoutExpired:
        return None, -1
    return p.stdout.decode("utf-8", "replace"), p.returncode

def process(pid):
    pdir = os.path.join(ROOT, pid)
    ddir = os.path.join(pdir, "data")
    os.makedirs(ddir, exist_ok=True)
    src_p = os.path.join(pdir, "code", "std.cpp")
    src = read(src_p)
    r = {"pid": pid, "added": 0, "reason": []}
    exe = os.path.join(WORK, f"{pid}.exe")
    c = subprocess.run([GPP, "-std=c++17", "-O2", src_p, "-o", exe],
                       capture_output=True, timeout=180)
    if c.returncode != 0:
        r["reason"].append("COMPILE_FAIL")
        return r
    existing = sorted(f[:-3] for f in os.listdir(ddir) if f.endswith(".in"))
    empty = len(existing) == 0
    # PE 探针基线
    pe_branch = bool(re.search(r'==\s*"PE"', src))
    pe_out = None
    if empty and pe_branch:
        out1, rc1 = run_exe(exe, "PE")
        out2, rc2 = run_exe(exe, "PE")
        if out1 is not None and rc1 == 0 and norm(out1) != "" and norm(out1) == norm(out2 or ""):
            pe_out = norm(out1)
            open(os.path.join(ddir, "01.in"), "w", newline="").write("PE\n")
            open(os.path.join(ddir, "01.out"), "w", newline="").write(pe_out + "\n")
            r["added"] += 1
            existing = ["01"]
        else:
            r["reason"].append("PE_PROBE_FAIL")
    elif existing:
        o = os.path.join(ddir, "01.out")
        if os.path.exists(o): pe_out = norm(read(o))
    seen = set()
    if pe_out is not None: seen.add(pe_out)
    # 候选
    is_mode = 'getline' in src and not re.search(r'(?:stringstream|istringstream)\s', src) \
              and not re.search(r'\bsto(?:ll|i)\b', src) and not re.search(r'cin\s*>>', src)
    if is_mode:
        cands = candidates_modes(src)
    else:
        cands = candidates_for(pid, src)
    kept = 0
    for inp in cands:
        if kept >= MAX_POINTS: break
        out1, rc1 = run_exe(exe, inp)
        if out1 is None or rc1 != 0:
            r["reason"].append(f"[{inp[:20]}]TLE_RC{rc1}"); continue
        out2, rc2 = run_exe(exe, inp)
        if out2 is None or norm(out1) != norm(out2):
            r["reason"].append(f"[{inp[:20]}]nondet"); continue
        o = norm(out1)
        if o == "" or o == "0":
            r["reason"].append(f"[{inp[:20]}]empty0"); continue
        if len(o) > MAX_OUT:
            r["reason"].append(f"[{inp[:20]}]toolarge"); continue
        if o in seen:
            continue
        seen.add(o)
        kept += 1
        idx = kept + len(existing)
        open(os.path.join(ddir, f"{idx:02d}.in"), "w", newline="").write(inp + "\n")
        open(os.path.join(ddir, f"{idx:02d}.out"), "w", newline="").write(o + "\n")
        r["added"] += 1
    if kept == 0 and not is_mode and not empty:
        r["reason"].append("no_valid_point")
    if kept == 0 and is_mode and empty:
        r["reason"].append("mode_all_fail")
    return r

def main():
    lo, hi = sys.argv[1], sys.argv[2]
    targets = []
    for d in sorted(os.listdir(ROOT)):
        if not re.fullmatch(r"\d{3}", d) or not (lo <= d <= hi): continue
        dd = os.path.join(ROOT, d, "data")
        n = len([f for f in os.listdir(dd) if f.endswith(".in")]) if os.path.isdir(dd) else 0
        if n == 0 or n == 1:
            targets.append(d)
    print(f"targets: {len(targets)}", flush=True)
    results = []
    with ThreadPoolExecutor(max_workers=8) as ex:
        for r in ex.map(process, targets):
            results.append(r)
    json.dump(results, open(os.path.join(WORK, "gen_report.json"), "w", encoding="utf-8"),
              ensure_ascii=False, indent=1)
    ok = [r for r in results if r["added"] >= 2]
    some = [r for r in results if 0 < r["added"] < 2]
    none = [r for r in results if r["added"] == 0]
    print(f"added>=2: {len(ok)}  added==1: {len(some)}  added==0: {len(none)}")
    for r in none[:40]:
        print(f"  NONE {r['pid']}: {r['reason'][:3]}")

if __name__ == "__main__":
    main()
