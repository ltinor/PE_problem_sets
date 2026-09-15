#!/usr/bin/env python3
"""Debug: check specific position (3,9)"""
import sys
sys.setrecursionlimit(10000)

def check_position(target_a, target_b, limit):
    """Brute force and check specific position"""
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
    
    print(f"Status of ({target_a},{target_b}): {'P' if is_p.get((target_a,target_b), False) else 'N'}")
    
    # List P-positions with smaller sum
    print(f"\nP-positions with sum < {target_a+target_b}:")
    for a,b,s in p_list:
        if s < target_a + target_b:
            print(f"  ({a},{b}) sum={s}")
    
    # Find all moves from (target_a, target_b) to P-positions
    print(f"\nMoves from ({target_a},{target_b}) to P-positions:")
    for n in range(1, target_a + 1):
        na, nb = target_a - n, target_b
        if na > nb: na, nb = nb, na
        if (na, nb) in is_p and is_p[(na, nb)]:
            print(f"  type1(n={n}): ({na},{nb})")
    for n in range(1, target_b + 1):
        na, nb = target_a, target_b - n
        if na > nb: na, nb = nb, na
        if (na, nb) in is_p and is_p[(na, nb)]:
            print(f"  type2(n={n}): ({na},{nb})")
    for n in range(1, min(target_a, target_b) + 1):
        na, nb = target_a - n, target_b - n
        if na > nb: na, nb = nb, na
        if (na, nb) in is_p and is_p[(na, nb)]:
            print(f"  type3(n={n}): ({na},{nb})")
    for n in range(1, min(target_a, target_b // 2) + 1):
        na, nb = target_a - n, target_b - 2*n
        if na > nb: na, nb = nb, na
        if (na, nb) in is_p and is_p[(na, nb)]:
            print(f"  type4(n={n}): ({na},{nb})")
    for n in range(1, min(target_a // 2, target_b) + 1):
        na, nb = target_a - 2*n, target_b - n
        if na > nb: na, nb = nb, na
        if (na, nb) in is_p and is_p[(na, nb)]:
            print(f"  type5(n={n}): ({na},{nb})")

check_position(3, 9, 100)
print("\n" + "="*50)
check_position(7, 10, 100)
