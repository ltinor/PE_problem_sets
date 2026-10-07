import sys
from functools import lru_cache
sys.setrecursionlimit(1000000)

memo = {}
def outcome(A, B, turn):
    key = (A, B, turn)
    if key in memo:
        return memo[key]
    if sum(A)+sum(B) == 0:
        res = (turn == 1)
        memo[key] = res
        return res
    if turn == 0:
        for i, v in enumerate(B):
            if v > 0:
                nb = list(B); nb[i]-=1; nb = tuple(sorted(x for x in nb if x>0))
                if outcome(A, nb, 1): memo[key]=True; return True
        for i, v in enumerate(A):
            na = list(A); na[i]=0; na = tuple(sorted(x for x in na if x>0))
            if outcome(na, B, 1): memo[key]=True; return True
        memo[key]=False; return False
    else:
        for i, v in enumerate(A):
            if v > 0:
                na = list(A); na[i]-=1; na = tuple(sorted(x for x in na if x>0))
                if not outcome(na, B, 0): memo[key]=False; return False
        for i, v in enumerate(B):
            nb = list(B); nb[i]=0; nb = tuple(sorted(x for x in nb if x>0))
            if not outcome(A, nb, 0): memo[key]=False; return False
        memo[key]=True; return True

def awin_both(A, B):
    return outcome(A, B, 0) and outcome(A, B, 1)

def partitions(n, maxpart=None):
    if maxpart is None or maxpart > n: maxpart = n
    if n == 0:
        yield (); return
    for first in range(maxpart, 0, -1):
        for rest in partitions(n-first, first):
            yield (first,)+rest

def E(N):
    cnt = 0
    for total in range(0, N+1):
        for sa in range(0, total+1):
            sb = total - sa
            for pa in partitions(sa):
                for pb in partitions(sb):
                    if awin_both(pa, pb):
                        cnt += 1
    return cnt

for N in [9, 10]:
    print(f"E({N}) = {E(N)}")
