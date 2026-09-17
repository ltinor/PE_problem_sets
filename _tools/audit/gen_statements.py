#!/usr/bin/env python3
"""为空骨架 statement.md 批量生成题面:
- 从 P/P.md (或 source/_posts/P.md) 提取 PE 原题中文描述与标题
- data/01.in+01.out 存在时附真实样例
- 顶部加"待人工校对"标注; 不触碰已有内容的题面
"""
import os
import re
import sys
from math import gcd

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

def content_lines(text):
    n = 0
    for l in text.split('\n'):
        s = l.strip()
        if not s or s.startswith('#') or s == '---' or s.startswith('```'): continue
        n += 1
    return n

def parse_original(pid):
    """返回 (英文标题, 中文标题, 中文题面, 英文题面, 官方链接)"""
    src = None
    for cand in (os.path.join(REPO, pid, f'{pid}.md'),
                 os.path.join(REPO, 'source', '_posts', f'{int(pid):d}.md'),
                 os.path.join(REPO, 'source', '_posts', f'{pid}.md')):
        if os.path.exists(cand): src = cand; break
    if not src: return None, None, None, None, None
    text = open(src, encoding='utf-8', errors='replace').read()
    text = re.sub(r'^---\s*$', '', text.split('---\n', 2)[-1] if text.startswith('title:') else text, flags=re.M) if text.startswith('title:') else text
    # 去掉 frontmatter
    m = re.match(r'---\n.*?\n---\n', text, re.S)
    if m: text = text[m.end():]
    link_m = re.search(r'\[Problem \d+\]\((https?://[^)]+)\)', text)
    link = link_m.group(1) if link_m else f'https://projecteuler.net/problem={int(pid)}'
    text = re.sub(r'^\*\*\*$', '', text, flags=re.M)
    text = re.sub(r'^# \[Problem \d+\].*$', '', text, flags=re.M).strip()
    # 找独立的粗体标题行 (**XXX**)
    bolds = [m for m in re.finditer(r'^\*\*([^*]+)\*\*\s*$', text, re.M)]
    if not bolds: return None, None, None, text.strip(), link
    en_title = bolds[0].group(1).strip()
    cn_title = None; cn_body = None; en_body = text.strip()
    if len(bolds) >= 2:
        cn_title = bolds[-1].group(1).strip()
        start = bolds[-1].end()
        cn_body = text[start:].strip()
        en_body = text[:bolds[1].start()].strip()
    return en_title, cn_title, cn_body, en_body, link

def has_data_sample(pid):
    i = os.path.join(REPO, pid, 'data', '01.in')
    o = os.path.join(REPO, pid, 'data', '01.out')
    if os.path.exists(i) and os.path.exists(o):
        return open(i, encoding='utf-8', errors='replace').read().strip()[:500], \
               open(o, encoding='utf-8', errors='replace').read().strip()[:500]
    return None, None

def gen(pid):
    sp = os.path.join(REPO, pid, 'statement.md')
    if os.path.exists(sp) and content_lines(open(sp, encoding='utf-8', errors='replace').read()) > 1:
        return 'SKIP_HAS_CONTENT'
    en_t, cn_t, cn_body, en_body, link = parse_original(pid)
    title = cn_t or en_t or f'Problem {int(pid)}'
    desc = cn_body or en_body or '（原题描述缺失）'
    desc = re.sub(r'\n{3,}', '\n\n', desc)
    sin, sout = has_data_sample(pid)
    parts = [f'# {title}（PE {int(pid)}）', '',
             '> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。',
             '> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；',
             '> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。', '']
    parts += ['## 原题描述', '']
    parts += [f'原题及更多讨论见 [{link}]({link})。', '']
    parts += desc.split('\n')
    parts += ['', '---', '', '## 输入格式', '', '（待人工补充：请对照 code/std.cpp 的读取约定描述。）', '',
              '## 输出格式', '', '（待人工补充。）', '']
    parts += ['## 样例', '']
    if sin is not None:
        parts += ['### 输入', '', '```', sin, '```', '', '### 输出', '', '```', sout, '```', '']
    else:
        parts += ['（无 data 数据，待人工补充。）', '']
    parts += ['---', '', '## 数据范围', '', '（待人工补充；原题参数范围见上方原题描述。）', '']
    open(sp, 'w', encoding='utf-8', newline='\n').write('\n'.join(parts) + '\n')
    return 'GENERATED'

def main():
    lo = int(sys.argv[1]) if len(sys.argv) > 1 else 1
    hi = int(sys.argv[2]) if len(sys.argv) > 2 else 968
    stats = {}
    for i in range(lo, hi + 1):
        r = gen(f'{i:03d}')
        stats[r] = stats.get(r, 0) + 1
    print(stats)

if __name__ == '__main__':
    main()
