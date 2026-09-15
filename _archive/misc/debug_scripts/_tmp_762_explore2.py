#!/usr/bin/env python3
"""Explore PE 762: Amoebas in 2D grid - with no-overlap constraint"""
from functools import lru_cache

def produce(T_mask):
    """Given a bitmask T of rows to split, return the produced mask in next column.
    Valid only if no overlaps."""
    result = 0
    count = 0
    for r in range(4):
        if T_mask & (1 << r):
            count += 1
            b1 = 1 << r
            b2 = 1 << ((r + 1) % 4)
            if result & b1 or result & b2:
                return None  # overlap
            result |= b1 | b2
    return result

@lru_cache(None)
def count_configs(mask, splits_left):
    """Count distinct final configs from active mask with splits_left."""
    if splits_left == 0:
        return 1
    
    if mask == 0:
        return 1 if splits_left == 0 else 0
    
    total = 0
    # Enumerate subsets T of mask that produce valid non-overlapping results
    submask = mask
    T = submask
    while True:
        T = (T - 1) & submask  # iterate through subsets
        if T == 0:
            new_mask = produce(T)
            if new_mask is not None:
                splits = bin(T).count('1')
                if splits > 0 and splits <= splits_left:
                    total += count_configs(new_mask, splits_left - splits)
            break
        # For non-zero T
        new_mask = produce(T)
        if new_mask is not None:
            splits = bin(T).count('1')
            if splits <= splits_left:
                total += count_configs(new_mask, splits_left - splits)
        if T == submask:
            # Also handle T = 0 case: settle all
            pass
        if T == 0:
            break
    
    # T = submask case (all split)
    new_mask = produce(submask)
    if new_mask is not None:
        splits = bin(submask).count('1')
        if splits <= splits_left:
            total += count_configs(new_mask, splits_left - splits)
    
    return total

# Compute small C(N) with DP
from functools import lru_cache

@lru_cache(None)
def C(N, mask=1):
    if N == 0:
        return 1 if mask == 0 else (1 if mask != 0 else 1)
    # DP: f[mask][n] = number of configs
    pass

# Let me do this more carefully with explicit DP
def compute_C(N):
    """Compute C(N) using DP."""
    # dp[n][mask] = number of configs after n splits with current active mask
    # But we need to settle as we go. Let me think differently.
    pass

# Actually let me just do BFS/DFS over all reachable final states
def enumerate_states(N):
    """Enumerate all reachable position sets after N splits."""
    # State: frozenset of (x,y) positions
    from collections import deque
    
    initial = frozenset([(0, 0)])
    seen = {initial: 0}  # state -> min splits to reach
    final_states = set()
    
    q = deque([(initial, 0)])
    while q:
        state, splits = q.popleft()
        if splits == N:
            final_states.add(state)
            continue
        if splits > N:
            continue
        
        # Try splitting each amoeba
        for (x, y) in state:
            target1 = (x+1, y)
            target2 = (x+1, (y+1) % 4)
            if target1 not in state and target2 not in state:
                new_state = frozenset(
                    (s for s in state if s != (x, y)) | {target1, target2}
                )
                if new_state not in seen or seen[new_state] > splits + 1:
                    seen[new_state] = splits + 1
                    q.append((new_state, splits + 1))
    
    return len(final_states)

for N in range(11):
    c = enumerate_states(N)
    print(f"C({N}) = {c}")
