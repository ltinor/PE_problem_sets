import math

MOD = 10**9 + 7

def popcount(x):
    return bin(x).count('1')

def is_prime(n):
    if n < 2: return False
    i = 2
    while i*i <= n:
        if n % i == 0: return False
        i += 1
    return True

def v_p(k, p):
    s = 0
    q = p
    while q <= k:
        s += k // q
        q *= p
    return s

def parity_k(k):
    par = popcount(v_p(k, 2)) & 1
    for p in range(3, k+1):
        if p % 8 in (5, 7) and is_prime(p):
            par ^= popcount(v_p(k, p)) & 1
    return par

chi = []
for k in range(1, 61):
    chi.append('A' if parity_k(k) == 0 else 'B')

# print in rows of 20
for i in range(0, 60, 20):
    row = ''.join(chi[i:i+20])
    print(f"k={i+1:3d}..{i+20:3d}: {row}")

# print k where in A
A_ks = [k+1 for k in range(60) if chi[k]=='A']
print("k in A:", A_ks)
