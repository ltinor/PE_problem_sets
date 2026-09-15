C = [1, 1, 2, 4, 9, 20, 46, 105, 243, 561, 1301, 3014, 6995, 16227, 37668]

def solve_order_k(k, start):
    """Try to fit order-k recurrence from terms starting at 'start'."""
    # Build matrix A (k x k) where A[i][j] = C[start + i + j]
    A = [[C[start + i + j] for j in range(k)] for i in range(k)]
    b = [C[start + k + i] for i in range(k)]
    
    # Gaussian elimination
    n = k
    M = [row[:] + [b[i]] for i, row in enumerate(A)]
    
    for col in range(n):
        # Find pivot
        pivot = None
        for row in range(col, n):
            if abs(M[row][col]) > 1e-9:
                pivot = row; break
        if pivot is None: return None
        M[col], M[pivot] = M[pivot], M[col]
        
        piv_val = M[col][col]
        for j in range(col, n+1):
            M[col][j] /= piv_val
        
        for row in range(n):
            if row != col and abs(M[row][col]) > 1e-9:
                factor = M[row][col]
                for j in range(col, n+1):
                    M[row][j] -= factor * M[col][j]
    
    sol = [M[i][n] for i in range(n)]
    return sol

for order in range(2, 6):
    print(f"Order {order}:")
    for s in range(len(C) - 2*order + 1):
        sol = solve_order_k(order, s)
        if sol is None: continue
        sol_round = [round(x) for x in sol]
        if all(abs(sol[i] - sol_round[i]) < 0.01 for i in range(order)):
            ok = True
            for n in range(s + order, len(C)):
                pred = sum(sol_round[j] * C[n - order + j] for j in range(order))
                if pred != C[n]:
                    ok = False; break
            if ok:
                terms = " + ".join(f"{c}*C[n-{order-j}]" for j,c in enumerate(sol_round))
                print(f"  C[n] = {terms}")
