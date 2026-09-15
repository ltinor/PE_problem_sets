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

# single A-pile p vs single B-pile q
print("A:[p] vs B:[q] -> A wins both?")
for p in range(0, 7):
    row = []
    for q in range(0, 7):
        if p==0 and q==0:
            row.append(" - ")
            continue
        A = (p,) if p>0 else ()
        B = (q,) if q>0 else ()
        row.append("W" if awin_both(A,B) else ".")
    print(p, " ".join(row))

print()
# Try to infer weight(k): for single piles, find threshold
# A:[p] alone (B empty) wins both iff p>=2
print("single A-pile p wins both:", [awin_both((p,),()) for p in range(1,7)])
print("single B-pile q: A wins both (should be all False):", [awin_both((),(q,)) for q in range(1,7)])
