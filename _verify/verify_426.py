#!/usr/bin/env python3
"""Verify PE 426 Box-ball system algorithm"""
import sys

def generate_t(N):
    """Generate t_0 through t_N"""
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def bbs_simulate(t):
    """Direct BBS simulation for small examples to verify"""
    # t is alternating occupied/empty block lengths
    # Convert to ball positions
    balls = set()
    pos = 0
    for i, length in enumerate(t):
        if i % 2 == 0:  # occupied
            for _ in range(length):
                balls.add(pos)
                pos += 1
        else:  # empty
            pos += length
    
    # Simulate turns until stable
    prev = None
    turn = 0
    while True:
        # Compute occupied block lengths
        occupied_blocks = []
        sorted_balls = sorted(balls)
        if not sorted_balls:
            return []
        prev_pos = sorted_balls[0] - 1
        count = 0
        for b in sorted_balls:
            if b == prev_pos + 1:
                count += 1
            else:
                if count > 0:
                    occupied_blocks.append(count)
                count = 1
            prev_pos = b
        if count > 0:
            occupied_blocks.append(count)
        occupied_blocks.sort()
        
        if occupied_blocks == prev:
            return occupied_blocks
        prev = occupied_blocks
        turn += 1
        if turn > 1000:
            return None
        
        # One turn of BBS
        new_balls = set()
        moved = set()
        sorted_balls = sorted(balls)
        for b in sorted_balls:
            if b in moved:
                continue
            moved.add(b)
            # Find nearest empty to the right
            for pos in range(b + 1, max(balls) + len(balls) + 10):
                if pos not in balls and pos not in new_balls:
                    new_balls.add(pos)
                    break
        balls = new_balls

def final_state_carrier(occupied_blocks):
    """Compute BBS final state using carrier method"""
    # This should work for the BBS final state
    # occupied_blocks: list of occupied block lengths
    a = {}  # a[length] = count
    
    for x in occupied_blocks:
        remain = x
        i = 1
        while remain > 0:
            if i in a and a[i] > 0:
                take = min(remain, a[i])
                a[i] -= take
                if a[i] == 0:
                    del a[i]
                a[i + 1] = a.get(i + 1, 0) + take
                remain -= take
            i += 1
            if i > 10000:
                break
        if remain > 0:
            a[remain] = a.get(remain, 0) + 1
    
    result = []
    for k in sorted(a.keys()):
        result.extend([k] * a[k])
    return result

def final_state_v2(occupied_blocks):
    """Alternative method: sort and process from largest"""
    blocks = sorted(occupied_blocks, reverse=True)
    a = {}
    
    for x in blocks:
        # Find the largest existing soliton that can absorb this
        remain = x
        # Try to distribute among existing solitons
        keys = sorted(a.keys())
        for k in keys:
            if remain == 0:
                break
            if a[k] > 0:
                take = min(remain, a[k])
                a[k] -= take
                if a[k] == 0:
                    del a[k]
                a[k + 1] = a.get(k + 1, 0) + take
                remain -= take
        if remain > 0:
            a[remain] = a.get(remain, 0) + 1
    
    result = []
    for k in sorted(a.keys()):
        result.extend([k] * a[k])
    return result

def final_state_v3(occupied_blocks):
    """Yet another approach: the '10-elimination' method"""
    # Count occurrences
    from collections import Counter
    cnt = Counter(occupied_blocks)
    
    # Process from smallest to largest
    max_v = max(occupied_blocks) if occupied_blocks else 0
    for v in range(1, max_v + 100):
        if cnt[v] == 0:
            continue
        # For each group of v+1 blocks of size v, they form one block of size v+1
        q = cnt[v] // (v + 1)
        if q > 0:
            cnt[v] -= q * (v + 1)
            cnt[v + 1] += q
    
    result = []
    for k in sorted(cnt.keys()):
        result.extend([k] * cnt[k])
    return result

# Test with the example
t_small = generate_t(10)
print("t_0..t_10:", t_small)

occupied_small = [t_small[i] for i in range(0, len(t_small), 2)]
print("Occupied blocks:", occupied_small)
print("Sum:", sum(occupied_small))

# Try different algorithms
result_carrier = final_state_carrier(occupied_small)
print("Carrier method:", result_carrier, "sum:", sum(result_carrier), "sq sum:", sum(x*x for x in result_carrier))

result_v2 = final_state_v2(occupied_small)
print("V2 method:", result_v2, "sum:", sum(result_v2), "sq sum:", sum(x*x for x in result_v2))

result_v3 = final_state_v3(occupied_small)
print("V3 method:", result_v3, "sum:", sum(result_v3), "sq sum:", sum(x*x for x in result_v3))

# Expected: [1, 3, 10, 24, 51, 75], sq sum = 1+9+100+576+2601+5625 = 8912
expected = [1, 3, 10, 24, 51, 75]
print("Expected:", expected, "sq sum:", sum(x*x for x in expected))
