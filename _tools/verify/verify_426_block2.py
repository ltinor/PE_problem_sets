#!/usr/bin/env python3
"""BBS block-level simulation - corrected version"""
import sys

def generate_t(N):
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def bbs_turn_blocks(seq):
    """One turn of BBS on alternating block sequence.
    seq = [o0, e0, o1, e1, ..., ok] (odd length, starts/ends with occupied)
    Returns new alternating sequence."""
    c = 0  # carrier (balls that need to be placed)
    result = []  # list of (type, size) where type is 'O' or 'E'
    
    for i, val in enumerate(seq):
        if i % 2 == 0:  # occupied block
            # All balls in this block are picked up
            c += val
            # These positions become empty
            result.append(('E', val))
        else:  # empty block
            # Some of these empty positions get filled by carrier balls
            fill = min(c, val)
            c -= fill
            if fill > 0:
                result.append(('O', fill))
            remaining = val - fill
            if remaining > 0:
                result.append(('E', remaining))
    
    # Remaining carrier balls go to new positions at the right end
    if c > 0:
        result.append(('O', c))
    
    # Merge adjacent blocks of the same type
    merged = []
    for typ, size in result:
        if size == 0:
            continue
        if merged and merged[-1][0] == typ:
            merged[-1] = (typ, merged[-1][1] + size)
        else:
            merged.append((typ, size))
    
    # Ensure starts with occupied
    if merged and merged[0][0] == 'E':
        # The leading empty block... hmm. The BBS starts counting from first occupied.
        # But in the infinite line, empty blocks before first occupied are irrelevant.
        merged.pop(0)
    
    # Convert to flat list (just sizes alternating occupied/empty/...)
    # Must start with occupied
    flat = []
    for typ, size in merged:
        if typ == 'O' and not flat:
            flat.append(size)
        elif typ == 'E' and flat:
            flat.append(size)
        elif typ == 'O' and flat:
            # Two occupied blocks adjacent shouldn't happen after merging
            flat.append(0)  # empty block of size 0
            flat.append(size)
    
    # If we end with empty, add a 0 for trailing occupied? No, trim trailing empty.
    while len(flat) >= 2 and flat[-1] == 'E' if isinstance(flat[-1], str) else (len(flat) % 2 == 0):
        # Actually flat is numbers, even index = occupied, odd = empty
        break
    
    # Ensure odd length (end with occupied)
    if len(flat) % 2 == 0:
        flat.append(0)  # trailing occupied of size 0? That seems wrong.
    
    # Simplify: just return merged as alternating, starting with occupied
    # Remove trailing empty
    while merged and merged[-1][0] == 'E':
        merged.pop()
    # Remove leading empty
    while merged and merged[0][0] == 'E':
        merged.pop(0)
    
    if not merged:
        return [0]
    
    flat = [merged[0][1]]
    for i in range(1, len(merged)):
        flat.append(merged[i][1])
    
    return flat

def extract_occupied(seq):
    occ = [seq[i] for i in range(0, len(seq), 2)]
    occ.sort()
    return occ

# Test
t = generate_t(10)
seq = list(t)
print("Initial seq:", seq)
print("Initial occupied:", extract_occupied(seq))

for turn in range(10):
    new_seq = bbs_turn_blocks(seq)
    new_occ = extract_occupied(new_seq)
    old_occ = extract_occupied(seq)
    print(f"Turn {turn+1}: seq={new_seq}, occ={new_occ}")
    if new_occ == old_occ:
        print(f"Stable at turn {turn+1}")
        break
    seq = new_seq

# Now test with 1000 elements
print("\n--- Testing 1000 ---")
t1000 = generate_t(1000)
seq1000 = list(t1000)
print(f"Initial length: {len(seq1000)}")
for turn in range(50):
    new_seq = bbs_turn_blocks(seq1000)
    new_occ = extract_occupied(new_seq)
    old_occ = extract_occupied(seq1000)
    if turn % 10 == 0:
        print(f"Turn {turn+1}: len={len(new_seq)}, occ_len={len(new_occ)}")
    if new_occ == old_occ:
        print(f"Stable at turn {turn+1}, occ_len={len(new_occ)}")
        break
    seq1000 = new_seq
