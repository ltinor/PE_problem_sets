#!/usr/bin/env python3
"""Examine C(4) configurations for PE 762"""
from collections import deque

def count_and_print(N):
    initial = frozenset([(0, 0)])
    seen = {}
    final_states = set()
    
    q = deque([(initial, 0)])
    while q:
        state, splits = q.popleft()
        if splits == N:
            final_states.add(state)
            continue
        if splits > N:
            continue
        
        for (x, y) in list(state):
            t1 = (x + 1, y)
            t2 = (x + 1, (y + 1) % 4)
            if t1 not in state and t2 not in state:
                new_positions = set(state)
                new_positions.remove((x, y))
                new_positions.add(t1)
                new_positions.add(t2)
                new_state = frozenset(new_positions)
                key = (new_state, splits + 1)
                if key not in seen:
                    seen[key] = True
                    q.append((new_state, splits + 1))
    
    return final_states

for N in range(5):
    states = count_and_print(N)
    print(f"\nC({N}) = {len(states)}")
    for s in sorted(states, key=lambda x: sorted(x)):
        print(f"  {sorted(s)}")
