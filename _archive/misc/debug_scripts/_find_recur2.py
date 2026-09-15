C = [1, 1, 2, 4, 9, 20, 46, 105, 243, 561, 1301, 3014, 6995, 16227, 37668]

def cramer3(A, b):
    a,b,c = A[0]; d,e,f = A[1]; g,h,i = A[2]
    r1,r2,r3 = b
    det = a*(e*i-f*h) - b*(d*i-f*g) + c*(d*h-e*g)
    if det == 0: return None
    d1 = r1*(e*i-f*h) - b*(r2*i-f*r3) + c*(r2*h-e*r3)
    d2 = a*(r2*i-f*r3) - r1*(d*i-f*g) + c*(d*r3-r2*g)
    d3 = a*(e*r3-r2*h) - b*(d*r3-r2*g) + r1*(d*h-e*g)
    return (d1/det, d2/det, d3/det)

# Try orders 2-5
for order in range(2, 6):
    print(f"\nOrder {order}:")
    for s in range(len(C) - 2*order + 1):
        A = [[C[s+i+j] for j in range(order)] for i in range(order)]
        b = [C[s+order+i] for i in range(order)]
        if order == 2:
            det = A[0][0]*A[1][1] - A[0][1]*A[1][0]
            if det == 0: continue
            a1 = (b[0]*A[1][1] - A[0][1]*b[1]) / det
            a2 = (A[0][0]*b[1] - b[0]*A[1][0]) / det
            sol = (a1, a2)
        elif order == 3:
            sol = cramer3(A, b)
        else:
            continue  # skip for now
        
        if sol is None: continue
        sol_round = tuple(round(x) for x in sol)
        if all(abs(sol[i]-sol_round[i]) < 0.001 for i in range(order)):
            ok = True
            for n in range(s+order, len(C)):
                pred = sum(sol_round[j] * C[n-order+j] for j in range(order))
                if pred != C[n]:
                    ok = False; break
            if ok:
                print(f"  Found: C[n] = " + " + ".join(f"{c}*C[n-{order-j}]" for j,c in enumerate(sol_round)))
