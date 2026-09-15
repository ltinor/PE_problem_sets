from fractions import Fraction

def primes_up_to(limit):
    isp = [True]*(limit+1)
    isp[0]=isp[1]=False
    for i in range(2, limit+1):
        if isp[i]:
            for j in range(i*i, limit+1, i):
                isp[j]=False
    return [i for i in range(2, limit+1) if isp[i]]

def alpha_terms():
    yield 2
    primes = primes_up_to(100000)
    for p in primes:
        for _ in range(p):
            yield 1
        yield 2

def gosper(M, terms, num_out):
    a,b = M[0]
    c,d = M[1]
    out = []
    it = terms
    def ingest():
        nonlocal a,b,c,d
        x = next(it)
        a,b,c,d = a*x+b, a, c*x+d, c
    while len(out) < num_out:
        if c == 0 and d == 0:
            break
        if c == 0 or d == 0:
            ingest()
            continue
        q1 = a//c
        q2 = b//d
        if q1 == q2:
            out.append(q1)
            a,b,c,d = c,d, a-q1*c, b-q1*d
        else:
            ingest()
    return out

M = [[2,3],[3,2]]
out = gosper(M, alpha_terms(), 120)
print("first 120 terms of beta (Gosper):")
print(out)
print("sum first 10:", sum(out[:10]))
print("sum first 20:", sum(out[:20]))
print("sum first 50:", sum(out[:50]))
print("sum first 100:", sum(out[:100]))
