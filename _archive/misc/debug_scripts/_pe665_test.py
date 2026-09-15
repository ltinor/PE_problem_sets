#!/usr/bin/env python3
"""Find P-positions for PE 665 (Proportionate Nim)"""
import sys
sys.setrecursionlimit(10000)

def compute_p_positions(limit):
    """Compute losing positions up to sum limit using DP"""
    is_p = {}
    p_positions = []
    
    for s in range(limit + 1):
        for a in range(s // 2 + 1):
            b = s - a
            if a > b:
                continue
            
            # Check all moves
            all_n = True
            # remove n from first pile
            for n in range(1, a + 1):
                na, nb = a - n, b
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]:
                    all_n = False; break
            if not all_n: 
                is_p[(a, b)] = False; continue
                
            # remove n from second pile
            for n in range(1, b + 1):
                na, nb = a, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]:
                    all_n = False; break
            if not all_n: 
                is_p[(a, b)] = False; continue
                
            # remove n from both
            for n in range(1, min(a, b) + 1):
                na, nb = a - n, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]:
                    all_n = False; break
            if not all_n: 
                is_p[(a, b)] = False; continue
                
            # remove n from first, 2n from second
            for n in range(1, min(a, b // 2) + 1):
                na, nb = a - n, b - 2*n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]:
                    all_n = False; break
            if not all_n: 
                is_p[(a, b)] = False; continue
                
            # remove 2n from first, n from second
            for n in range(1, min(a // 2, b) + 1):
                na, nb = a - 2*n, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in is_p and is_p[(na, nb)]:
                    all_n = False; break
            if not all_n: 
                is_p[(a, b)] = False; continue
            
            is_p[(a, b)] = True
            p_positions.append((a, b, s))
    
    return p_positions

# Test
print("f(10):")
pp = compute_p_positions(10)
for a, b, s in pp:
    print(f"  ({a},{b}) sum={s}")
print(f"f(10) = {sum(s for _,_,s in pp)}")

print("\nf(20):")
pp = compute_p_positions(20)
for a, b, s in pp:
    if s <= 20:
        print(f"  ({a},{b}) sum={s}")
print(f"f(20) = {sum(s for _,_,s in pp)}")

print("\nf(100) = ", sum(s for _,_,s in compute_p_positions(100)))
