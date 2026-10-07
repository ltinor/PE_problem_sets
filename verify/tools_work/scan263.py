#!/usr/bin/env python3
"""263 旁路: 分段筛枚举 <= 1e9 的 engineer paradise, 验证 4 最大之和 = 2039506520。"""
import numpy as np

LIMIT = 10**9
BASE = 40000

def base_primes(limit):
    s = np.ones(limit + 1, dtype=bool); s[:2] = False
    for i in range(2, int(limit ** 0.5) + 1):
        if s[i]: s[i*i::i] = False
    return [i for i in range(2, limit + 1) if s[i]]

BP = base_primes(BASE)

def segment(lo, hi):
    size = hi - lo
    s = np.ones(size, dtype=bool)
    if lo <= 1: s[:2 - lo] = False
    for p in BP:
        start = max(p * p, ((lo + p - 1) // p) * p)
        if start < hi: s[start - lo::p] = False
    return s

def is_practical(n):
    if n == 1: return True
    if n % 2: return False
    m = n; a = 0
    while m % 2 == 0: m //= 2; a += 1
    sigma = (1 << (a + 1)) - 1
    d = 3
    while m > 1:
        if d * d > m:
            if d > sigma: return False
            sigma += d * sigma
            break
        if m % d == 0:
            c = 0
            while m % d == 0: m //= d; c += 1
            if d > sigma: return False
            sigma *= (d ** (c + 1) - 1) // (d - 1)
        d += 2
    return True

found = []
seg = 2 * 10 ** 8
for lo in range(2, LIMIT + 16, seg):
    hi = min(lo + seg, LIMIT + 16)
    s = segment(lo, hi)
    isp = lambda x: s[x - lo]
    for p in range(max(17, lo + ((17 - lo) % 2)), hi - 12, 2):
        if not isp(p) or not isp(p - 6) or not isp(p + 6) or not isp(p + 12): continue
        if isp(p - 4) or isp(p - 2) or isp(p + 2) or isp(p + 4) or isp(p + 8) or isp(p + 10): continue
        n = p + 3
        if (is_practical(n - 8) and is_practical(n - 4) and is_practical(n)
                and is_practical(n + 4) and is_practical(n + 8)):
            found.append(n)
    print(f"  scanned to {hi}: {len(found)} paradises", flush=True)

print("paradises <= 1e9:", found)
if len(found) >= 4:
    print("sum of 4 largest:", sum(found[-4:]), "(official 2039506520)")
