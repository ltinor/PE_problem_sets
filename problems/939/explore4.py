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

def outclass(A, B):
    # returns L, R, N, P
    af = outcome(A, B, 0)  # A wins moving first
    bf = outcome(A, B, 1)  # A wins when B moves first
    if af and bf: return 'L'
    if af and not bf: return 'N'
    if not af and bf: return 'P'
    return 'R'

def P(A, B):
    return outclass(A,B)

# Test a_3 - a_2 etc.
for p in range(1,7):
    for q in range(1,7):
        A = (p,) if p>0 else ()
        B = (q,) if q>0 else ()
        print(f"a_{p} - a_{q}  (A=[{p}],B=[{q}]) = {outclass(A,B)}")
    print()
