#!/usr/bin/env python3
"""Find BBS final state - try more approaches"""
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

def alternating_to_balls(t):
    balls = set()
    pos = 0
    for i, length in enumerate(t):
        if i % 2 == 0:
            for _ in range(length):
                balls.add(pos)
                pos += 1
        else:
            pos += length
    return balls

def bbs_carrier_one_turn(balls_set):
    max_pos = max(balls_set) if balls_set else 0
    new_balls = set()
    c = 0
    for pos in range(max_pos + 5000):
        if pos in balls_set:
            c += 1
        else:
            if c > 0:
                new_balls.add(pos)
                c -= 1
    p = max(max_pos + 5000, max(new_balls) if new_balls else 0)
    while c > 0:
        p += 1
        new_balls.add(p)
        c -= 1
    return new_balls

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

def final_state_sim(occupied_blocks_all, empty_blocks_all):
    """Simulate BBS using alternating blocks, return final occupied blocks"""
    # Convert to alternating sequence
    t = []
    for i in range(max(len(occupied_blocks_all), len(empty_blocks_all))):
        if i < len(occupied_blocks_all):
            t.append(occupied_blocks_all[i])
        if i < len(empty_blocks_all):
            t.append(empty_blocks_all[i])
    
    balls = alternating_to_balls(t)
    prev = None
    for _ in range(1000):
        blocks = balls_to_occupied_blocks(balls)
        if blocks == prev:
            return blocks
        prev = blocks
        balls = bbs_carrier_one_turn(balls)
    return blocks

def final_state_capacity(occupied, empty):
    """Try capacity/convex hull method"""
    # C[i] = cumulative sum of (occupied - empty)
    cum = [0]
    for i in range(len(occupied)):
        cum.append(cum[-1] + occupied[i])
        if i < len(empty):
            cum.append(cum[-1] - empty[i])
    
    # Find upper envelope
    # Take points (i, cum[i]) for i = 0, 2, 4, ... (occupied block boundaries)
    points = [(i, cum[i]) for i in range(0, len(cum), 2)]
    
    # Convex hull (upper envelope) - monotone chain
    # Actually, we want the concave upper envelope
    hull = []
    for x, y in points:
        while len(hull) >= 2:
            x1, y1 = hull[-2]
            x2, y2 = hull[-1]
            # Cross product to check if (x2,y2) is below line (x1,y1)-(x,y)
            if (x2 - x1) * (y - y1) - (y2 - y1) * (x - x1) <= 0:
                hull.pop()
            else:
                break
        hull.append((x, y))
    
    # Soliton sizes are the slopes of the hull segments
    solitons = []
    for i in range(1, len(hull)):
        dx = hull[i][0] - hull[i-1][0]
        dy = hull[i][1] - hull[i-1][1]
        if dx > 0:
            soliton = dy // dx  # slope
            # Actually dy/dx might not be integer...
            # The soliton is dy (the rise), and there are dx of them?
            solitons.append(dy)  # total rise across dx blocks
            for _ in range(dx):
                pass  # hmm
    
    return solitons

def final_state_toda(occupied, empty):
    """Ultra-discrete Toda: compute eigenvalues of Lax matrix"""
    # L = bidiagonal with occupied on diagonal, 1 on sub-diagonal
    # But ultra-discrete eigenvalues are computed differently
    n = len(occupied)
    
    # In max-plus algebra, compute characteristic polynomial
    # p_k(λ) = max(o_{k-1} + p_{k-1}(λ), 1 + p_{k-2}(λ)) 
    # Actually for Toda, it's more complex
    
    # Let me try: sort the occupied blocks and see
    result = sorted(occupied)
    return result

def final_state_fermi(occupied, empty):
    """Maya diagram / Fermi sea approach"""
    # Compute "charge" at each boundary
    n = len(occupied)
    charges = [0]
    for i in range(n):
        charges.append(charges[-1] + occupied[i])
        if i < len(empty):
            charges.append(charges[-1] - empty[i])
    
    # The soliton content = the conjugate of the partition 
    # given by the positive part of the charge
    # Or: the row lengths of the Young diagram where row i has 
    # length = max(0, some function of charges)
    
    # Actually, for the BBS, the soliton content is the set of 
    # "distances" between balls in the initial configuration
    # after removing the "vacancies"
    
    return []

t = generate_t(10)
occupied = [t[i] for i in range(0, len(t), 2)]
empty = [t[i] for i in range(1, len(t), 2)]

print("Occupied:", occupied)
print("Empty:", empty)

# Get actual final state by simulation
actual = final_state_sim(occupied, empty)
print("Actual final:", actual)

# Try to see relationship between initial and final
print("\nAnalysis:")
print("Sum occupied:", sum(occupied))
print("Sum empty:", sum(empty))

# Sort occupied
sorted_occ = sorted(occupied)
print("Sorted occupied:", sorted_occ)

# The final state [1,3,10,24,51,75] - what's the pattern?
# 1, 3, 10, 24, 51, 75
# Differences: 2, 7, 14, 27, 24
# No obvious pattern

# Let me look at the cumulative charge
cum = 0
charges = []
for i in range(len(occupied)):
    cum += occupied[i]
    charges.append(cum)
    if i < len(empty):
        cum -= empty[i]
    charges.append(cum)
print("Charges:", charges)
print("Final charge:", cum)

# Is the final state related to the charges?
# Maybe the solitons are the "positive peaks" of the charge function?
print("\n--- Testing bigger example ---")
t100 = generate_t(100)
occ100 = [t100[i] for i in range(0, len(t100), 2)]
emp100 = [t100[i] for i in range(1, len(t100), 2)]

# Simulate to get actual final state
print("Simulating 100 elements...")
actual100 = final_state_sim(occ100, emp100)
print(f"Final (len={len(actual100)}): {actual100[:30]}...")
print(f"Sum: {sum(actual100)}")
print(f"Expected total: {sum(occ100)}")

# Check: is the number of solitons preserved?
print(f"# occupied blocks: {len(occ100)}, # solitons: {len(actual100)}")
