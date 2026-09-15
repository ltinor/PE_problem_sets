import sys
from functools import lru_cache
from itertools import combinations_with_replacement, product
from math import factorial
from collections import Counter

sys.setrecursionlimit(1000000)
memo = {}

def outcome(words, turn):
    key = (tuple(sorted(words)), turn)
    if key in memo:
        return memo[key]
    if all(len(w) == 1 for w in words):
        L = sum(1 for w in words if w == 'L')
        R = sum(1 for w in words if w == 'R')
        res = 0 if L > R else 1
        memo[key] = res
        return res
    opts = []
    for w in words:
        m = len(w)
        if m == 1:
            opts.append([w])
        elif turn == 0:
            opts.append([w[k:] for k in range(1, m)] + [w])
        else:
            opts.append([w[:m-k] for k in range(1, m)] + [w])
    target = 0 if turn == 0 else 1
    for combo in product(*opts):
        if combo == tuple(words):
            continue
        if outcome(list(combo), 1 - turn) == target:
            memo[key] = target
            return target
    memo[key] = 1 - target
    return 1 - target

def G(n, k):
    words = []
    for mask in range(1 << n):
        w = ''.join('R' if (mask >> i) & 1 else 'L' for i in range(n-1, -1, -1))
        words.append(w)
    cnt = 0
    for combo in combinations_with_replacement(words, k):
        if outcome(list(combo), 0) == 1:
            c = Counter(combo)
            ways = factorial(k)
            for v in c.values():
                ways //= factorial(v)
            cnt += ways
    return cnt

if __name__ == '__main__':
    for k in (1, 3, 5):
        row = []
        for n in range(1, 6):
            g = G(n, k)
            total = (1 << n) ** k
            row.append((n, g, total))
        print(f"k={k}:")
        for n, g, t in row:
            print(f"  G({n},{k}) = {g}  (total {t})")
