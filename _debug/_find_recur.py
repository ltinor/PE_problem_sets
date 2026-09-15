C = [1, 1, 2, 4, 9, 20, 46, 105, 243, 561, 1301, 3014, 6995, 16227, 37668]

# Try order 2: C[n] = a*C[n-1] + b*C[n-2]
for s in range(len(C)-3):
    det = C[s+2]*C[s] - C[s+1]*C[s+1]
    if det == 0: continue
    a = (C[s+3]*C[s] - C[s+2]*C[s+1]) / det
    b = (C[s+2]*C[s+2] - C[s+3]*C[s+1]) / det
    if abs(a - round(a)) < 0.001 and abs(b - round(b)) < 0.001:
        ai, bi = round(a), round(b)
        ok = True
        for n in range(s+3, len(C)):
            if C[n] != ai*C[n-1] + bi*C[n-2]:
                ok = False; break
        if ok:
            print(f"Order 2: C[n] = {ai}*C[n-1] + {bi}*C[n-2]")

# Try order 3
for s in range(len(C)-6):
    rows = []
    for i in range(3):
        rows.append([C[s+i], C[s+1+i], C[s+2+i]])
    rhs = [C[s+3], C[s+4], C[s+5]]
    a,b,c = rows[0]
    d,e,f = rows[1]
    g,h,i = rows[2]
    det = a*(e*i-f*h) - b*(d*i-f*g) + c*(d*h-e*g)
    if det == 0: continue
    r1,r2,r3 = rhs
    d1 = r1*(e*i-f*h) - b*(r2*i-f*r3) + c*(r2*h-e*r3)
    d2 = a*(r2*i-f*r3) - r1*(d*i-f*g) + c*(d*r3-r2*g)
    d3 = a*(e*r3-r2*h) - b*(d*r3-r2*g) + r1*(d*h-e*g)
    p,q,r = d1/det, d2/det, d3/det
    if abs(p-round(p))<0.001 and abs(q-round(q))<0.001 and abs(r-round(r))<0.001:
        pi,qi,ri = round(p),round(q),round(r)
        ok = True
        for n in range(s+3, len(C)):
            if C[n] != pi*C[n-1] + qi*C[n-2] + ri*C[n-3]:
                ok = False; break
        if ok:
            print(f"Order 3: C[n] = {pi}*C[n-1] + {qi}*C[n-2] + {ri}*C[n-3]")
