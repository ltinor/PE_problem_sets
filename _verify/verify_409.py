#!/usr/bin/env python3
"""PE 409: Nim extreme"""
# A game of Nim with n heaps, each heap size from 1 to n.
# Two players take turns. A move consists of removing any positive
# number of stones from a SINGLE heap (standard Nim).
# The player who takes the last stone wins.
# 
# Let W(n) be the number of winning positions (positions where the
# first player can force a win) among all positions with heap sizes
# in [1, n] (each heap independently chosen from 1..n).
# Find W(n) for some n, modulo something.
# PE answer: 253223948

# In Nim, a position is winning (N-position) iff XOR of heap sizes ≠ 0.
# Total positions with heap sizes in [1,n] and k heaps: n^k.
# Winning positions: n^k - (number of positions with XOR = 0).

# Wait, what's the exact formulation? Let me check different parameterizations.

# The word "extreme" suggests min/max. Maybe: 
# "Consider all positions with heap sizes in [1,n] and k heaps.
# Let f(n,k) = number of winning positions. Find f(n,k) for given n,k."

# Or maybe: "For a given n, consider all positions where each heap size ≤ n
# (each heap independently). Find the number of P-positions (XOR = 0)."

# Let me compute for small n and k to see patterns.

def count_xor_zero(n, k, mod=None):
    """Count of k-tuples from [1,n]^k with XOR = 0"""
    from collections import Counter
    dp = Counter()
    dp[0] = 1
    for _ in range(k):
        ndp = Counter()
        for x, cnt in dp.items():
            for v in range(1, n + 1):
                ndp[x ^ v] += cnt
        dp = ndp
    result = dp[0]
    if mod:
        result %= mod
    return result

# Test
for n in range(1, 6):
    for k in range(1, 5):
        total = n ** k
        zero = count_xor_zero(n, k)
        print(f"n={n}, k={k}: total={total}, xor0={zero}, win={total-zero}")

# Maybe the problem asks: for n heaps, heap i has size in [1, i].
# More generally: heaps of size 1..n, but the sizes form a permutation?
# PE 409: Let me think... "Nim extreme" - this usually means:
# "Consider Nim where the heap sizes are a permutation of 1..n.
# How many permutations result in a winning position for the first player?"

def count_winning_permutations(n, mod=None):
    """Count permutations of 1..n as heap sizes that are N-positions"""
    import itertools
    win = 0
    for perm in itertools.permutations(range(1, n+1)):
        xor = 0
        for x in perm:
            xor ^= x
        if xor != 0:
            win += 1
    if mod:
        win %= mod
    return win

print("\nPermutation Nim:")
for n in range(1, 9):
    w = count_winning_permutations(n)
    f = 1
    for i in range(1, n+1):
        f *= i
    print(f"n={n}: win={w}, total={f}, lose={f-w}")

# PE 409 answer might be something like: number of winning permutations
# for n=10^5 or n=10^6, modulo something.
# 253223948

# Let me check: for larger n, all permutations are winning if n is not
# of the form 4k? XOR of 1..n = 1 if n≡1 mod 4, n+1 if n≡2 mod 4,
# 0 if n≡3 mod 4, n if n≡0 mod 4.
# Wait, XOR of ALL numbers 1..n: this cycles every 4.
# For a permutation, the XOR is still the XOR of {1..n} (since XOR is
# commutative and associative). So EVERY permutation has the same XOR.
# That means either ALL permutations are winning or ALL are losing!

import functools
import operator

print("\nXOR of 1..n:")
for n in range(1, 17):
    xor_all = functools.reduce(operator.xor, range(1, n+1))
    print(f"n={n}: XOR={xor_all}")

# So "Nim extreme" must be a different game variant.
# Maybe it's not about permutations but about something else.
# 
# "Nim extreme" - could be about Nim where you can remove from at most k heaps?
# Or Nim where heaps are arranged in a line and you can only take from ends?
# 
# Actually, PE 409 is: "Nim is a game played with heaps of stones, where
# players alternate taking any positive number of stones from any single heap.
# We consider the variant called 'extreme Nim': ..."
#
# Maybe: "A position in extreme Nim has heap sizes 1..n where n is even.
# The player who takes the last stone wins. Find the number of winning
# positions..." 
#
# Or maybe: "In 'extreme Nim', each heap has at most 1 stone (i.e., sizes 0 or 1).
# This is just impartial game with binary heaps."
#
# I think PE 409 might be about: 
# "Define W(n) = number of winning positions in Nim where there are exactly
# n stones total, and all heap sizes are ≤ n (or something)."
#
# Let me try: "Nim extreme means you can take stones from ANY number of heaps
# in a single move (like the misère version?)" No.

# Let me try: "Extreme Nim: All heaps have size exactly 1. Players remove
# any number of heaps (1 to all). This is just the subtraction game where
# you can remove 1 to n stones." The winning positions are those not divisible
# by (n+1). Number of winning positions = n^k - something.

# Hmm wait. Actually let me try: "Extreme Nim" could mean you can remove
# stones from all non-empty heaps? Or the move is: choose a heap and
# either remove all stones or reduce to 1?

# Let me just try: W(n) = number of subsets of {1..n} with XOR ≠ 0
# (positions where you have some subset of possible heap sizes)
# But this gives 2^n - 1 or similar.

# OK, let me try the interpretation: 
# "Nim extreme" = the game where you have n heaps, heap i has i stones.
# (So heap sizes are 1, 2, 3, ..., n).
# Find the number of ways to remove some stones (a move) such that the
# resulting position is a P-position (losing for next player).

# OR: "Consider Nim with heaps of sizes from {1,...,n}. For each subset S
# of {1,...,n}, consider the position with heaps sizes = elements of S.
# Count how many subsets give winning positions."

def count_subsets_xor(n, mod=None):
    """Count subsets of {1..n} with XOR ≠ 0 (winning Nim positions)"""
    # DP over possible subset XORs
    dp = {0: 1}  # xor -> count
    for x in range(1, n+1):
        ndp = dict(dp)
        for xor_val, cnt in dp.items():
            ndp[xor_val ^ x] = ndp.get(xor_val ^ x, 0) + cnt
        dp = ndp
    total = sum(dp.values())
    winning = total - dp.get(0, 0)
    if mod:
        winning %= mod
    return winning

print("\nSubset Nim (heap sizes = subset of 1..n):")
for n in range(1, 11):
    w = count_subsets_xor(n)
    print(f"n={n}: winning subsets = {w} (total={2**n})")

# Does 253223948 match any of these? Let me try n=28:
# 2^28 = 268435456. 253223948 = ? 
# 268435456 - 253223948 = 15211508
# Hmm, that's not a clean power of 2.

# Let me try: n=30, total=2^30=1073741824
# 1073741824 - 253223948 = 820517876
# No pattern.

# Maybe the answer is modulo 10^9 (+7 or +9)?
print(f"\n253223948 mod 10^9+7 = {253223948 % (10**9+7)}")
print(f"253223948 mod 10^9+9 = {253223948 % (10**9+9)}")
