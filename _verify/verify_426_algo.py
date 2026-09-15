#!/usr/bin/env python3
"""Find algorithm for BBS final state from occupied blocks"""
import sys
import heapq

def generate_t(N):
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def final_state_v4(occupied_blocks):
    """Try: for each x, find smallest in multiset, replace with x+s"""
    h = []  # min-heap
    for x in occupied_blocks:
        if not h:
            heapq.heappush(h, x)
        else:
            s = heapq.heappop(h)
            heapq.heappush(h, x + s)
    return sorted(h)

def final_state_v5(occupied_blocks):
    """Try: maintain counters, process blocks from left"""
    # Using the "10-elimination": for each v, v*(v+1) of them form v+1
    from collections import Counter
    cnt = Counter()
    for x in occupied_blocks:
        cnt[x] += 1
    # Then reduce
    changed = True
    while changed:
        changed = False
        for v in sorted(cnt.keys()):
            if cnt[v] >= v + 1:
                q = cnt[v] // (v + 1)
                cnt[v] -= q * (v + 1)
                cnt[v + 1] += q
                changed = True
    result = []
    for k in sorted(cnt.keys()):
        result.extend([k] * cnt[k])
    return result

def final_state_v6(occupied_blocks):
    """Carrier-based: process all blocks through the carrier,
    and the soliton content is derived from the carrier overflow"""
    # This is the "slot" method
    # Maintain an array slot[1..max_val] = max balls at each level
    max_val = 64  # since t_k <= 64
    carrier = [0] * (max_val * 200)  # overestimate
    
    for x in occupied_blocks:
        # Add x to the carrier at level 0
        # Then propagate
        c = x
        level = 0
        while c > 0:
            if level >= len(carrier):
                carrier.append(0)
            if carrier[level] > 0:
                take = min(c, carrier[level])
                carrier[level] -= take
                carrier[level + 1] += take
                c -= take
            else:
                carrier[level] = c
                c = 0
            level += 1
    
    result = []
    for i, cnt in enumerate(carrier):
        if cnt > 0:
            result.extend([i + 1] * cnt)  # +1 for 1-indexed
    return sorted(result)

def final_state_v7(occupied_blocks):
    """Another method: process occupied blocks as they are,
    treating the carrier as the number of balls at each 'slot'"""
    # The BBS carrier process for occupied blocks directly
    # Maintain a list of soliton sizes
    solitons = []
    for x in occupied_blocks:
        # Each occupied block of size x adds x balls
        # Distribute among existing solitons
        added = False
        for i in range(len(solitons)):
            if solitons[i] <= x:
                # This soliton can merge with the new balls
                solitons[i] += x
                added = True
                break
        if not added:
            solitons.append(x)
        solitons.sort()
    return solitons

def final_state_v8(occupied_blocks):
    """RSK-based: use patience sorting"""
    piles = []
    for x in occupied_blocks:
        # Find leftmost pile whose top >= x
        placed = False
        for pile in piles:
            if pile[-1] >= x:
                pile.append(x)
                placed = True
                break
        if not placed:
            piles.append([x])
    # Row lengths give shape
    result = [len(p) for p in piles]
    result.sort()
    return result

def final_state_v9(occupied_blocks):
    """RSK variant: find leftmost pile whose top > x"""
    piles = []
    for x in occupied_blocks:
        placed = False
        for pile in piles:
            if pile[-1] > x:
                pile.append(x)
                placed = True
                break
        if not placed:
            piles.append([x])
    result = [len(p) for p in piles]
    result.sort()
    return result

def final_state_v10(occupied_blocks):
    """Process block sizes through carrier, compute soliton from cumulative"""
    # This is the method from the Takahashi-Satsuma paper:
    # The soliton content is given by the differences of the "capacity" function
    n = len(occupied_blocks)
    # Compute prefix sums
    pref = [0]
    for x in occupied_blocks:
        pref.append(pref[-1] + x)
    
    # For each position, the "height" of the Young diagram
    # The soliton is the conjugate partition
    # Actually, compute the "capacity" function F(i) = pref[i] + (some function of empty blocks)
    # But we only have occupied blocks
    
    # Try: soliton content = differences of sorted prefix sums?
    return []

t = generate_t(10)
occupied = [t[i] for i in range(0, len(t), 2)]
print("Occupied:", occupied)

# Test each method
methods = [
    ("v4 heap", final_state_v4),
    ("v5 10-elim", final_state_v5),
    ("v6 carrier", final_state_v6),
    ("v7 soliton-merge", final_state_v7),
    ("v8 RSK", final_state_v8),
    ("v9 RSK2", final_state_v9),
]

expected = [1, 3, 10, 24, 51, 75]
for name, fn in methods:
    result = fn(occupied)
    match = "✓" if result == expected else "✗"
    print(f"{match} {name}: {result}")

# Let me also test with larger examples to see patterns
print("\n--- Testing with more data ---")
t2 = generate_t(100)
occ2 = [t2[i] for i in range(0, len(t2), 2)]
# Compare v7 and v8
r7 = final_state_v7(occ2)
r8 = final_state_v8(occ2)
print(f"v7 ({len(r7)}): {r7[:20]}...")
print(f"v8 ({len(r8)}): {r8[:20]}...")
print(f"v7 sum: {sum(r7)}, total: {sum(occ2)}")
print(f"v8 sum: {sum(r8)}, total: {sum(occ2)}")
