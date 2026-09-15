import sys
from functools import lru_cache
from itertools import combinations_with_replacement, product
from math import factorial

sys.setrecursionlimit(1000000)

# Global memo: (sorted tuple of words, turn) -> winner (0=Left, 1=Right)
memo = {}

def outcome(words, turn):
    key = (tuple(sorted(words)), turn)
    if key in memo:
        return memo[key]
    # terminal
    if all(len(w) == 1 for w in words):
        L = sum(1 for w in words if w == 'L')
        R = sum(1 for w in words if w == 'R')
        res = 0 if L > R else 1
        memo[key] = res
        return res
    # build options per word
    opts = []
    for w in words:
        m = len(w)
        if m == 1:
            opts.append([w])
        elif turn == 0:  # Left: proper suffixes
            opts.append([w[k:] for k in range(1, m)] + [w])
        else:  # Right: proper prefixes
            opts.append([w[:m-k] for k in range(1, m)] + [w])
    target = 0 if turn == 0 else 1
    # iterate product, exclude all-unchanged
    for combo in product(*opts):
        if combo == tuple(words):
            continue
        sub = outcome(list(combo), 1 - turn)
        if sub == target:
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
        if outcome(list(combo), 0) == 1:  # Right wins
            # multinomial count of distinct orderings
            from collections import Counter
            c = Counter(combo)
            ways = factorial(k)
            for v in c.values():
                ways //= factorial(v)
            cnt += ways
    return cnt

if __name__ == '__main__':
    print("G(2,3) =", G(2,3), "(expected 14)")
    print("G(3,3) =", G(3,3))
    print("G(4,3) =", G(4,3), "(expected 496)")
