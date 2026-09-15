#!/usr/bin/env python3
"""PE 924: Larger Digit Permutation II - analyze a_n = a_{n-1}^2 + 2"""
MOD = 10**9 + 7

def B(n):
    """Smallest number > n formed by rearranging digits of n, or 0"""
    s = list(str(n))
    # Find next permutation
    # Find the rightmost digit that is smaller than some digit to its right
    i = len(s) - 2
    while i >= 0 and s[i] >= s[i+1]:
        i -= 1
    if i < 0:
        return 0
    # Find smallest digit to the right of i that is larger than s[i]
    j = len(s) - 1
    while s[j] <= s[i]:
        j -= 1
    # Swap
    s[i], s[j] = s[j], s[i]
    # Reverse the suffix
    s[i+1:] = reversed(s[i+1:])
    return int(''.join(s))

# Compute a_n
a = [0]
for n in range(1, 20):
    a.append(a[-1]**2 + 2)

print("First few a_n and B(a_n):")
for n in range(1, min(15, len(a))):
    an = a[n]
    bn = B(an)
    print(f"n={n}: a_n={an} (digits: {len(str(an))}), B(a_n)={bn}")

# Try to compute U(10) mod MOD
total = 0
for n in range(1, 11):
    total = (total + B(a[n])) % MOD
print(f"\nU(10) mod MOD = {total}")
print(f"Expected: 543870437")

# For large N, a_n grows very fast. Let's see when a_n exceeds Python's limits.
# At n=6, a_n has 13 digits. At n=7, ~25 digits. At n=8, ~50 digits.
# At n=12, ~800 digits. At n=16, ~25600 digits.
# By n=20, a_n has millions of digits, impractical.
# But we need up to N=10^16. 

# Key insight: For large n, B(a_n) depends on the digit multiset of a_n.
# If the digits are in descending order, B(a_n) = 0.
# For large random-like numbers, digits are rarely in descending order.
# But a_n are specific numbers: a_n = a_{n-1}^2 + 2

# Let me check more values of a_n for patterns
