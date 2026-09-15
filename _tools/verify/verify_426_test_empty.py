#!/usr/bin/env python3
"""Test if empty blocks affect BBS final state"""
import sys

def bbs_turn_blocks(seq):
    c = 0
    result = []
    for i, val in enumerate(seq):
        if i % 2 == 0:
            c += val
            result.append(('E', val))
        else:
            fill = min(c, val)
            c -= fill
            if fill > 0:
                result.append(('O', fill))
            remaining = val - fill
            if remaining > 0:
                result.append(('E', remaining))
    if c > 0:
        result.append(('O', c))
    
    merged = []
    for typ, size in result:
        if size == 0: continue
        if merged and merged[-1][0] == typ:
            merged[-1] = (typ, merged[-1][1] + size)
        else:
            merged.append((typ, size))
    
    while merged and merged[0][0] == 'E':
        merged.pop(0)
    while merged and merged[-1][0] == 'E':
        merged.pop()
    
    if not merged: return [0]
    flat = [merged[0][1]]
    for i in range(1, len(merged)):
        flat.append(merged[i][1])
    return flat

def extract_occupied(seq):
    return sorted([seq[i] for i in range(0, len(seq), 2)])

def simulate_to_end(seq):
    prev = None
    for _ in range(10000):
        seq = bbs_turn_blocks(seq)
        occ = extract_occupied(seq)
        if occ == prev:
            return occ
        prev = occ
    return None

# Original: occupied [46, 9, 21, 54, 3, 31], empty [24, 1, 51, 6, 7]
orig = [46, 24, 9, 1, 21, 51, 54, 6, 3, 7, 31]
print("Original final:", simulate_to_end(orig))

# Change empty blocks
test1 = [46, 100, 9, 100, 21, 100, 54, 100, 3, 100, 31]
print("Big empty final:", simulate_to_end(test1))

test2 = [46, 1, 9, 1, 21, 1, 54, 1, 3, 1, 31]
print("Small empty final:", simulate_to_end(test2))

test3 = [46, 0, 9, 0, 21, 0, 54, 0, 3, 0, 31]
print("Zero empty final:", simulate_to_end(test3))

# What about different order of occupied blocks?
test4 = [3, 24, 9, 1, 21, 51, 31, 6, 46, 7, 54]
print("Reordered occupied final:", simulate_to_end(test4))
