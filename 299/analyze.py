def is_similar(s1, s2):
    a = sorted(s1); b = sorted(s2)
    return a[0]*b[1] == a[1]*b[0] and a[1]*b[2] == a[2]*b[1]

def triangle_exists(a, b, d, u):
    v = a - u
    t1 = [(b-a)**2, 2*v*v, (b-u)**2 + v*v]
    t2 = [(d-a)**2, 2*u*u, u*u + (d-v)**2]
    t3 = [b*b + d*d, (b-u)**2 + v*v, u*u + (d-v)**2]
    return is_similar(t1, t2) and is_similar(t1, t3)

N = 200
from math import gcd
rows = []
for a in range(1, N):
    for b in range(a+1, N):
        for d in range(a+1, N):
            if b + d >= N: break
            for u in range(1, a):
                if triangle_exists(a, b, d, u):
                    v = a - u
                    alpha = b - a
                    beta = d - a
                    g = gcd(u, v)
                    rows.append((a, b, d, u, v, alpha, beta))
                    break

print("count N=200:", len(rows))
# print families where u==v
print("--- u==v cases ---")
for r in rows:
    if r[3] == r[4]:
        print(r)
