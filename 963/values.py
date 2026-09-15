import sys
from fractions import Fraction
from functools import lru_cache

def tern(n):
    if n == 0:
        return "0"
    s = ""
    while n:
        s = str(n % 3) + s
        n //= 3
    return s

def remove_digit(n, d):
    """numbers reachable by removing one digit == d (char) from ternary(n)"""
    s = tern(n)
    L = len(s)
    res = set()
    for i in range(L):
        if s[i] != d:
            continue
        t = s[:i] + s[i+1:]
        if t == "":
            continue
        # leading zeros?
        if t[0] == '0':
            # invalid move? strip? -> test
            continue
        res.add(int(t, 3))
    return res

# simplest number in (lo, hi), lo < hi, using surreal "simplest" rule
def simplest(lo, hi):
    # integers/numbers: find simplest number strictly between lo and hi
    # try integers from 0 outward
    lo = Fraction(lo); hi = Fraction(hi)
    # simplest = integer if any integer in (lo,hi)
    import math
    # candidates: integer part
    for k in range(-20, 21):
        if lo < Fraction(k) < hi:
            return Fraction(k)
    # dyadic rationals with smallest denominator 2^m
    for m in range(1, 20):
        den = 2**m
        # numbers with denominator den: (2j+1)/den
        for j in range(-20*den, 20*den):
            f = Fraction(2*j+1, den)
            if lo < f < hi:
                return f
    return None

@lru_cache(maxsize=None)
def G(n):
    L = set()
    R = set()
    for x in remove_digit(n, '0'):
        L.add(G(x))
    for x in remove_digit(n, '2'):
        L.add(G(x))
    for x in remove_digit(n, '1'):
        R.add(G(x))
    for x in remove_digit(n, '2'):
        R.add(G(x))
    if not L and not R:
        return Fraction(0)
    # number check: max(L) < min(R)
    Lmax = max(L) if L else None
    Rmin = min(R) if R else None
    if Lmax is None:
        # only right options: value = simplest < Rmin = Rmin - 1 (integer)
        return Fraction(Rmin - 1)
    if Rmin is None:
        return Fraction(Lmax + 1)
    if Lmax >= Rmin:
        return None  # not a number (this would be surprising)
    return simplest(Lmax, Rmin)

if __name__ == "__main__":
    for n in range(0, 21):
        v = G(n)
        print(f"G({n}) = {v}   tern={tern(n)}")
