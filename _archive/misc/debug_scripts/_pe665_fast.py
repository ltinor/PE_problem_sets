#!/usr/bin/env python3
"""Efficient P-position generation for PE 665 using mex approach"""
import sys
sys.setrecursionlimit(10000)

def generate_p_positions(limit_sum):
    """Generate P-positions with sum <= limit_sum using mex method.
    
    Key insight: Let a_k = mex of all previous a_i, b_i.
    Then b_k = a_k + d_k where d_k is also determined by a mex-like rule.
    
    Actually, we can generate using: a_k = mex of all previous values,
    then check increasing b > a until (a,b) is a P-position.
    Since only one P-position exists for each a (when b-a is correct),
    we can find b efficiently.
    """
    seen = set()  # all a_i and b_i seen
    seen.add(0)
    
    positions = [(0, 0)]  # (a, b) P-positions
    used_diffs = set()
    
    mex = 1  # current mex candidate
    max_sum = 0
    
    # We'll generate by mex of a-values
    while True:
        # Find next a = mex of seen
        a = mex
        while a in seen:
            a += 1
        mex = a + 1
        
        # Find b > a such that (a,b) is a P-position
        # b must be: such that no move from (a,b) leads to a P-position
        # This means: (a-n,b) not P for n≤a, (a,b-n) not P for n≤b,
        # (a-n,b-n) not P, (a-n,b-2n) not P, (a-2n,b-n) not P.
        
        # For a given a, we can try b values
        b = a + 1
        while True:
            s = a + b
            if s > limit_sum:
                return positions
            
            # Quick check: b must not be in seen (else it's a previous a or b value)
            if b in seen:
                b += 1
                continue
            
            # Check if (a,b) is P-position
            is_p = True
            
            # Check remove n from first: (a-n, b) should not be P
            # Since only P-positions we know have a' < a (or a' = a, b' < b for previous ones),
            # we need to check if (a-n, b) is a known P-position
            # But b could match a previous b value... let's just check against known positions
            
            # This requires checking against all known P-positions
            # For efficiency, we can use a set of (a,b) pairs
            # But let's do it more cleverly
            
            # Actually, let me use a hash set of (a,b) for P-positions
            break  # placeholder
            
        break
    
    return positions

# Let me try a different approach: generate using a simpler mex rule
def generate_fast(limit):
    """Generate P-positions using the known mex rule.
    
    From analysis: the game is equivalent to Wythoff-style with 
    two interleaved sequences. The a-values follow mex of all previous a,b.
    
    Actually, let me use the mex-of-differences approach.
    """
    # We'll maintain: a-values (mex of all a,b), and two difference sequences
    a_vals = [0]
    b_vals = [0]
    seen = {0}
    
    # The b-a differences
    # It appears that d = b-a follows a specific pattern.
    # Let me compute by generating mex of a-values and checking b.
    
    p_set = {(0, 0)}
    mex_candidate = 1
    total = 0
    
    while True:
        a = mex_candidate
        while a in seen:
            a += 1
        
        # Find the b for this a
        # b must be > a, not in seen, and (a,b) must be P-position
        b = a + 1
        found = False
        while a + b <= limit:
            if b in seen:
                b += 1
                continue
            
            # Check if any move from (a,b) leads to a P-position
            is_p = True
            # Check moves: (a-n, b), (a, b-n), (a-n, b-n), (a-n, b-2n), (a-2n, b-n)
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
                a_vals.append(a)
                b_vals.append(b)
                total += a + b
                mex_candidate = a + 1
                found = True
                break
            b += 1
        
        if not found:
            # No more P-positions within limit
            break
    
    return a_vals[1:], b_vals[1:], total

# Test
a_vals, b_vals, total = generate_fast(200)
print("P-positions (a,b,sum):")
for i in range(min(30, len(a_vals))):
    print(f"  {i+1}: ({a_vals[i]},{b_vals[i]}) sum={a_vals[i]+b_vals[i]}, diff={b_vals[i]-a_vals[i]}")

print(f"\nf(200) = {total}")

# f(1000)
a_vals, b_vals, total = generate_fast(1000)
print(f"f(1000) = {total} (expected 117002)")
