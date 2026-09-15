#!/usr/bin/env python3
"""Verify PE 426 BBS final state through direct simulation"""
import sys

def generate_t(N):
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def bbs_one_turn(balls):
    """One turn of BBS: move each ball to nearest empty right"""
    occupied = set(balls)
    # Find max position to scan
    max_pos = max(balls) + len(balls) + 1000
    new_balls = set()
    moved = set()
    
    for b in sorted(balls):
        if b in moved:
            continue
        moved.add(b)
        # Find nearest empty to the right of b
        for p in range(b + 1, max_pos):
            if p not in occupied and p not in new_balls:
                new_balls.add(p)
                break
    
    return new_balls

def balls_to_occupied_blocks(balls):
    """Convert ball positions to sorted occupied block lengths"""
    if not balls:
        return []
    sorted_b = sorted(balls)
    blocks = []
    prev = sorted_b[0] - 1
    count = 0
    for b in sorted_b:
        if b == prev + 1:
            count += 1
        else:
            if count > 0:
                blocks.append(count)
            count = 1
        prev = b
    if count > 0:
        blocks.append(count)
    blocks.sort()
    return blocks

def alternating_to_balls(t):
    """Convert alternating sequence to ball positions"""
    balls = []
    pos = 0
    for i, length in enumerate(t):
        if i % 2 == 0:  # occupied
            for _ in range(length):
                balls.append(pos)
                pos += 1
        else:  # empty
            pos += length
    return balls

# Test with small example
t = generate_t(10)
print("t:", t)

balls = alternating_to_balls(t)
print("Initial balls at positions:", balls[:20], "..." if len(balls) > 20 else "")

# Simulate turns
prev_blocks = None
for turn in range(200):
    blocks = balls_to_occupied_blocks(balls)
    if blocks == prev_blocks:
        print(f"Stable after {turn} turns")
        break
    prev_blocks = blocks
    if turn % 50 == 0:
        print(f"Turn {turn}: {blocks}")
    balls = bbs_one_turn(balls)

print("Final occupied blocks:", blocks)
print("Sum:", sum(blocks))
print("Expected:", [1, 3, 10, 24, 51, 75])
print("Match:", blocks == [1, 3, 10, 24, 51, 75])
