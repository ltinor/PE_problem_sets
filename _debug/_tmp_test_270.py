# PE270: Compute C(30) mod 10^8

def compute_C_mod(N, mod):
    total_points = 4 * N
    points = []
    
    # Clockwise from top-left (0,N):
    for x in range(0, N):
        points.append((x, N))
    for y in range(N, -1, -1):
        points.append((N, y))
    for x in range(N - 1, -1, -1):
        points.append((x, 0))
    for y in range(1, N):
        points.append((0, y))
    
    LEFT, BOTTOM, RIGHT, TOP = 1, 2, 4, 8
    def get_sides(x, y):
        mask = 0
        if x == 0: mask |= LEFT
        if y == 0: mask |= BOTTOM
        if x == N: mask |= RIGHT
        if y == N: mask |= TOP
        return mask
    
    side_mask = [get_sides(x, y) for (x, y) in points]
    
    # Precompute valid chords
    valid = [[False] * total_points for _ in range(total_points)]
    for i in range(total_points):
        for j in range(i + 1, total_points):
            valid[i][j] = valid[j][i] = ((side_mask[i] & side_mask[j]) == 0)
    
    # DP[l][r] for l < r
    dp = [[0] * total_points for _ in range(total_points)]
    for i in range(total_points - 1):
        dp[i][i + 1] = 1  # edge
    
    # Increasing interval length
    for length in range(2, total_points):
        for l in range(0, total_points - length):
            r = l + length
            total = 0
            for k in range(l + 1, r):
                valid_lk = (k == l + 1) or valid[l][k]
                valid_kr = (r == k + 1) or valid[k][r]
                if valid_lk and valid_kr:
                    total = (total + dp[l][k] * dp[k][r]) % mod
            dp[l][r] = total
    
    return dp[0][total_points - 1]

mod = 10**8
result = compute_C_mod(30, mod)
print(f"C(30) mod 10^8 = {result}")
print(f"Expected: 82282080")
print(f"Match: {result == 82282080}")
