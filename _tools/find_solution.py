"""Find specific 3-flip solution for N=5"""
N = 5
lo = (N-1)*(N-1)
hi = N*N
CN = [[0]*N for _ in range(N)]
for x in range(N):
    for y in range(N):
        if lo <= x*x + y*y < hi:
            CN[x][y] = 1
print("CN:")
for row in CN:
    print(row)

from itertools import combinations
positions = [(i,j) for i in range(N) for j in range(N)]
for combo in combinations(positions, 3):
    board = [[0]*N for _ in range(N)]
    for i, j in combo:
        for x in range(N):
            for y in range(N):
                if x == i or y == j:
                    board[x][y] ^= 1
    if board == CN:
        print(f"Found solution: {combo}")
        print("Resulting board:")
        for row in board:
            print(row)
