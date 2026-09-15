#!/usr/bin/env python3
"""PE 406: Guessing Game - verify answer"""
# We need to find the sum for n=1..10^4 of the minimal expected 
# number of guesses with costs: too_low=1, too_high=1
# Answer: 36813.982586

# Let me think about what PE 406 actually asks...
# Actually PE 406: "Guessing Game"
# We want to guess an integer t ∈ [1, n]
# Each guess x costs: "too low" costs a, "too high" costs b
# Minimize worst-case cost, sum over all t
# Wait, or is it expected value?

# Let me check: 36813.982586 as a float sum
# If it were a straight sum of integers for n up to 10^4, it would be integer.
# The decimal suggests it's a probability/expected value.

# Actually, PE 406: there are TWO costs: if guess is too low, cost = 2;
# if too high, cost = 1. Compute minimal expected number of guesses
# for the optimal strategy, averaged over all secret numbers.
# Sum the minimal expected values for n = 1 to 10^4.

# Let me implement: binary search with asymmetric costs.
# DP: E[l][r] = min cost to guess a number in [l, r]
# E[l][r] = min_{x in [l,r]} (prob(x< t)*cost_low + prob(x>t)*cost_high + 
#            prob(x< t)*E[l][x-1] + prob(x>t)*E[x+1][r])
# But since all t are equally likely...

# Actually the game is: Alice picks t. Bob guesses. For each guess x:
# if x < t: pay cost_less
# if x > t: pay cost_greater  
# if x = t: done
# Bob wants to minimize worst-case total cost (adversarial).
# The answer is sum over n=1..M of f(n) where f(n) is the min worst-case cost.

# Let's try costs (1, 1) first - standard binary search. Worst case ~ log2(n).
# Sum for n=1..100: let's compute

def min_max_cost_binary(n, cost_less=1, cost_more=1):
    """Min worst-case cost for guessing in [1,n]"""
    # With equal costs, this is just ceil(log2(n+1))
    # Actually worst-case number of guesses for binary search
    if n <= 1:
        return 1 if n == 1 else 0
    # Binary search: worst case is ceil(log2(n))
    import math
    return math.ceil(math.log2(n + 1))

# But the answer 36813.982586 has decimals. So it's PROBABLY expected value,
# not worst case.

# Let me try: minimize EXPECTED cost when t is uniformly random in [1,n].
# DP: E[l][r] = expected cost for interval [l,r]
# E[l][r] = 0 if l > r
# E[l][r] = min_{x in [l,r]} ( cost_less*(x-l)/(r-l+1) + cost_more*(r-x)/(r-l+1)
#            + (x-l)/(r-l+1)*E[l][x-1] + (r-x)/(r-l+1)*E[x+1][r] )
# Then E[l][r] = min_x ... multiply both sides by (r-l+1):
# (r-l+1)*E[l][r] = min_x (cost_less*(x-l) + cost_more*(r-x)
#                         + (x-l)*E[l][x-1] + (r-x)*E[x+1][r])

# Let's compute for small n and see

def expected_cost(n, cost_less=2, cost_more=1):
    """Compute min expected cost for range [1,n]"""
    # E[i][j] for i <= j
    E = [[0.0] * (n+2) for _ in range(n+2)]
    for length in range(1, n+1):
        for l in range(1, n - length + 2):
            r = l + length - 1
            best = float('inf')
            for x in range(l, r+1):
                exp = (cost_less * (x - l) + cost_more * (r - x) + 
                       (x - l) * E[l][x-1] + (r - x) * E[x+1][r])
                exp /= (r - l + 1)
                if exp < best:
                    best = exp
            E[l][r] = best
    return E[1][n]

# Let's test with small n
for n in range(1, 11):
    ec = expected_cost(n, 2, 1)
    print(f"n={n}: expected={ec:.6f}")

# Let's compute sum for n=1..100
total = 0.0
for n in range(1, 101):
    total += expected_cost(n, 2, 1)
print(f"\nSum n=1..100: {total:.6f}")
