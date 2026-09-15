#!/usr/bin/env python3
"""Try RSK correspondence for BBS soliton decomposition"""
import sys
import bisect

def generate_t(N):
    s = 290797
    MOD = 50515093
    t = []
    for _ in range(N + 1):
        t.append((s % 64) + 1)
        s = (s * s) % MOD
    return t

def rsk_row_insert(tableau, x):
    """Schensted row insertion: insert x into tableau, return new tableau"""
    for row in tableau:
        # Find leftmost element > x
        idx = bisect.bisect_right(row, x)
        if idx < len(row):
            # Bump this element
            x, row[idx] = row[idx], x
        else:
            # Append to end of row
            row.append(x)
            return tableau
    # Need new row
    tableau.append([x])
    return tableau

def rsk_from_word(word):
    """Apply RSK to a word (list of integers)"""
    P = []  # insertion tableau
    for x in word:
        P = rsk_row_insert(P, x)
    return P

def shape(tableau):
    """Return the shape (row lengths) of a tableau"""
    return [len(row) for row in tableau]

def alternating_to_word(t):
    """Convert alternating sequence to RSK word.
    Occupied blocks -> 1's, Empty blocks -> 2's"""
    word = []
    for i, val in enumerate(t):
        digit = 1 if i % 2 == 0 else 2
        word.extend([digit] * val)
    return word

# Test with example
t = generate_t(10)
word = alternating_to_word(t)
print(f"Word length: {len(word)}")
print(f"Word first 50: {word[:50]}")

P = rsk_from_word(word)
sh = shape(P)
print(f"Shape: {sh}")
print(f"Expected final state: [1, 3, 10, 24, 51, 75]")
print(f"Sum shape: {sum(sh)}")

# The shape should match the soliton content
# But it might be the CONJUGATE partition
# Let me try both the shape and its conjugate

def conjugate_partition(sh):
    if not sh:
        return []
    conj = []
    for i in range(sh[0]):
        cnt = sum(1 for x in sh if x > i)
        if cnt > 0:
            conj.append(cnt)
    return conj

conj = conjugate_partition(sh)
print(f"Conjugate: {conj}")

# Also try: maybe I should insert 2's first then 1's? Or use a different alphabet?
# Let me try with 0 and 1
def alternating_to_word_01(t):
    word = []
    for i, val in enumerate(t):
        digit = 0 if i % 2 == 0 else 1
        word.extend([digit] * val)
    return word

word01 = alternating_to_word_01(t)
P01 = rsk_from_word(word01)
sh01 = shape(P01)
print(f"\nWith 0/1 word:")
print(f"Shape: {sh01}")
print(f"Conjugate: {conjugate_partition(sh01)}")

# What about inserting in REVERSE order?
word_rev = list(reversed(word))
P_rev = rsk_from_word(word_rev)
sh_rev = shape(P_rev)
print(f"\nReversed word shape: {sh_rev}")
print(f"Reversed conjugate: {conjugate_partition(sh_rev)}")

# What about different sizes - compare with simulation
def bbs_sim(t):
    """Simulate BBS to get final state (for verification)"""
    seq = list(t)
    prev = None
    for _ in range(10000):
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
        while merged and merged[0][0] == 'E': merged.pop(0)
        while merged and merged[-1][0] == 'E': merged.pop()
        if not merged: seq = [0]
        else:
            seq = [merged[0][1]]
            for j in range(1, len(merged)): seq.append(merged[j][1])
        occ = sorted([seq[j] for j in range(0, len(seq), 2)])
        if occ == prev: return occ
        prev = occ
    return None

sim_result = bbs_sim(t)
print(f"\nSimulation final: {sim_result}")
