# Search for all solutions to g(n) = n up to 10^12
# Using signature-based computation

from collections import defaultdict
from functools import lru_cache
import math

# g for a signature = tuple of exponents (sorted descending)
@lru_cache(maxsize=None)
def g_sig(sig):
    if not sig or sig == (0,):
        return 1
    sig = tuple(sorted([e for e in sig if e > 0], reverse=True))
    if not sig:
        return 1
    # Sum over all proper divisor signatures
    total = 0
    r = len(sig)
    # Generate all tuples (a_1,...,a_r) with 0 <= a_i <= sig[i], not all equal to sig
    def dfs(idx, current):
        nonlocal total
        if idx == r:
            if current != sig:
                total += g_sig(tuple(current))
            return
        for a in range(sig[idx] + 1):
            current.append(a)
            dfs(idx + 1, current)
            current.pop()
    dfs(0, [])
    return total

# Precompute g for small signatures
print("Precomputing g for small signatures...")
sig_values = {}
for max_e in range(0, 8):
    for e1 in range(max_e + 1):
        sig = tuple(sorted([e1], reverse=True))
        sig_values[sig] = g_sig(sig)
        for e2 in range(max_e + 1):
            sig = tuple(sorted([e1, e2], reverse=True))
            sig_values[sig] = g_sig(sig)
            for e3 in range(max_e + 1):
                sig = tuple(sorted([e1, e2, e3], reverse=True))
                sig_values[sig] = g_sig(sig)

print(f"Precomputed {len(sig_values)} signatures")

# Now search for n where g(n) = n
# Generate numbers using primes 2,3,5,7,11,13,17,19,23,29,31,37
primes = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47]
LIMIT = 10**12

solutions = []

def search(idx, current_n, exponents, min_exp):
    global solutions
    if current_n > LIMIT:
        return
    if idx >= len(primes):
        return
    
    # Try adding this prime with various exponents
    p = primes[idx]
    
    # Option: skip this prime (exponent 0)
    search(idx + 1, current_n, exponents, 0)
    
    # Option: use this prime with exponent e >= 1
    e = 1
    while True:
        new_n = current_n * (p ** e)
        if new_n > LIMIT:
            break
        
        new_exp = exponents + [e]
        sig = tuple(sorted(new_exp, reverse=True))
        
        # Compute or look up g
        if sig in sig_values:
            g_val = sig_values[sig]
        else:
            g_val = g_sig(sig)
            sig_values[sig] = g_val
        
        if g_val == new_n:
            solutions.append((new_n, sig, g_val))
            print(f"FOUND: n={new_n}, sig={sig}, g={g_val}")
        
        search(idx + 1, new_n, new_exp, e)
        
        e += 1
        # Prune: p^e alone exceeds limit
        if p ** (e + 1) > LIMIT:
            break

print(f"Searching up to {LIMIT}...")
search(0, 1, [], 0)

print(f"\nTotal solutions: {len(solutions)}")
solutions.sort()
for n, sig, g in solutions:
    print(f"  n={n:>15}, sig={sig}")

# Also check known solutions
print("\nChecking specific patterns:")
# Family: 2^{4k} * p_k
odd_primes = primes[1:]  # skip 2
for k in range(1, 20):
    two_pow = 2 ** (4 * k)
    if k <= len(odd_primes):
        n = two_pow * odd_primes[k-1]
        if n <= LIMIT:
            sig = (4*k, 1)
            gv = g_sig(sig)
            if gv == n:
                print(f"  Family 1: k={k}, n=2^{4*k}*{odd_primes[k-1]}={n}, g={gv}, match=True")
