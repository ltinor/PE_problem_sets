#!/usr/bin/env python3
"""残留清理：把 std.cpp 注释/诊断路径、题面等处的旧 PE 值替换为官方答案。
每题替换后重编译+探针+数据回归验证，失败整体回滚。
旧值来源：git HEAD 中 data/01.out（01.in=="PE" 的探针输出）。
"""
import os, re, sys, json, subprocess
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
GPP = r"F:\tools\mingw64\bin\g++.exe"
WORK = os.path.join(HERE, "inv260")
INV = json.load(open(os.path.join(WORK, "inventory.json"), encoding="utf-8"))
TOKEN = lambda v: re.compile(r"(?<![\w.])" + re.escape(v) + r"(?![\w.])")

def read(p):
    return open(p, encoding="utf-8", errors="surrogateescape", newline="").read()

def write(p, s):
    open(p, "w", encoding="utf-8", errors="surrogateescape", newline="").write(s)

def norm(s):
    return "\n".join(l.rstrip() for l in s.replace("\r\n", "\n").split("\n") if l.strip())

def head_show(p):
    r = subprocess.run(["git", "show", f"HEAD:{p}"], capture_output=True)
    return r.stdout.decode("utf-8", "replace") if r.returncode == 0 else None

def one(r):
    pid, off = r["pid"], r["official"]
    pdir = os.path.join(ROOT, pid)
    old_in = head_show(f"{pid}/data/01.in") or ""
    old_out = head_show(f"{pid}/data/01.out") or ""
    if old_in.strip() != "PE" or not old_out.strip():
        return pid, "SKIP", "no PE probe data at HEAD"
    got = old_out.strip().split("\n")[-1].strip()
    if not got or got == off:
        return pid, "SKIP", "no old value"
    tok = TOKEN(got)
    # 1) 全目录 token 替换（跳过 data/ 与二进制）
    changed = []
    for root, dirs, files in os.walk(pdir):
        dirs[:] = [d for d in dirs if d != "data"]
        for fn in files:
            if fn.endswith((".exe", ".o")): continue
            fp = os.path.join(root, fn)
            try: t = read(fp)
            except OSError: continue
            t2 = tok.sub(off, t)
            if t2 != t:
                write(fp, t2)
                changed.append(fp)
    if not changed:
        return pid, "SKIP", "no residue"

    def rollback():
        for fp in changed:
            subprocess.run(["git", "checkout", "--", os.path.relpath(fp, ROOT)],
                           cwd=ROOT, capture_output=True)

    # 2) 编译 + 探针
    exe = os.path.join(WORK, f"res_{pid}.exe")
    c = subprocess.run([GPP, "-std=c++17", "-O2", os.path.join(pdir, "code", "std.cpp"),
                        "-o", exe], capture_output=True, timeout=180)
    if c.returncode != 0:
        rollback()
        return pid, "MANUAL", "compile fail: " + c.stderr.decode("utf-8", "replace")[-150:]
    try:
        p = subprocess.run([exe], input=b"PE\n", capture_output=True, timeout=60)
        lines = [l.strip() for l in p.stdout.decode("utf-8", "replace").split("\n") if l.strip()]
        new_got = lines[-1] if lines else ""
    except subprocess.TimeoutExpired:
        rollback(); return pid, "MANUAL", "probe TLE"
    if p.returncode != 0 or new_got != off:
        rollback(); return pid, "MANUAL", f"probe={new_got!r}"

    # 3) 数据回归（PE 探针 .out 应已为官方；横幅含旧值者同步）
    touched = []
    ddir = os.path.join(pdir, "data")
    regress = []
    if os.path.isdir(ddir):
        for fn in sorted(os.listdir(ddir)):
            if not fn.endswith(".in"): continue
            in_p = os.path.join(ddir, fn)
            out_p = in_p[:-3] + ".out"
            in_txt = read(in_p).strip()
            old_o = read(out_p) if os.path.exists(out_p) else None
            if in_txt == "PE":
                if norm(old_o or "") != off:
                    touched.append(out_p); write(out_p, off + "\n")
                continue
            try:
                rp = subprocess.run([exe], input=open(in_p, "rb").read(),
                                    capture_output=True, timeout=30)
            except subprocess.TimeoutExpired:
                regress.append(f"{fn}:TLE"); continue
            new_o = norm(rp.stdout.decode("utf-8", "replace"))
            if rp.returncode != 0:
                regress.append(f"{fn}:rc={rp.returncode}"); continue
            if old_o is not None and norm(old_o) == new_o:
                continue
            if old_o is not None and tok.search(norm(old_o)) and \
                    new_o == tok.sub(off, norm(old_o)):
                touched.append(out_p); write(out_p, new_o + "\n")
                continue
            regress.append(f"{fn}:WA new={new_o[:40]!r} old={norm(old_o)[:40]!r}")
    if regress:
        rollback()
        for fp in touched:
            subprocess.run(["git", "checkout", "--", os.path.relpath(fp, ROOT)],
                           cwd=ROOT, capture_output=True)
        return pid, "MANUAL", "regression " + "; ".join(regress[:3])
    return pid, "OK", f"replaced in {len(changed)} files, data_sync={len(touched)}"

def main():
    with ThreadPoolExecutor(max_workers=8) as ex:
        results = list(ex.map(one, INV))
    n = {"OK": 0, "SKIP": 0, "MANUAL": 0}
    for pid, st, detail in results:
        n[st] = n.get(st, 0) + 1
        if st == "MANUAL":
            print(f"  MANUAL {pid}: {detail[:150]}")
    print(f"OK={n['OK']} SKIP={n['SKIP']} MANUAL={n.get('MANUAL',0)}")

if __name__ == "__main__":
    main()
