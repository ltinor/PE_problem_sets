from fractions import Fraction
import sys
sys.setrecursionlimit(1000000)

memo = {}
def value(s):
    if s in memo:
        return memo[s]
    n = len(s)
    if n == 1:
        v = ('num', Fraction(1 if s == 'L' else -1))
        memo[s] = v
        return v
    Lopts = [value(s[k:]) for k in range(1, n)]
    Ropts = [value(s[:n-k]) for k in range(1, n)]
    def rep(v):
        return v[1] if v[0] == 'num' else v[1]  # mean for switch
    Lmax = max(rep(v) for v in Lopts)
    Rmin = min(rep(v) for v in Ropts)
    if Lmax <= Rmin:
        v = ('num', simplest(Lmax, Rmin))
    else:
        v = ('switch', Fraction(Lmax + Rmin, 2), Fraction(Lmax - Rmin, 2))
    memo[s] = v
    return v

def simplest(lo, hi):
    # simplest dyadic rational in [lo, hi]: smallest denominator, then smallest abs
    import math
    # integers first
    for d in [1, 2, 4, 8, 16, 32, 64, 128]:
        candidates = []
        for k in range(int(lo * d) - 1, int(hi * d) + 2):
            f = Fraction(k, d)
            if lo <= f <= hi:
                candidates.append(f)
        if candidates:
            # choose smallest |value|
            return min(candidates, key=lambda f: abs(f))
    raise ValueError

if __name__ == '__main__':
    for n in range(1, 6):
        from collections import defaultdict
        groups = defaultdict(list)
        for mask in range(1 << n):
            s = ''.join('R' if (mask >> i) & 1 else 'L' for i in range(n-1, -1, -1))
            v = value(s)
            key = v
            groups[key].append(s)
        print(f"=== n={n} ===")
        for key in sorted(groups, key=str):
            print(f"  {key}: {sorted(groups[key])}")
