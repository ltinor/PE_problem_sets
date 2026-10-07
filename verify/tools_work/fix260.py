#!/usr/bin/env python3
"""修复 260 道 PE_DIFF 题：PE 分支值替换为官方答案，逐题编译+探针+数据回归验证。

策略：
  - 纯整数官方答案 + 整型常量定义 → 替换数字字面量（保留 LL 等后缀）
  - 其余（小数/科学计数法/十六进制/字符串答案）→ 定义改为 const char*（要求该变量仅 PE 分支单点使用）
  - PE 分支直接 cout 字符串字面量 → 替换字面量内容
  - 每题修完：重编译 → PE 探针必须等于官方 → 全部 data 回归（PE 探针 .out 同步重写；
    旧 .out 恰为旧 PE 值的视为 PE 点同步重写；其余不匹配即回滚）
  - 同步替换 statement.md 中的旧值 token
任何一步失败：整体回滚该题，记入 MANUAL 队列。
"""
import os, re, sys, json, subprocess
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
GPP = r"F:\tools\mingw64\bin\g++.exe"
WORK = os.path.join(HERE, "inv260")
INV = json.load(open(os.path.join(WORK, "inventory.json"), encoding="utf-8"))
BY_PID = {r["pid"]: r for r in INV}

INT_RE = re.compile(r"^-?\d+$")
TOKEN = lambda v: re.compile(r"(?<![\w.])" + re.escape(v) + r"(?![\w.])")

def read(p):
    return open(p, encoding="utf-8", errors="surrogateescape", newline="").read()

def write(p, s):
    open(p, "w", encoding="utf-8", errors="surrogateescape", newline="").write(s)

def norm(s):
    return "\n".join(l.rstrip() for l in s.replace("\r\n", "\n").split("\n") if l.strip())

def compile_exe(pid, exe):
    c = subprocess.run([GPP, "-std=c++17", "-O2", os.path.join(ROOT, pid, "code", "std.cpp"),
                        "-o", exe], capture_output=True, timeout=180)
    return c.returncode == 0, c.stderr.decode("utf-8", "replace")[-300:]

def probe(exe, timeout=60):
    p = subprocess.run([exe], input=b"PE\n", capture_output=True, timeout=timeout)
    lines = [l.strip() for l in p.stdout.decode("utf-8", "replace").replace("\r\n", "\n").split("\n") if l.strip()]
    return (lines[-1] if lines else ""), p.returncode

def run_in(exe, in_bytes, timeout=30):
    p = subprocess.run([exe], input=in_bytes, capture_output=True, timeout=timeout)
    return norm(p.stdout.decode("utf-8", "replace")), p.returncode

def fix_pid(pid):
    """返回 (status, detail)。status: FIXED / MANUAL / ALREADY"""
    r0 = BY_PID[pid]
    got, off = r0["got"], r0["official"]
    src_p = os.path.join(ROOT, pid, "code", "std.cpp")
    src = read(src_p)
    orig_src = src
    if got is None or off is None:
        return "MANUAL", "no got/official"
    is_int = bool(INT_RE.match(off))

    # ---- 定位 PE 分支（花括号配平）----
    m = re.search(r'if\s*\([^()]*"PE"[^()]*\)\s*\{', src)
    if not m:
        return "MANUAL", "PE branch not found"
    i = m.end() - 1  # 指向 '{'
    depth = 0
    for j in range(i, len(src)):
        if src[j] == "{": depth += 1
        elif src[j] == "}":
            depth -= 1
            if depth == 0: break
    branch = src[i:j]

    # ---- 分支内 cout 形态 ----
    strat = None
    lit_re = re.compile(r'cout\s*<<\s*"((?:[^"\\]|\\.)*)"')
    lits = list(lit_re.finditer(branch))
    MANIP = {"fixed", "scientific", "setprecision", "setw", "setfill", "left",
             "right", "internal", "showpoint", "noshowpoint", "endl", "flush"}
    cm = None
    for stm in re.finditer(r'cout((?:\s*<<\s*(?:[^;{]+)));', branch):
        for tok in re.findall(r'([A-Za-z_]\w*)', stm.group(1)):
            if tok not in MANIP:
                cm = tok
                break
        if cm: break
    if lits and any(got in g.group(1) for g in lits):
        strat = ("STRLIT", lits[0].group(1))
    elif cm:
        strat = ("VAR", cm)
    else:
        return "MANUAL", "no cout literal/var in branch"

    old_lit = None
    if strat[0] == "STRLIT":
        old_lit = strat[1]
        body = old_lit
        # 保留 \n 结尾结构
        ends_nl = body.endswith("\\n")
        core = body[:-2] if ends_nl else body
        if got not in core:
            return "MANUAL", f"strlit {core!r} != got {got!r}"
        new_core = core.replace(got, off)
        new_lit_body = new_core + ("\\n" if ends_nl else "")
        branch_new = branch[:lits[0].start(1)] + new_lit_body + branch[lits[0].end(1):]
        src = src[:i] + branch_new + src[j:]
    else:
        name = strat[1]
        # 找定义
        defs = list(re.finditer(
            rf'(?:const\s+|constexpr\s+)?([A-Za-z_][\w:]*)\s*\*?\s*{name}\s*=\s*([^;]+);', src))
        defs = [d for d in defs if not re.match(r'\s*\*', d.group(2))]
        if len(defs) != 1:
            return "MANUAL", f"def count={len(defs)} for {name}"
        d = defs[0]
        typ, val = d.group(1), d.group(2).strip()
        qm = re.fullmatch(r'"((?:[^"\\]|\\.)*)"', val)
        vm = re.fullmatch(r'"?(-?[0-9][0-9.eE+\-]*)"?(\w*)', val) if not qm else None
        is_float_typ = bool(re.search(r'double|float|\bld\b|long\s+double', typ))

        # 编辑列表 (start, end, replacement)，按位置倒序应用，避免索引漂移
        edits = []
        strv = None
        if qm:
            # 定义即字符串（char*/string）：替换内容
            edits.append((d.start(2), d.end(2), '"' + off + '"'))
        elif vm and is_int and not is_float_typ and typ != "string" \
                and "." not in val and "e" not in val.lower():
            # 整型常量 + 整数官方：字面量直替
            suf = vm.group(2) if vm.group(2) in ("LL", "ll", "ULL", "ull", "u", "UL", "L") else ""
            edits.append((d.start(2), d.end(2), off + suf))
        elif vm and is_int and typ == "string":
            edits.append((d.start(2), d.end(2), '"' + off + '"'))
        elif vm and is_int and is_float_typ:
            if abs(int(off)) <= 2 ** 53:
                # 浮点常量 + 整数官方（精度可表示）：分支输出取整 + 定义改值
                sm = re.search(rf'<<\s*{name}\b', branch)
                if not sm:
                    return "MANUAL", "float-int: branch print not found"
                edits.append((i + sm.start(), i + sm.end(), f"<< (long long)({name} + 0.5)"))
                edits.append((d.start(2), d.end(2), off))
            else:
                # 超 double 精度：整体换成整型定义，打印点直出精确整数
                edits.append((d.start(), d.end(), f"const long long {name} = {off}LL;"))
        else:
            # S2 双常量：新增 const char* 供所有 cout 打印点使用，数值定义同步改对
            if not vm:
                return "MANUAL", f"def value not literal: {val[:50]}"
            base = name + "_STR"
            k = 2
            while re.search(rf'\b{base}\b', src):
                base = f"{name}_STR{k}"; k += 1
            strv = base
            if not is_float_typ and typ != "string":
                # 整型定义保留原值（如 mantissa），只改打印点
                pass
            else:
                edits.append((d.start(2), d.end(2), off))
            # 找所有 cout 打印点行
            line_start = 0
            for ln in src.split("\n"):
                line_end = line_start + len(ln)
                if "cout" in ln and re.search(rf'<<\s*{name}\b', ln):
                    seg = ln
                    off_in_line = 0
                    for sm2 in re.finditer(rf'<<\s*{name}\b', ln):
                        edits.append((line_start + sm2.start(), line_start + sm2.end(),
                                      f"<< {strv}"))
                line_start = line_end + 1
            # 插入新常量定义
            def_line_end = src.find("\n", d.end())
            def_line_end = len(src) if def_line_end == -1 else def_line_end
            ins = f'\nconst char* {strv} = "{off}";'
            edits.append((def_line_end, def_line_end, ins))
        if not edits:
            return "MANUAL", "no edits produced"
        for s0, e0, rep in sorted(edits, key=lambda x: -x[0]):
            src = src[:s0] + rep + src[e0:]

    if src == orig_src:
        return "MANUAL", "no change produced"

    # ---- 落盘 std.cpp（编译前必须写回；后续失败则回滚）----
    write(src_p, src)
    touched = []  # [(path, old_content_or_None)] 供回滚

    # ---- 编译 + 探针验证 ----
    exe = os.path.join(WORK, f"fix_{pid}.exe")
    ok, err = compile_exe(pid, exe)
    if not ok:
        write(src_p, orig_src)
        return "MANUAL", f"compile fail after edit: {err[-120:]}"
    try:
        new_got, rc = probe(exe)
    except subprocess.TimeoutExpired:
        write(src_p, orig_src)
        return "MANUAL", "probe TLE after edit"
    if rc != 0 or new_got != off:
        write(src_p, orig_src)
        return "MANUAL", f"probe after edit = {new_got!r} != official"

    # ---- data 回归 + PE .out 同步 ----
    ddir = os.path.join(ROOT, pid, "data")
    data_updates, regress = [], []
    if os.path.isdir(ddir):
        for fn in sorted(os.listdir(ddir)):
            if not fn.endswith(".in"): continue
            in_p = os.path.join(ddir, fn)
            out_p = in_p[:-3] + ".out"
            in_txt = read(in_p).strip() if os.path.exists(in_p) else ""
            old_out = read(out_p) if os.path.exists(out_p) else None
            if in_txt == "PE":
                touched.append((out_p, old_out))
                write(out_p, off + "\n")
                data_updates.append(fn)
                continue
            try:
                out_got, rc2 = run_in(exe, open(in_p, "rb").read())
            except subprocess.TimeoutExpired:
                regress.append(f"{fn}:TLE"); continue
            if rc2 != 0:
                regress.append(f"{fn}:rc={rc2}"); continue
            if old_out is not None and norm(old_out) == out_got:
                continue
            # 不匹配：旧 .out 是否为旧 PE 值或横幅内嵌旧 PE 值 → 同步更新
            if old_out is not None and got and TOKEN(got).search(norm(old_out)) \
                    and out_got == TOKEN(got).sub(off, norm(old_out)):
                touched.append((out_p, old_out))
                write(out_p, out_got + "\n")
                data_updates.append(fn + "(pe-banner)")
                continue
            regress.append(f"{fn}:WA got={out_got[:40]!r} want={norm(old_out)[:40]!r}")
    if regress:
        write(src_p, orig_src)
        for p, old in touched:
            if old is None: os.remove(p)
            else: write(p, old)
        return "MANUAL", "regression " + "; ".join(regress[:3])

    # ---- statement.md 同步 ----
    stmt_changed = False
    sp = os.path.join(ROOT, pid, "statement.md")
    if os.path.exists(sp):
        st = read(sp)
        st2 = st
        if got and got != off:
            st2 = TOKEN(got).sub(off, st2)
        if old_lit and got != old_lit and got in old_lit:
            # 字面量含 got 已覆盖；再兜底换整个旧字面量（如 '12.3\\n' 形态不会出现于题面）
            pass
        if st2 != st:
            write(sp, st2)
            stmt_changed = True

    # ---- 全目录残留扫描 ----
    residue = []
    for root, _, files in os.walk(os.path.join(ROOT, pid)):
        for fn in files:
            fp = os.path.join(root, fn)
            if fn.endswith((".exe", ".o")): continue
            try: t = read(fp)
            except OSError: continue
            if got and got != off and TOKEN(got).search(t):
                residue.append(os.path.relpath(fp, ROOT))
    detail = f"off={off} data={data_updates or '-'} stmt={'Y' if stmt_changed else 'N'} residue={residue or '-'}"
    return "FIXED", detail

def main():
    pids = sys.argv[1:] if len(sys.argv) > 1 else [r["pid"] for r in INV]
    report = {}
    with ThreadPoolExecutor(max_workers=8) as ex:
        for pid, (status, detail) in zip(pids, ex.map(fix_pid, pids)):
            report[pid] = {"status": status, "detail": detail}
    json.dump(report, open(os.path.join(WORK, "fix_report.json"), "w", encoding="utf-8"),
              ensure_ascii=False, indent=1)
    n_fix = sum(1 for v in report.values() if v["status"] == "FIXED")
    n_man = sum(1 for v in report.values() if v["status"] == "MANUAL")
    print(f"processed={len(pids)} FIXED={n_fix} MANUAL={n_man}")
    for pid, v in report.items():
        if v["status"] != "FIXED":
            print(f"  MANUAL {pid}: {v['detail'][:140]}")

if __name__ == "__main__":
    main()
