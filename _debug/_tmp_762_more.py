#!/usr/bin/env python3
"""Compute C(N) for PE 762 up to N=20 efficiently"""
from collections import deque

def compute_C(N):
    initial = frozenset([(0, 0)])
    seen_states = {initial: 0}
    final_count = 0
    
    q = deque([(initial, 0)])
    while q:
        state, splits = q.popleft()
        if splits == N:
            final_count += 1
            continue
        if splits >= N:
            continue
        
        for (x, y) in list(state):
            t1 = (x + 1, y)
            t2 = (x + 1, (y + 1) % 4)
            if t1 not in state and t2 not in state:
                new_positions = set(s for s in state if s != (x, y))
                new_positions.add(t1)
                new_positions.add(t2)
                new_state = frozenset(new_positions)
                ns = splits + 1
                # only add if new or better
                old = seen_states.get(new_state, 10**9)
                if ns < old:
                    seen_states[new_state] = ns
                    q.append((new_state, ns))
    return final_count

for N in range(13):
    c = compute_C(N)
    print(f"C({N}) = {c}")
