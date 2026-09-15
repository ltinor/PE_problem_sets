#!/usr/bin/env python3
"""Verify (47,51) status and find winning move"""
import sys
sys.setrecursionlimit(10000)

def get_p_positions(limit):
    is_p = {}
    p_positions = {}
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
            p_positions[(a,b)] = s
    return is_p, p_positions

# Get P-positions up to 200
is_p_status, pp = get_p_positions(200)

# Check (47,51)
print("Status of (47,51):", "P" if is_p_status.get((47,51), False) else "N")

# Find all P-positions reachable from (47,51)
a, b = 47, 51
print("\nAll P-positions reachable from (47,51):")
for n in range(1, a + 1):
    na, nb = a - n, b
    if na > nb: na, nb = nb, na
    if (na, nb) in pp:
        print(f"  remove {n} from first: ({na},{nb}) sum={pp[(na,nb)]}")
for n in range(1, b + 1):
    na, nb = a, b - n
    if na > nb: na, nb = nb, na
    if (na, nb) in pp:
        print(f"  remove {n} from second: ({na},{nb}) sum={pp[(na,nb)]}")
for n in range(1, min(a, b) + 1):
    na, nb = a - n, b - n
    if na > nb: na, nb = nb, na
    if (na, nb) in pp:
        print(f"  remove {n} from both: ({na},{nb}) sum={pp[(na,nb)]}")
for n in range(1, min(a, b // 2) + 1):
    na, nb = a - n, b - 2*n
    if na > nb: na, nb = nb, na
    if (na, nb) in pp:
        print(f"  remove (n,2n): ({na},{nb}) sum={pp[(na,nb)]}")
for n in range(1, min(a // 2, b) + 1):
    na, nb = a - 2*n, b - n
    if na > nb: na, nb = nb, na
    if (na, nb) in pp:
        print(f"  remove (2n,n): ({na},{nb}) sum={pp[(na,nb)]}")

# Print all P-positions with sum < 100
print("\nAll P-positions with sum < 100:")
for (a,b), s in sorted(pp.items(), key=lambda x: x[1]):
    if s < 100:
        print(f"  ({a},{b}) sum={s}")
