#!/usr/bin/env python3
"""Analyze P-positions for PE 665"""
import sys
sys.setrecursionlimit(10000)

def compute_p_positions(limit):
    is_p = {}
    p_positions = []
    for s in range(limit + 1):
        for a in range(s // 2 + 1):
            b = s - a
            if a > b: continue
            all_n = True
            # remove n from first pile
            for n in range(1, a + 1):
                na, nb = a - n, b
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]: all_n = False; break
            if not all_n: is_p[(a, b)] = False; continue
            # remove n from second pile
            for n in range(1, b + 1):
                na, nb = a, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]: all_n = False; break
            if not all_n: is_p[(a, b)] = False; continue
            # remove n from both
            for n in range(1, min(a, b) + 1):
                na, nb = a - n, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]: all_n = False; break
            if not all_n: is_p[(a, b)] = False; continue
            # remove n from first, 2n from second
            for n in range(1, min(a, b // 2) + 1):
                na, nb = a - n, b - 2*n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]: all_n = False; break
            if not all_n: is_p[(a, b)] = False; continue
            # remove 2n from first, n from second
            for n in range(1, min(a // 2, b) + 1):
                na, nb = a - 2*n, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]: all_n = False; break
            if not all_n: is_p[(a, b)] = False; continue
            is_p[(a, b)] = True
            p_positions.append((a, b, s))
    return p_positions

pp = compute_p_positions(200)
print('First 30 P-positions (excluding (0,0)):')
for i, (a, b, s) in enumerate(pp[1:31]):
    print(f'  {i+1}: ({a},{b}) sum={s}, a/b={a/b:.6f}, diff={b-a}')

print(f'\nf(100) = {sum(s for _,_,s in compute_p_positions(100))}')
print(f'f(200) = {sum(s for _,_,s in compute_p_positions(200))}')
print(f'f(300) = {sum(s for _,_,s in compute_p_positions(300))}')
print(f'f(400) = {sum(s for _,_,s in compute_p_positions(400))}')
print(f'f(500) = {sum(s for _,_,s in compute_p_positions(500))}')
print(f'f(1000) = {sum(s for _,_,s in compute_p_positions(1000))}')
