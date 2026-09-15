#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10000)

def bf(limit):
    is_p = {}
    p_list = []
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
            p_list.append((a,b,s))
    return sum(s for _,_,s in p_list), p_list

f100, pp100 = bf(100)
print(f"BF: f(100) = {f100}")
print(f"P-positions up to sum 30:")
for a,b,s in pp100:
    if s <= 30:
        print(f"  ({a},{b}) s={s}")

f1000, _ = bf(1000)
print(f"BF: f(1000) = {f1000}")
