from itertools import combinations_with_replacement
from functools import lru_cache
import sys
sys.setrecursionlimit(100000)

def tern(n):
    if n == 0: return "0"
    s = ""
    while n:
        s = str(n % 3) + s
        n //= 3
    return s

def build_removals(N):
    """rem[d][x] = set of numbers reachable from x by removing one trit == d"""
    rem = {'0':[[] for _ in range(N+1)], '1':[[] for _ in range(N+1)], '2':[[] for _ in range(N+1)]}
    for x in range(N+1):
        s = tern(x)
        L = len(s)
        for i in range(L):
            d = s[i]
            t = s[:i] + s[i+1:]
            if t == "":
                r = 0
            else:
                t = t.lstrip('0') or "0"
                r = int(t, 3)
            if r != x:
                if r not in rem[d][x]:
                    rem[d][x].append(r)
    return rem

def make_F(N):
    rem = build_removals(N)
    @lru_cache(maxsize=None)
    def win(a,b,c,d,turn):
        own = (a,b) if turn==0 else (c,d)
        opp = (c,d) if turn==0 else (a,b)
        # own numbers: remove 0 (rem['0']) and 2 (rem['2'])
        for idx, x in enumerate(own):
            for r in rem['0'][x]:
                nxt = (r,b,c,d) if (turn==0 and idx==0) else ((a,r,c,d) if (turn==0 and idx==1) else ((a,b,r,d) if (turn==1 and idx==0) else (a,b,c,r)))
                if not win(*nxt, 1-turn): return True
            for r in rem['2'][x]:
                nxt = (r,b,c,d) if (turn==0 and idx==0) else ((a,r,c,d) if (turn==0 and idx==1) else ((a,b,r,d) if (turn==1 and idx==0) else (a,b,c,r)))
                if not win(*nxt, 1-turn): return True
        # opp numbers: remove 1 (rem['1']) and 2 (rem['2'])
        for idx, x in enumerate(opp):
            for r in rem['1'][x]:
                nxt = (a,b,r,d) if (turn==0 and idx==0) else ((a,b,c,r) if (turn==0 and idx==1) else ((r,b,c,d) if (turn==1 and idx==0) else (a,r,c,d)))
                if not win(*nxt, 1-turn): return True
            for r in rem['2'][x]:
                nxt = (a,b,r,d) if (turn==0 and idx==0) else ((a,b,c,r) if (turn==0 and idx==1) else ((r,b,c,d) if (turn==1 and idx==0) else (a,r,c,d)))
                if not win(*nxt, 1-turn): return True
        return False

    def F(N):
        nums = list(range(1, N+1))
        pairs = list(combinations_with_replacement(nums, 2))
        cnt = 0
        for (a,b) in pairs:
            for (c,d) in pairs:
                if (not win(a,b,c,d,0)) and (not win(a,b,c,d,1)):
                    cnt += 1
        return cnt
    return F

for N in range(1, 16):
    F = make_F(N)
    print(f"F({N}) = {F(N)}")
