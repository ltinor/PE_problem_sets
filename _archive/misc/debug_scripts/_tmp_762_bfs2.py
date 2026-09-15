#!/usr/bin/env python3
"""Compute C(N) for PE 762 up to N=15 using BFS with pruning"""
from collections import deque, defaultdict

def compute_C_bfs(N):
    """Use BFS counting only final states by tracking which states are reachable at each split count."""
    # layers[splits] = set of frozensets reachable with exactly that many splits
    layers = [set() for _ in range(N+1)]
    initial = frozenset([(0, 0)])
    layers[0].add(initial)
    
    for k in range(N):
        print(f"  Layer {k}: {len(layers[k])} states")
        for state in layers[k]:
            for (x, y) in state:
                t1 = (x+1, y)
                t2 = (x+1, (y+1) % 4)
                if t1 not in state and t2 not in state:
                    new_positions = set(s for s in state if s != (x, y))
                    new_positions.add(t1)
                    new_positions.add(t2)
                    layers[k+1].add(frozenset(new_positions))
    
    return len(layers[N])

for N in range(15):
    c = compute_C_bfs(N)
    print(f"C({N}) = {c}")
