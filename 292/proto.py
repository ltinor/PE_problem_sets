import sys
from math import gcd, isqrt

def gen_directions(N):
    # returns list of (a,b,c) primitive directions with a^2+b^2=c^2, c<=N,
    # plus axis directions (1,0),(0,1),(-1,0),(0,-1) with c=1
    dirs = []
    seen = set()
    # axis directions
    for (a,b) in [(1,0),(-1,0),(0,1),(0,-1)]:
        dirs.append((a,b,1))
        seen.add((a,b))
    # primitive pythagorean triples a^2+b^2=c^2, 0<a<b, c<=N
    for a in range(1, N+1):
        for b in range(a+1, N+1):
            c2 = a*a + b*b
            c = isqrt(c2)
            if c*c == c2 and c <= N:
                if gcd(a,b) == 1:
                    # 8 sign/swap combos
                    for (x,y) in [(a,b),(a,-b),(-a,b),(-a,-b),(b,a),(b,-a),(-b,a),(-b,-a)]:
                        if (x,y) not in seen:
                            dirs.append((x,y,c))
                            seen.add((x,y))
    return dirs

def P(N):
    dirs = gen_directions(N)
    # DP: dict (x,y,p) -> count, x,y in [-N,N], p in [0,N]
    from collections import defaultdict
    dp = defaultdict(int)
    dp[(0,0,0)] = 1
    for (a,b,c) in dirs:
        ndp = dict(dp)  # skip
        maxk = N // c
        for (x,y,p), cnt in dp.items():
            for k in range(1, maxk+1):
                nx, ny, np_ = x + k*a, y + k*b, p + k*c
                if np_ <= N and abs(nx) <= N and abs(ny) <= N:
                    ndp[(nx,ny,np_)] += cnt
        dp = ndp
    # S(N) = sum over p=1..N of count[(0,0,p)]
    S = sum(cnt for (x,y,p), cnt in dp.items() if x==0 and y==0 and 1<=p<=N)
    # segments: pairs of opposite directions {u,-u}
    seg = 0
    # axis pairs
    seg += 2 * (N // 2)  # {(1,0),(-1,0)} and {(0,1),(0,-1)}
    # triple pairs: 4 opposite pairs per triple, each primitive length c
    pairs = set()
    for (a,b,c) in dirs:
        if c == 1:
            continue
        opp = (-a,-b)
        key = tuple(sorted([(a,b),opp]))
        if key in pairs:
            continue
        pairs.add(key)
        seg += (N // (2*c))
    return S - seg

for N in [4, 30, 60]:
    print(N, P(N))
