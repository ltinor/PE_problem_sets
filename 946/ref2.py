from fractions import Fraction
from decimal import Decimal, getcontext

getcontext().prec = 300

def primes_up_to(limit):
    isp = [True]*(limit+1)
    isp[0]=isp[1]=False
    for i in range(2, limit+1):
        if isp[i]:
            for j in range(i*i, limit+1, i):
                isp[j]=False
    return [i for i in range(2, limit+1) if isp[i]]

def alpha_terms(num):
    yield 2
    primes = primes_up_to(20000)
    for p in primes:
        for _ in range(p):
            yield 1
        yield 2

# Build alpha's CF terms list (enough, say 2000 terms)
terms = []
g = alpha_terms(10**9)
for _ in range(2000):
    terms.append(next(g))

# Compute alpha via convergent recurrence (exact Fraction) using ALL 2000 terms
# Convergent recurrence:
# p_{-2}=0,p_{-1}=1 ; q_{-2}=1,q_{-1}=0
# p_n = a_n p_{n-1} + p_{n-2}
# q_n = a_n q_{n-1} + q_{n-2}
def cf_to_fraction(terms):
    p0, p1 = 0, 1
    q0, q1 = 1, 0
    for a in terms:
        p2 = a*p1 + p0
        q2 = a*q1 + q0
        p0, p1 = p1, p2
        q0, q1 = q1, q2
    return Fraction(p1, q1)

alpha = cf_to_fraction(terms)
beta = (2*alpha + 3)/(3*alpha + 2)
print("beta approx:", float(beta))

# extract CF of beta (exact, since beta is a Fraction)
out = []
x = beta
for _ in range(60):
    q = x.numerator // x.denominator
    out.append(q)
    rem = x - q
    if rem == 0:
        break
    x = 1/rem

print("beta CF (exact via truncated alpha):")
print(out)
print("sum first 10:", sum(out[:10]))
print("sum first 20:", sum(out[:20]))
print("sum first 50:", sum(out[:50]))
print("sum first 60:", sum(out[:60]))
