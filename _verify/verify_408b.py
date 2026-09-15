#!/usr/bin/env python3
"""PE 408: Admissible paths through a grid - explore different formulations"""
import math

# Try different formulations to match known PE 408 behavior

# Formulation 1: admissible if x, y, x+y are all perfect powers
def is_perfect_power(x):
    if x <= 1:
        return x == 1
    for k in range(2, 21):  # up to 2^20
        r = round(x ** (1.0 / k))
        if r ** k == x or (r+1) ** k == x or (r-1) ** k == x:
            if r ** k == x:
                return True
    return False

def count_paths_pp(n, mod=None):
    """Paths where (x,y) admissible if x,y,x+y are all perfect powers"""
    dp = [[0] * (n + 1) for _ in range(n + 1)]
    dp[0][0] = 1
    for s in range(1, 2*n + 1):
        for x in range(max(0, s - n), min(n, s) + 1):
            y = s - x
            if x > n or y > n:
                continue
            if (x, y) == (0, 0):
                continue
            if (x, y) == (n, n):
                pass  # endpoint always allowed
            elif not (is_perfect_power(x) and is_perfect_power(y) and is_perfect_power(x+y)):
                continue
            
            if x > 0:
                dp[x][y] += dp[x-1][y]
            if y > 0:
                dp[x][y] += dp[x][y-1]
            if mod:
                dp[x][y] %= mod
    return dp[n][n]

# Formulation 2: admissible if x, y, x+y are all powers of 2
def is_pow2(x):
    return x > 0 and (x & (x-1)) == 0

def count_paths_pow2(n, mod=None):
    """Admissible: x, y, x+y all powers of 2"""
    dp = [[0] * (n + 1) for _ in range(n + 1)]
    dp[0][0] = 1
    for s in range(1, 2*n + 1):
        for x in range(max(0, s - n), min(n, s) + 1):
            y = s - x
            if x > n or y > n:
                continue
            if (x, y) == (0, 0):
                continue
            if (x, y) == (n, n):
                pass
            elif not (is_pow2(x) or x == 0) or not (is_pow2(y) or y == 0) or not is_pow2(x+y):
                if not (x == 0 or is_pow2(x)) or not (y == 0 or is_pow2(y)) or not is_pow2(x+y):
                    continue
            
            if x > 0:
                dp[x][y] += dp[x-1][y]
            if y > 0:
                dp[x][y] += dp[x][y-1]
            if mod:
                dp[x][y] %= mod
    return dp[n][n]

# Formulation 3: admissible if gcd(x,y)=1, BUT 0 is special
def count_paths_coprime(n, mod=None):
    dp = [[0] * (n + 1) for _ in range(n + 1)]
    dp[0][0] = 1
    for s in range(1, 2*n + 1):
        for x in range(max(0, s - n), min(n, s) + 1):
            y = s - x
            if x > n or y > n:
                continue
            if (x, y) == (0, 0):
                continue
            if (x, y) == (n, n):
                pass
            elif x == 0 or y == 0:
                pass  # axes always admissible
            elif math.gcd(x, y) != 1:
                continue
            
            if x > 0:
                dp[x][y] += dp[x-1][y]
            if y > 0:
                dp[x][y] += dp[x][y-1]
            if mod:
                dp[x][y] %= mod
    return dp[n][n]

# Test
for n in range(1, 15):
    c3 = count_paths_coprime(n)
    print(f"n={n}: coprime={c3}")

print("\n=== Trying powers of 2 ===")
for n in range(1, 10):
    c = count_paths_pow2(n)
    print(f"n={n}: {c}")

# Let me also check: maybe the answer is modulo 10^9+7?
print("\n=== Larger n with coprime, mod 10^9+7 ===")
MOD = 10**9 + 7
for n in [10, 20, 50, 100, 200]:
    print(f"n={n}: {count_paths_coprime(n, MOD)}")

# What if the answer is for n=10^8 or 10^7?
# 299742733 is less than 10^9, so maybe it IS the answer (not modular)
