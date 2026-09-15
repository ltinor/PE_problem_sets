#!/usr/bin/env python3
"""Verify corrected invariant-based P-position generation for PE 665"""
import sys
sys.setrecursionlimit(10000)

def generate_opt_corrected(limit):
    has_a = {0}
    has_b = {0}
    has_diff = {0}
    has_b2a = {0}
    has_2ba = {0}
    pp_list = [(0, 0, 0)]
    
    for s in range(1, limit + 1):
        for a in range(s // 2 + 1):
            b = s - a
            if a > b: continue
            
            is_n = False
            # Type 2: remove from second -> normalized a could be a or b-n
            if a in has_a or a in has_b: is_n = True
            # Type 1: remove from first -> normalized b becomes the a or b
            if not is_n and (b in has_a or b in has_b): is_n = True
            # Type 3: both piles
            if not is_n and (b - a) in has_diff: is_n = True
            # Type 4: (n, 2n)
            if not is_n and (b - 2*a) in has_b2a: is_n = True
            # Type 5: (2n, n)
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

for limit in [10, 100, 200, 1000]:
    opt = generate_opt_corrected(limit)
    bf = brute_force(limit)
    f_opt = sum(s for _,_,s in opt)
    f_bf = sum(s for _,_,s in bf)
    opt_set = set((a,b) for a,b,s in opt)
    bf_set = set((a,b) for a,b,s in bf)
    extra = opt_set - bf_set
    missing = bf_set - opt_set
    print(f"limit={limit}: f_opt={f_opt}, f_bf={f_bf}, match={f_opt==f_bf}")
    if extra:
        print(f"  Extra: {sorted(extra)[:5]}")
    if missing:
        print(f"  Missing: {sorted(missing)[:5]}")
