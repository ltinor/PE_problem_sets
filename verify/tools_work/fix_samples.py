#!/usr/bin/env python3
"""批量重写题面样例输出块为 std 实跑结果 (仓库约定 std 为权威)。
守卫: std 不稳定/崩溃/空输出跳过; 新输出是横幅而旧样例不是 -> 跳过待手工。
"""
import os, re, json, subprocess
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
GPP = r"F:\tools\mingw64\bin\g++.exe"

def strict_norm(s):
    lines = [l.rstrip() for l in s.replace("\r\n", "\n").split("\n")]
    while lines and lines[-1] == "": lines.pop()
    return "\n".join(lines)

def locate_out_blocks(lines):
    """返回样例节内各 ### 输出 围栏内容的 (start,end) 行号列表 (end 为闭合围栏行号)。"""
    blocks, kind, fence, buf_start = [], None, False, None
    in_sample = False
    for idx, raw in enumerate(lines):
        s = raw.strip()
        if re.match(r"^##+\s*样例", s): in_sample = True; continue
        if in_sample and re.match(r"^## ", s): in_sample = False
        if not in_sample: continue
        if s.startswith("###") and not fence:
            kind = "out" if "输出" in s else None
            fence = False
        elif s == "```":
            if fence:
                if kind == "out": blocks.append((buf_start, idx))
                kind, fence = None, False
            else:
                fence = True; buf_start = idx + 1
    return blocks

def process(pid):
    sp = os.path.join(ROOT, pid, "statement.md")
    text = open(sp, encoding="utf-8", newline="").read()
    eol = "\r\n" if "\r\n" in text else "\n"
    lines = text.split("\n")
    blocks = locate_out_blocks(lines)
    if not blocks:
        return pid, "no_out_blocks", 0
    # 样例输入块: 同法取 in 围栏内容
    ins, kind, fence, buf_start = [], None, False, None
    in_sample = False
    for idx, raw in enumerate(lines):
        s = raw.strip()
        if re.match(r"^##+\s*样例", s): in_sample = True; continue
        if in_sample and re.match(r"^## ", s): in_sample = False
        if not in_sample: continue
        if s.startswith("###") and not fence:
            kind = "in" if "输入" in s else None
            fence = False
        elif s == "```":
            if fence:
                if kind == "in": ins.append((buf_start, idx))
                kind, fence = None, False
            else:
                fence = True; buf_start = idx + 1
    exe = os.path.join(HERE, "sfix", f"{pid}.exe")
    if not os.path.exists(exe):
        c = subprocess.run([GPP, "-std=c++17", "-O2", os.path.join(ROOT, pid, "code", "std.cpp"),
                            "-o", exe], capture_output=True, timeout=180)
        if c.returncode != 0:
            return pid, "compile_fail", 0
    rewritten, skipped = 0, []
    for bi, (st, en) in enumerate(blocks):
        if bi >= len(ins): break
        ist, ie = ins[bi]
        sample_in = "\n".join(l.strip("\r") for l in lines[ist:ie]).strip("\n")
        try:
            p1 = subprocess.run([exe], input=(sample_in + "\n").encode(), capture_output=True, timeout=10)
            p2 = subprocess.run([exe], input=(sample_in + "\n").encode(), capture_output=True, timeout=10)
        except subprocess.TimeoutExpired:
            skipped.append(f"S{bi+1}TLE"); continue
        if p1.returncode != 0 or p2.returncode != 0:
            skipped.append(f"S{bi+1}rc"); continue
        o1 = strict_norm(p1.stdout.decode("utf-8", "replace"))
        o2 = strict_norm(p2.stdout.decode("utf-8", "replace"))
        if not o1 or o1 != o2:
            skipped.append(f"S{bi+1}unstable"); continue
        old = strict_norm("\n".join(l.strip("\r") for l in lines[st:en]))
        if o1 == old:
            continue
        # 横幅守卫
        if re.match(r"^PE \d{3}:", o1) and not re.match(r"^PE \d{3}:", old):
            skipped.append(f"S{bi+1}banner"); continue
        cr = "\r" if (lines[st].endswith("\r") or eol == "\r\n") else ""
        new_lines = [l + cr for l in o1.split("\n")]
        lines[st:en] = new_lines
        rewritten += 1
        # 行号位移后重定位剩余块
        delta = len(new_lines) - (en - st)
        blocks = [(a + delta if a > st else a, b + delta if b > st else b) for a, b in blocks]
        ins = [(a + delta if a > st else a, b + delta if b > st else b) for a, b in ins]
    if rewritten:
        open(sp, "w", encoding="utf-8", newline="").write("\n".join(lines))
    return pid, ("ok" if rewritten else "clean"), skipped

def main():
    res = json.load(open(os.path.join(ROOT, "_tools", "audit", "statement_audit.json"), encoding="utf-8"))
    pids = sorted({r["id"] for r in res if any(i.startswith("SAMPLE") and "WRONG" in i for i in r["issues"])})
    print(f"rewriting samples for {len(pids)} problems", flush=True)
    out = []
    with ThreadPoolExecutor(max_workers=6) as ex:
        out = list(ex.map(process, pids))
    from collections import Counter
    print(Counter(s for _, s, _ in out))
    for pid, s, sk in out:
        if s != "ok" or sk:
            print(f"  {pid}: {s} {sk[:3]}")

if __name__ == "__main__":
    main()
