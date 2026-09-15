#!/usr/bin/env python3
"""Generate P-positions for PE 665 up to higher limit to see pattern"""
import sys
sys.setrecursionlimit(10000)

def generate_pp(limit):
    """Generate P-positions using optimized approach with invariant hashing"""
    # For each type of move, maintain: invariant -> min_a that has this invariant
    # Move types:
    # 1: b fixed → hash by b
    # 2: a fixed → hash by a
    # 3: b-a fixed → hash by diff
    # 4: b-2a fixed → hash by b-2a
    # 5: 2b-a fixed → hash by 2b-a
    
    # We just need to know if ANY P-position exists with a given invariant
    # (since we process in sum order, any P-position is reachable)
    has_b = set()      # b-values of P-positions
    has_a = set()      # a-values
    has_diff = set()   # b-a values
    has_b2a = set()    # b-2a values
    has_2ba = set()    # 2b-a values
    
    pp_list = [(0, 0, 0, 0)]
    has_a.add(0)
    has_b.add(0)
    has_diff.add(0)
    has_b2a.add(0)
    has_2ba.add(0)
    
    for s in range(1, limit + 1):
        # Only check first time each a is considered
        # Optimization: for each s, enumerate a from 0 to s/2
        for a in range(s // 2 + 1):
            b = s - a
            if a > b: continue
            
            # Check if any move from (a,b) leads to P-position
            is_n = False
            
            # Move type 2: (a, b-n) → check if a is an a-value of a P-position
            if a in has_a:
                is_n = True
            
            # Move type 1: (a-n, b) → check if b is a b-value
            if not is_n and b in has_b:
                is_n = True
            
            # Move type 3: both piles → check if diff (b-a) has been seen
            if not is_n and (b - a) in has_diff:
                is_n = True
            
            # Move type 4: (n, 2n) → check b-2a
            if not is_n and (b - 2*a) in has_b2a:
                is_n = True
            
            # Move type 5: (2n, n) → check 2b-a
            if not is_n and (2*b - a) in has_2ba:
                is_n = True
            
            if not is_n:
                # P-position found
                pp_list.append((a, b, s, b-a))
                has_a.add(a)
                has_b.add(b)
                has_diff.add(b-a)
                has_b2a.add(b-2*a)
                has_2ba.add(2*b-a)
    
    return pp_list

pp_list = generate_pp(5000)
print(f"Generated {len(pp_list)} P-positions up to sum 5000")
print(f"f(10) = {sum(s for _,_,s,_ in pp_list if s <= 10)}")
print(f"f(100) = {sum(s for _,_,s,_ in pp_list if s <= 100)}")
print(f"f(1000) = {sum(s for _,_,s,_ in pp_list if s <= 1000)}")

# Analyze diffs
print("\nDiff analysis:")
diffs = [d for _,_,_,d in pp_list[1:]]
print(f"First 100 diffs: {diffs[:100]}")

# Find missing diffs in first 200
used = set(diffs)
missing = sorted(set(range(200)) - used)
print(f"Missing diffs (first 50): {missing[:50]}")
print(f"Max diff: {max(diffs)}")

# Count gaps
print("\nConsecutive used diffs:")
consec = []
start = 1
while start in used:
    consec.append(start)
    start += 1
print(f"1 through {len(consec)} are all used")
