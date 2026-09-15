def primes_up_to(limit):
    isp = [True]*(limit+1)
    isp[0]=isp[1]=False
    for i in range(2, limit+1):
        if isp[i]:
            for j in range(i*i, limit+1, i):
                isp[j]=False
    return [i for i in range(2, limit+1) if isp[i]]

def alpha_gen(primes):
    yield 2
    for p in primes:
        for _ in range(p):
            yield 1
        yield 2

def run(n):
    primes = primes_up_to(5000000)
    it = alpha_gen(primes)
    a,b = 2,3
    c,d = 3,2
    out = 0
    alpha_consumed = 0
    maxval = 0
    maxq = 0
    def ingest():
        nonlocal a,b,c,d, alpha_consumed
        x = next(it)
        alpha_consumed += 1
        a,b,c,d = a*x+b, a, c*x+d, c
    while out < n:
        if c == 0 and d == 0:
            break
        if c == 0 or d == 0:
            ingest()
            continue
        q1 = a//c
        q2 = b//d
        if q1 == q2:
            out += 1
            maxq = max(maxq, q1)
            a,b,c,d = c,d, a-q1*c, b-q1*d
        else:
            ingest()
        maxval = max(maxval, max(a,b,c,d))
    return out, alpha_consumed, maxval, maxq

for n in [10, 100, 1000, 10000, 100000, 1000000]:
    out, ac, mv, mq = run(n)
    print(f"n={n}: alpha_consumed={ac}, max_state_val={mv}, max_q={mq}")
