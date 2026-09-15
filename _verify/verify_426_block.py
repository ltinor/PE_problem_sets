#!/usr/bin/env python3
"""BBS block-level simulation to find patterns"""
import sys

def generate_t(N):
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def alternating_to_balls_positions(t):
    """Convert alternating sequence to ball positions for verification"""
    balls = []
    pos = 0
    for i, length in enumerate(t):
        if i % 2 == 0:
            balls.extend(range(pos, pos + length))
        pos += length
    return balls

def bbs_turn_block(seq):
    """One turn of BBS on alternating block sequence.
    seq = [o0, e0, o1, e1, ..., ok] (odd length, starts and ends with occupied)
    Returns new alternating sequence (starts with occupied, may have different length)"""
    c = 0  # carrier
    new_seq = []  # new alternating sequence
    new_seq.append(0)  # new occupied block 0 size
    
    # We process blocks in pairs (occupied, empty) except the last occupied
    for i, val in enumerate(seq):
        if i % 2 == 0:  # occupied block
            c += val
        else:  # empty block
            filled = min(c, val)
            c -= filled
            
            # The filled portion becomes part of the next occupied block
            # Actually, the filled empty slots become OCCUPIED
            
            if filled > 0:
                new_seq[-1] += filled  # add to current occupied block
            
            remaining_empty = val - filled
            if remaining_empty > 0:
                # There's still empty space, so we start a new occupied block after it
                new_seq.append(remaining_empty)  # empty block
                new_seq.append(0)  # placeholder for next occupied block
            elif filled > 0:
                # All empty was filled, but there might be more carrier
                # The empty block becomes an occupied block
                # Wait, the balls placed in this empty block are now occupied
                # They're already added to new_seq[-1]
                # But what about the empty block? It's gone (filled)
                # If c > 0, we continue placing balls in subsequent empty blocks
                pass
    
    # After all blocks, remaining carrier becomes the last occupied block
    if c > 0:
        new_seq[-1] += c
    
    # Clean up: remove leading/trailing zeros, ensure starts with occupied
    # Remove zero-size blocks at the beginning
    while new_seq and new_seq[0] == 0:
        new_seq.pop(0)
        if new_seq:
            new_seq.pop(0)  # also remove the following empty block
    
    # Remove trailing zeros
    while new_seq and new_seq[-1] == 0:
        new_seq.pop()
        if new_seq:
            new_seq.pop()  # also remove preceding empty block
    
    # Ensure starts with occupied
    if not new_seq:
        return [0]
    return new_seq

def extract_occupied(seq):
    """Extract and sort occupied block sizes from alternating sequence"""
    occ = [seq[i] for i in range(0, len(seq), 2)]
    occ.sort()
    return occ

# Test with small example
t = generate_t(10)
seq = list(t)  # alternating sequence
print("Initial seq:", seq)
print("Initial occupied (sorted):", extract_occupied(seq))

for turn in range(10):
    new_seq = bbs_turn_block(seq)
    occ_new = extract_occupied(new_seq)
    print(f"Turn {turn+1}: occupied={occ_new}")
    if occ_new == extract_occupied(seq):
        print(f"Stable after {turn+1} turns!")
        break
    seq = new_seq

# Also verify using ball-level simulation
print("\n--- Verifying with ball-level sim ---")
t = generate_t(10)
balls = set(alternating_to_balls_positions(t))

def carrier_one_turn(balls_set):
    max_pos = max(balls_set)
    new_balls = set()
    c = 0
    for pos in range(max_pos + 5000):
        if pos in balls_set:
            c += 1
        else:
            if c > 0:
                new_balls.add(pos)
                c -= 1
    p = max_pos + 5000
    while c > 0:
        p += 1
        new_balls.add(p)
        c -= 1
    return new_balls

def balls_to_occ(balls_set):
    if not balls_set:
        return []
    s = sorted(balls_set)
    blocks = []
    prev = s[0] - 1
    cnt = 0
    for b in s:
        if b == prev + 1:
            cnt += 1
        else:
            if cnt > 0:
                blocks.append(cnt)
            cnt = 1
        prev = b
    if cnt > 0:
        blocks.append(cnt)
    blocks.sort()
    return blocks

prev_occ = None
for turn in range(10):
    occ = balls_to_occ(balls)
    print(f"Ball-sim Turn {turn}: {occ}")
    if occ == prev_occ:
        break
    prev_occ = occ
    balls = carrier_one_turn(balls)
