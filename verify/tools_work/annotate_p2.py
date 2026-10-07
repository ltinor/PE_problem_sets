#!/usr/bin/env python3
"""P2 标注: 为原 37 个无 data 题中已有 data 的题, 在题面"数据范围"节末尾追加缩小参数说明。"""
import os, re, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", "..", ".."))
P2 = "049 059 142 144 147 170 181 194 196 201 221 236 240 250 257 263 288 289 298 316 322 326 327 336 348 365 412 706 708 709 710 941 943 949 950 952 966".split()
NOTE = "- 注：本题 data 由 std 实跑生成；原题全规模参数下 std 会超时，测试点采用可在时限内完成的缩小规模参数。"

done = skip_have = skip_nodata = 0
for pid in P2:
    ddir = os.path.join(ROOT, pid, "data")
    n = len([f for f in os.listdir(ddir) if f.endswith(".in")]) if os.path.isdir(ddir) else 0
    if n == 0:
        skip_nodata += 1
        continue
    sp = os.path.join(ROOT, pid, "statement.md")
    txt = open(sp, encoding="utf-8", newline="").read()
    if "缩小规模参数" in txt:
        skip_have += 1
        continue
    m = re.search(r"(##+\s*数据范围\s*\n)(.*?)(?=\n## |\Z)", txt, re.S)
    if not m:
        print(f"  {pid}: NO 数据范围 section")
        continue
    body = m.group(2)
    eol = "\r\n" if "\r\n" in txt else "\n"
    new_body = body.rstrip("\n") + eol + eol + NOTE + eol
    txt2 = txt[:m.start(2)] + new_body + txt[m.end(2):]
    open(sp, "w", encoding="utf-8", newline="").write(txt2)
    done += 1
print(f"annotated={done} already={skip_have} no_data={skip_nodata}")
