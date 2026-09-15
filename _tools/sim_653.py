#!/usr/bin/env python3
"""PE 653: Simulate small test case carefully."""
L, R, v = 5000, 10, 1.0
N = 3
x = [127.0, 579.0, 772.0]
d = [1, -1, -1]  # +1 east, -1 west
total_dist = [0.0, 0.0, 0.0]
exited = [False, False, False]

t = 0.0
while not all(exited):
    # Find next event
    next_t = float('inf')
    next_type = None
    next_i = -1
    next_j = -1
    
    for i in range(N):
        if exited[i]:
            continue
        # Wall bounce (west, sealed)
        if d[i] == -1:
            tw = (x[i] - R) / v
            if tw > 1e-12 and tw < next_t - 1e-12:
                next_t = tw
                next_type = 'wall'
                next_i = i
        # Exit (east)
        te = (L - x[i]) / v
        if te > 1e-12 and te < next_t - 1e-12:
            next_t = te
            next_type = 'exit'
            next_i = i
    
    # Collisions: only between adjacent in x-order
    active = [(x[i], i) for i in range(N) if not exited[i]]
    active.sort()
    for k in range(len(active) - 1):
        i = active[k][1]
        j = active[k+1][1]
        if d[i] == 1 and d[j] == -1:  # approaching
            tc = (x[j] - x[i] - 2*R) / (2*v)
            if tc > 1e-12 and tc < next_t - 1e-12:
                next_t = tc
                next_type = 'collision'
                next_i = i
                next_j = j
    
    if next_t == float('inf'):
        break
    
    # Advance all
    dt = next_t
    for i in range(N):
        if not exited[i]:
            x[i] += d[i] * v * dt
            total_dist[i] += v * dt
    
    t += dt
    
    if next_type == 'collision':
        d[next_i] *= -1
        d[next_j] *= -1
        #print(f"t={t:.2f}: collision M{next_i+1}(x={x[next_i]:.1f}) ↔ M{next_j+1}(x={x[next_j]:.1f})")
    elif next_type == 'wall':
        d[next_i] *= -1
        #print(f"t={t:.2f}: M{next_i+1} bounce at wall, x={x[next_i]:.1f}")
    elif next_type == 'exit':
        exited[next_i] = True
        print(f"t={t:.2f}: M{next_i+1} EXIT, distance={total_dist[next_i]:.1f}")

print(f"\nFinal distances: {[f'{d:.1f}' for d in total_dist]}")
print(f"Expected d(5000,3,2)=5519")
