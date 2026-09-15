"""Check if CN can be expressed as R[x] + C[y]"""
def check_rc_form(N):
    lo = (N-1)*(N-1)
    hi = N*N
    CN = [[0]*N for _ in range(N)]
    for x in range(N):
        for y in range(N):
            if lo <= x*x + y*y < hi:
                CN[x][y] = 1
    
    # Check: CN[x][y] = CN[x][0] ^ CN[0][y] ^ CN[0][0]
    ok = True
    for x in range(N):
        for y in range(N):
            expected = CN[x][0] ^ CN[0][y] ^ CN[0][0]
            if CN[x][y] != expected:
                if ok:
                    print(f"  First mismatch at x={x}, y={y}: CN={CN[x][y]}, expected={expected}")
                    ok = False
    return ok

for N in [3, 5, 7, 10, 15]:
    print(f"N={N}: RC-form solvable = {check_rc_form(N)}")
