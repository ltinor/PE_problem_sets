#!/usr/bin/env python3
"""Explore PE 762: Amoebas in 2D grid - enumerating final states"""
from collections import deque

def count_arrangements(N):
    """Count distinct final states after exactly N splits."""
    initial = frozenset([(0, 0)])
    seen_states = {initial: 0}  # state -> min splits to reach
    
    q = deque([(initial, 0)])
    final_count = 0
    
    while q:
        state, splits = q.popleft()
        if splits == N:
            final_count += 1
            continue
        if splits > N:
            continue
        
        # Try splitting each amoeba in the state
        for (x, y) in list(state):
            target1 = (x + 1, y)
            target2 = (x + 1, (y + 1) % 4)
            if target1 not in state and target2 not in state:
                # Create new state
                new_positions = set(state)
                new_positions.remove((x, y))
                new_positions.add(target1)
                new_positions.add(target2)
                new_state = frozenset(new_positions)
                
                if new_state not in seen_states or seen_states[new_state] > splits + 1:
                    seen_states[new_state] = splits + 1
                    q.append((new_state, splits + 1))
    
    return final_count

for N in range(11):
    c = count_arrangements(N)
    print(f"C({N}) = {c}")
