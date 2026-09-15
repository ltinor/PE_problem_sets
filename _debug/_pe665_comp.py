#!/usr/bin/env python3
"""Compare invariant-based P-position generation with brute force"""
import sys
sys.setrecursionlimit(10000)

def generate_opt(limit):
    has_b = {0}
    has_a = {0}
    has_diff = {0}
    has_b2a = {0}
    has_2ba = {0}
    pp_list = [(0, 0, 0)]
    
    for s in range(1, limit + 1):
        for a in range(s // 2 + 1):
            b = s - a
            if a > b: continue
            
            is_n = False
            if a in has_a: is_n = True
            if not is_n and b in has_b: is_n = True
            if not is_n and (b - a) in has_diff: is_n = True
            if not is_n and (b - 2*a) in has_b2a: is_n = True
            if not is_n and (2*b - a) in has_2ba: is_n = True
            
            if not is_n:
                pp_list.append((a, b, s))
                has_a.add(a)
                has_b.add(b)
                has_diff.add(b-a)
                has_b2a.add(b-2*a)
                has_2ba.add(2*b-a)
    
    return pp_list

def brute_force(limit):
    is_p = {}
    p_list = [(0,0,0)]
    for s in range(1, limit + 1):
        for a in range(s // 2 + 1):
            b = s - a
            if a > b: continue
            all_n = True
            for n in range(1, a + 1):
                na, nb = a - n, b
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]: all_n = False; break
            if not all_n: is_p[(a, b)] = False; continue
            for n in range(1, b + 1):
                na, nb = a, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]: all_n = False; break
            if not all_n: is_p[(a, b)] = False; continue
            for n in range(1, min(a, b) + 1):
                na, nb = a - n, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]: all_n = False; break
            if not all_n: is_p[(a, b)] = False; continue
            for n in range(1, min(a, b // 2) + 1):
                na, nb = a - n, b - 2*n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]: all_n = False; break
            if not all_n: is_p[(a, b)] = False; continue
            for n in range(1, min(a // 2, b) + 1):
                na, nb = a - 2*n, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]: all_n = False; break
            if not all_n: is_p[(a, b)] = False; continue
            is_p[(a, b)] = True
            p_list.append((a,b,s))
    return p_list

limit = 100
opt = set((a,b) for a,b,s in generate_opt(limit))
bf = set((a,b) for a,b,s in brute_force(limit))

extra = opt - bf
missing = bf - opt

print(f"Optimizer: {len(opt)} P-positions")
print(f"Brute force: {len(bf)} P-positions")
print(f"\nExtra P-positions (opt says P, BF says N):")
for a,b in sorted(extra)[:20]:
    s = a + b
    print(f"  ({a},{b}) sum={s}")
print(f"\nMissing P-positions (BF says P, opt says N):")
for a,b in sorted(missing)[:20]:
    s = a + b
    print(f"  ({a},{b}) sum={s}")
