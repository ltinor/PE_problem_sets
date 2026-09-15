#!/usr/bin/env python3
"""Compare brute-force and mex-generated P-positions for PE 665"""
import sys
sys.setrecursionlimit(10000)

def brute_force(limit):
    is_p = {}
    p_positions = []
    for s in range(limit + 1):
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
            p_positions.append((a, b, s))
    return p_positions

def mex_generate(limit):
    p_set = {(0, 0)}
    seen = {0}
    mex_candidate = 1
    
    while True:
        a = mex_candidate
        while a in seen:
            a += 1
        
        if a > limit // 2 + 500:
            break
        
        b = a + 1
        found = False
        while a + b <= limit:
            if b in seen:
                b += 1
                continue
            
            is_p = True
            for n in range(1, a + 1):
                if (a - n, b) in p_set:
                    is_p = False; break
            if is_p:
                for n in range(1, b + 1):
                    nb = b - n
                    key = (a, nb) if a <= nb else (nb, a)
                    if key in p_set:
                        is_p = False; break
            if is_p:
                for n in range(1, min(a, b) + 1):
                    key = (a - n, b - n)
                    if key[0] > key[1]: key = (key[1], key[0])
                    if key in p_set:
                        is_p = False; break
            if is_p:
                for n in range(1, min(a, b // 2) + 1):
                    na, nb = a - n, b - 2*n
                    key = (na, nb) if na <= nb else (nb, na)
                    if key in p_set:
                        is_p = False; break
            if is_p:
                for n in range(1, min(a // 2, b) + 1):
                    na, nb = a - 2*n, b - n
                    key = (na, nb) if na <= nb else (nb, na)
                    if key in p_set:
                        is_p = False; break
            
            if is_p:
                p_set.add((a, b))
                seen.add(a)
                seen.add(b)
                mex_candidate = a + 1
                found = True
                break
            b += 1
        
        if not found:
            break
    
    return [(a, b, a+b) for (a, b) in sorted(p_set) if a > 0]

limit = 200
bf = set((a,b) for a,b,s in brute_force(limit) if a > 0)
mx = set((a,b) for a,b,s in mex_generate(limit) if a > 0)

print(f"Brute force: {len(bf)} P-positions")
print(f"Mex generate: {len(mx)} P-positions")
print(f"In BF but not MX: {len(bf - mx)}")
for a, b in sorted(bf - mx)[:20]:
    print(f"  ({a},{b}) sum={a+b}")
print(f"In MX but not BF: {len(mx - bf)}")
for a, b in sorted(mx - bf)[:10]:
    print(f"  ({a},{b}) sum={a+b}")
