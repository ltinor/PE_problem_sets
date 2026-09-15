#!/usr/bin/env python3
"""Debug: check specific P-positions"""
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

bf = brute_force(200)
# Find P-positions with a=47, etc.
for a_check in [47, 51, 52, 53, 56, 57, 58, 61, 62, 63, 64, 66, 71, 72, 73, 74]:
    for a,b,s in bf:
        if a == a_check:
            print(f"  ({a},{b}) sum={s}")
            break
    else:
        # Check if b matches
        for a2,b2,s2 in bf:
            if b2 == a_check:
                print(f"  ({a2},{a_check}) sum={s2} (as b-value)")
                break
        else:
            print(f"  a={a_check}: no P-position found")

# Show all P-positions by a-value
print("\nAll P-positions by a-value:")
by_a = {}
for a,b,s in bf:
    if a > 0:
        by_a[a] = (b, s)
for a in sorted(by_a)[:60]:
    b, s = by_a[a]
    print(f"  a={a}: b={b}, sum={s}, diff={b-a}")
