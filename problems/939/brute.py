import sys
from functools import lru_cache
sys.setrecursionlimit(1000000)

# Partisan Nim: piles on A's side or B's side.
# A's turn: remove 1 stone from a B-pile, OR remove an entire A-pile.
# B's turn: remove 1 stone from an A-pile, OR remove an entire B-pile.
# Winner removes the last stone.
# E(N): #configs (unordered piles) with total stones <= N where A wins
# regardless of who moves first.

@lru_cache(maxsize=None)
def outcome(A, B, turn):
    # A, B are sorted tuples of positive pile sizes.
    # turn: 0 = A to move, 1 = B to move.
    # returns True if A wins (from here with perfect play).
    if not A and not B:
        # no stones; player to move loses (previous player took last stone)
        # A to move and no stones => A loses. B to move and no stones => B loses => A wins.
        return (turn == 1)
    if turn == 0:
        # A's moves
        # remove 1 from a B-pile
        for i, s in enumerate(B):
            nb = list(B); 
            if s == 1:
                del nb[i]
            else:
                nb[i] = s-1
            nb = tuple(sorted(nb))
            if outcome(A, nb, 1):
                return True
        # remove an entire A-pile
        for i, s in enumerate(A):
            na = list(A); del na[i]; na = tuple(sorted(na))
            if outcome(na, B, 1):
                return True
        return False
    else:
        # B's moves
        # remove 1 from an A-pile
        for i, s in enumerate(A):
            na = list(A)
            if s == 1:
                del na[i]
            else:
                na[i] = s-1
            na = tuple(sorted(na))
            if not outcome(na, B, 0):
                return False  # B found a move to make A lose
        # remove an entire B-pile
        for i, s in enumerate(B):
            nb = list(B); del nb[i]; nb = tuple(sorted(nb))
            if not outcome(A, nb, 0):
                return False
        return True  # A wins (B has no winning move)

def wins_regardless(A, B):
    # A wins whether A goes first or B goes first
    return outcome(tuple(sorted(A)), tuple(sorted(B)), 0) and \
           outcome(tuple(sorted(A)), tuple(sorted(B)), 1)

def partitions(n, maxpart=None):
    if maxpart is None:
        maxpart = n
    if n == 0:
        yield []
        return
    for k in range(min(n, maxpart), 0, -1):
        for rest in partitions(n-k, k):
            yield [k] + rest

def E(N):
    cnt = 0
    configs = []
    # total stones s from 0..N, a from 0..s, b=s-a
    for s in range(1, N+1):
        for a in range(0, s+1):
            b = s - a
            for pa in partitions(a):
                for pb in partitions(b):
                    if wins_regardless(pa, pb):
                        cnt += 1
                        configs.append((list(pa), list(pb)))
    return cnt, configs

for N in range(1, 9):
    c, cfg = E(N)
    print(f"E({N}) = {c}")
    if N == 4:
        for pa, pb in cfg:
            print("   A:", pa, " B:", pb)
