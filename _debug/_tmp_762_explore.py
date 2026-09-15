#!/usr/bin/env python3
"""Explore PE 762: Amoebas in 2D grid"""
from functools import lru_cache

MOD = 10**9

@lru_cache(None)
def count_configs(state, remaining_splits):
    """Count configs starting from 'state' (4-tuple of active counts), 
    with exactly 'remaining_splits' splits left."""
    a, b, c, d = state
    total = sum(state)
    
    if remaining_splits == 0:
        return 1  # settle all remaining
    
    if total == 0:
        return 1 if remaining_splits == 0 else 0
    
    # We can split s0,s1,s2,s3 amoebas
    result = 0
    for s0 in range(a + 1):
        for s1 in range(b + 1):
            for s2 in range(c + 1):
                for s3 in range(d + 1):
                    splits = s0 + s1 + s2 + s3
                    if splits > remaining_splits:
                        continue
                    if splits == 0 and total > 0:
                        continue
                    new_state = (
                        s0 + s3,
                        s0 + s1,
                        s1 + s2,
                        s2 + s3
                    )
                    result += count_configs(new_state, remaining_splits - splits)
    return result

# Compute small C(N)
for N in range(11):
    c = count_configs((1, 0, 0, 0), N)
    print(f"C({N}) = {c}")
