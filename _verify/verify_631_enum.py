#!/usr/bin/env python3
"""Count inversion tables for various L with sum <= 40."""
def count_inv_tables(L, max_sum=40):
    dp = [0] * (max_sum + 1)
    dp[0] = 1
    for i in range(1, L + 1):
        max_a = L - i
        new_dp = [0] * (max_sum + 1)
        for s in range(max_sum + 1):
            if dp[s] == 0:
                continue
            for a in range(min(max_a, max_sum - s) + 1):
                new_dp[s + a] += dp[s]
        dp = new_dp
    return sum(dp)

for L in [5, 10, 20, 30, 40, 41, 50, 100]:
    cnt = count_inv_tables(L, 40)
    print(f"L={L}: {cnt}")

# Also compute how many are possible for very large L
# For L > 40, all entries a_i for i > 40 have bound L-i
# For i = 41 with L >= 41: bound L-41, which grows with L
# So for large L, there are MANY more possibilities
print()
print("For L > 40, entries i > 40 can have non-zero values")
print("But sum <= 40, so at most 40 entries can be non-zero")
print("And those non-zero entries could be at positions 1..40 (bounded)")
print("or at larger positions with larger bounds")
