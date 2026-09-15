#!/usr/bin/env python3
"""Check if (63,97) is P or N and find the correct rule"""
import sys
sys.setrecursionlimit(10000)

def get_p_positions(limit):
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
            p_list.append((a, b, s, b-a))
    return is_p, p_list

# Get P-positions up to 200
is_p, p_list = get_p_positions(200)

# Check (63,97)
print(f"(63,97): {'P' if is_p.get((63,97), False) else 'N'}")
print(f"Sum=160, diff=34")

# Find winning move from (63,97)
print("\nWinning moves from (63,97):")
for n in range(1, 64):
    key = (63-n, 97)
    if key in is_p and is_p[key]: print(f"  (63-{n}, 97) = ({63-n},97) P")
for n in range(1, 98):
    na, nb = 63, 97-n
    key = (na, nb) if na <= nb else (nb, na)
    if key in is_p and is_p[key]: print(f"  (63, 97-{n}) = {key} P")
for n in range(1, 64):
    na, nb = 63-n, 97-n
    key = (na, nb) if na <= nb else (nb, na)
    if key in is_p and is_p[key]: print(f"  both-{n}: {key} P")
for n in range(1, 64):
    na, nb = 63-n, 97-2*n
    if na >= 0 and nb >= 0:
        key = (na, nb) if na <= nb else (nb, na)
        if key in is_p and is_p[key]: print(f"  (n={n},2n): {key} P")
for n in range(1, 32):
    na, nb = 63-2*n, 97-n
    if na >= 0 and nb >= 0:
        key = (na, nb) if na <= nb else (nb, na)
        if key in is_p and is_p[key]: print(f"  (2n={2*n},n={n}): {key} P")

# Also list P-positions with diff = 34
print("\nP-positions with diff=34 up to sum 200:")
for a,b,s,d in p_list:
    if d == 34:
        print(f"  ({a},{b}) sum={s}")

# Show P-positions ordered by diff
print("\nP-positions by diff:")
by_diff = {}
for a,b,s,d in p_list[1:]:
    if d not in by_diff:
        by_diff[d] = []
    by_diff[d].append((a,b,s))
for d in sorted(by_diff)[:50]:
    positions = by_diff[d]
    for a,b,s in positions:
        print(f"  diff={d}: ({a},{b}) sum={s}")
