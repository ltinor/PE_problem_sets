def is_similar(s1, s2):
    a = sorted(s1); b = sorted(s2)
    return a[0]*b[1] == a[1]*b[0] and a[1]*b[2] == a[2]*b[1]

def triangle_exists(a, b, d, u):
    v = a - u
    t1 = [(b-a)**2, 2*v*v, (b-u)**2 + v*v]
    t2 = [(d-a)**2, 2*u*u, u*u + (d-v)**2]
    t3 = [b*b + d*d, (b-u)**2 + v*v, u*u + (d-v)**2]
    return is_similar(t1, t2) and is_similar(t1, t3)

def count_brute(N):
    c = 0
    for a in range(1, N):
        for b in range(a+1, N):
            for d in range(a+1, N):
                if b + d >= N: break
                for u in range(1, a):
                    if triangle_exists(a, b, d, u):
                        c += 1
                        break
    return c

def count_cond2(N):
    c = 0
    for a in range(1, N):
        for b in range(a+1, N):
            for d in range(a+1, N):
                if b + d >= N: break
                alpha = b - a
                beta = d - a
                ok = False
                for u in range(1, a):
                    v = a - u
                    if alpha * beta == 2 * u * v and (u == v or alpha == beta):
                        ok = True
                        break
                if ok:
                    c += 1
    return c

for N in [10, 20, 50, 100, 200]:
    b = count_brute(N)
    c2 = count_cond2(N)
    print(N, b, c2, "OK" if b == c2 else "DIFF")
