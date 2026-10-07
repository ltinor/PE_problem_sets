from fractions import Fraction as Fr
from math import gcd
import sys

Q = int(sys.argv[1]) if len(sys.argv) > 1 else 3000
amb = []
char_cnt = 0
import time
t0 = time.time()
for q in range(102, Q+1):
    if q % 500 == 0: print(f'  q={q} elapsed={time.time()-t0:.0f}s amb={len(amb)}', flush=True)
    pmax = (q - 1) // 100
    inv = None
    for p in range(1, pmax + 1):
        if gcd(p, q) != 1: continue
        inv = pow(p, -1, q)
        below = []
        b = inv
        while b <= Q:
            a = (p*b - 1) // q
            h = p*b - a*q
            below.append((b, a, h))
            b += q
        above = []
        d0 = q - inv
        while d0 <= Q:
            c = (p*d0 + 1) // q
            h = c*q - p*d0
            above.append((d0, c, h))
            d0 += q
        ib = ia = 0
        found = False
        while ib < len(below) and ia < len(above) and not found:
            nxt = min(below[ib][0], above[ia][0])
            while ib + 1 < len(below) and below[ib+1][0] <= nxt: ib += 1
            while ia + 1 < len(above) and above[ia+1][0] <= nxt: ia += 1
            bb, aa, hb = below[ib]
            dd, cc, hd = above[ia]
            if hb * dd == hd * bb:
                amb.append((p, q, bb, aa, dd, cc, hb, hd))
                found = True
        # 特征: p 奇 q 偶 因子拆分
        if p % 2 == 1 and q % 2 == 0:
            A = (p - 1) // 2; B = (p + 1) // 2
            dA = [i for i in range(1, A+1) if A % i == 0] if A > 0 else list(range(1, Q+1))
            dB = [i for i in range(1, B+1) if B % i == 0]
            for dd in dA:
                for bb in dB:
                    qq = dd * bb
                    if qq % 2 == 0 and 100*p < qq <= Q:
                        char_cnt += 1
                        break
print(f'Q={Q}: true brute={len(amb)}, characterization={char_cnt}')
for a in amb[:15]:
    p, q, bb, aa, dd, cc, hb, hd = a
    print(f'  x={p}/{q} 邻居 {bb}/{aa} {dd}/{cc} h=({hb},{hd}) d0={min(bb,dd)}')
