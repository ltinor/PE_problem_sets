#!/usr/bin/env python3
"""PE 653: Efficient simulation using event-based approach with O(N log N).

Key: Marbles preserve order. Process from right to left?
Actually, for identical marbles, the exit time of marble j is the time
when the j-th smallest position among 'free' trajectories reaches L.

But this doesn't account for the radius. Let me brute-force simulate
small N and compare with free trajectory approach.
"""
R = 10

def simulate(L, N, j):
    """Event-based simulation."""
    MOD_PRNG = 32745673
    r = 6563116
    x = []
    d = []
    
    for i in range(N):
        gap = (r % 1000) + 1
        if i == 0:
            xi = gap + R
        else:
            xi = x[-1] + R + gap + R
        x.append(float(xi))
        d.append(1 if r <= 10000000 else -1)
        r = (r * r) % MOD_PRNG
    
    total_dist = [0.0] * N
    exited = [False] * N
    t = 0.0
    v = 1.0
    
    while not all(exited):
        next_dt = float('inf')
        next_type = None
        next_i = -1
        next_j = -1
        
        for i in range(N):
            if exited[i]: continue
            # Wall bounce
            if d[i] == -1:
                tw = (x[i] - R) / v
                if tw > 1e-12 and tw < next_dt - 1e-12:
                    next_dt = tw; next_type = 'wall'; next_i = i
            # Exit
            te = (L - x[i]) / v
            if te > 1e-12 and te < next_dt - 1e-12:
                next_dt = te; next_type = 'exit'; next_i = i
        
        # Collisions (only adjacent in x-order)
        active = [(x[i], i) for i in range(N) if not exited[i]]
        active.sort()
        for k in range(len(active)-1):
            i, jj = active[k][1], active[k+1][1]
            if d[i] == 1 and d[jj] == -1:
                tc = (x[jj] - x[i] - 2*R) / (2*v)
                if tc > 1e-12 and tc < next_dt - 1e-12:
                    next_dt = tc; next_type = 'collision'; next_i = i; next_j = jj
        
        # Advance
        for i in range(N):
            if not exited[i]:
                x[i] += d[i] * v * next_dt
                total_dist[i] += v * next_dt
        t += next_dt
        
        if next_type == 'collision':
            d[next_i] *= -1
            d[next_j] *= -1
        elif next_type == 'wall':
            d[next_i] *= -1
        elif next_type == 'exit':
            exited[next_i] = True
    
    return int(round(total_dist[j-1]))

def compute_free(L, N, j):
    """Free trajectory approach."""
    MOD_PRNG = 32745673
    r = 6563116
    free_dist = []
    
    x_prev_center = 0
    for i in range(N):
        gap = (r % 1000) + 1
        if i == 0:
            x = gap + R
        else:
            x = x_prev_center + R + gap + R
        x_prev_center = x
        
        direc = 1 if r <= 10000000 else -1
        if direc == 1:
            fd = L - x
        else:
            fd = (x - R) + (L - R)
        free_dist.append(fd)
        r = (r * r) % MOD_PRNG
    
    free_dist.sort()
    return free_dist[N - j]  # No subtraction

# Test
for L, N, j, expected in [
    (5000, 3, 2, 5519),
    (10000, 11, 6, 11780),
    (100000, 101, 51, 114101),
]:
    sim = simulate(L, N, j)
    free = compute_free(L, N, j)
    print(f"d({L},{N},{j}): sim={sim}, free={free}, expected={expected}")
    print(f"  sim diff={sim-expected}, free diff={free-expected}")
