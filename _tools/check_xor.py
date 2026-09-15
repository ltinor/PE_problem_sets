"""Check XOR model (CN = R ⊕ C only) for various N"""
import math

def compute_CN(N):
    lo = (N-1)*(N-1)
    hi = N*N
    CN = {}
    for x in range(N):
        for y in range(N):
            if lo <= x*x + y*y < hi:
                CN[(x,y)] = 1
    return CN

def check_xor_model(N):
    CN = compute_CN(N)
    c00 = CN.get((0,0), 0)
    for x in range(N):
        for y in range(N):
            expected = CN.get((x,0), 0) ^ CN.get((0,y), 0) ^ c00
            if CN.get((x,y), 0) != expected:
                return False
    return True

def check_xor_model_smart(N):
    """More efficient check"""
    c00 = 1 if (N-1)*(N-1) <= 0 < N*N else 0  # (0,0): sqrt(0)=0, for N>1: always 0
    
    for x in range(N):
        cx0 = 1 if (N-1)*(N-1) <= x*x < N*N else 0
        for y in range(N):
            c0y = 1 if (N-1)*(N-1) <= y*y < N*N else 0
            cxy = 1 if (N-1)*(N-1) <= x*x + y*y < N*N else 0
            if cxy != (cx0 ^ c0y ^ c00):
                return False
    return True

for N in [3, 5, 7, 10, 15]:
    print(f"N={N}: XOR model = {check_xor_model_smart(N)}")

# For N=2^k-1:
for k in range(2, 10):
    N = (1 << k) - 1
    result = check_xor_model_smart(N)
    print(f"k={k}, N={N}: XOR model = {result}")
