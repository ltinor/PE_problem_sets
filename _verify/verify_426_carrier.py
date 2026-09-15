#!/usr/bin/env python3
"""Test carrier process for BBS"""
import sys

def generate_t(N):
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def bbs_carrier_one_turn(balls_set):
    """One turn of BBS using carrier process"""
    # balls_set: set of positions with balls
    max_pos = max(balls_set) if balls_set else 0
    new_balls = set()
    c = 0
    # Scan positions
    for pos in range(max_pos + 1000):  # scan a bit beyond
        if pos in balls_set:
            c += 1  # pick up ball
        else:
            if c > 0:
                new_balls.add(pos)
                c -= 1  # place ball
    # Place remaining carrier balls
    p = max(max_pos + 1000, max(new_balls) if new_balls else 0)
    while c > 0:
        p += 1
        new_balls.add(p)
        c -= 1
    return new_balls

def alternating_to_balls(t):
    balls = []
    pos = 0
    for i, length in enumerate(t):
        if i % 2 == 0:
            for _ in range(length):
                balls.append(pos)
                pos += 1
        else:
            pos += length
    return set(balls)

def balls_to_occupied_blocks(balls):
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

# Test
t = generate_t(10)
print("t:", t)
balls = alternating_to_balls(t)
print("Initial balls:", sorted(balls))

prev_blocks = None
for turn in range(20):
    blocks = balls_to_occupied_blocks(balls)
    print(f"Turn {turn}: {blocks}")
    if blocks == prev_blocks:
        print(f"Stable after {turn} turns")
        break
    prev_blocks = blocks
    balls = bbs_carrier_one_turn(balls)

print("Final:", blocks)
print("Expected:", [1, 3, 10, 24, 51, 75])
print("Match:", blocks == [1, 3, 10, 24, 51, 75])
