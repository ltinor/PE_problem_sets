import sys
from functools import lru_cache
from itertools import combinations_with_replacement

sys.setrecursionlimit(1000000)

# State = (sorted A piles tuple, sorted B piles tuple), only positive sizes.
# turn: 0 = A to move, 1 = B to move. Return True if A wins.

memo = {}

def outcome(A, B, turn):
    key = (A, B, turn)
    if key in memo:
        return memo[key]
    total = sum(A) + sum(B)
    if total == 0:
        # no stones; last mover won. If A to move now -> B took last -> A loses.
        res = (turn == 1)  # if B to move now, A took last -> A wins
        memo[key] = res
        return res
    if turn == 0:  # A's turn
        # A can remove 1 from a B-pile
        for i, v in enumerate(B):
            if v > 0:
                nb = list(B); nb[i] -= 1
                nb = tuple(sorted(x for x in nb if x > 0))
                if outcome(A, nb, 1):
                    memo[key] = True
                    return True
        # A can remove entire A-pile
        for i, v in enumerate(A):
            na = list(A); na[i] = 0
            na = tuple(sorted(x for x in na if x > 0))
            if outcome(na, B, 1):
                memo[key] = True
                return True
        memo[key] = False
        return False
    else:  # B's turn, B wants to win -> A loses
        # B can remove 1 from an A-pile
        for i, v in enumerate(A):
            if v > 0:
                na = list(A); na[i] -= 1
                na = tuple(sorted(x for x in na if x > 0))
                if not outcome(na, B, 0):
                    memo[key] = False
                    return False
        # B can remove entire B-pile
        for i, v in enumerate(B):
            nb = list(B); nb[i] = 0
            nb = tuple(sorted(x for x in nb if x > 0))
            if not outcome(A, nb, 0):
                memo[key] = False
                return False
        memo[key] = True
        return True

def partitions(n, maxpart=None):
    if maxpart is None or maxpart > n:
        maxpart = n
    if n == 0:
        yield ()
        return
    for first in range(maxpart, 0, -1):
        for rest in partitions(n - first, first):
            yield (first,) + rest

def all_states_upto(N):
    # enumerate all multisets of piles assigned to A or B with total <= N
    states = []
    for total in range(0, N+1):
        # choose A piles partition with sum = sa, B piles partition with sum = total - sa
        for sa in range(0, total+1):
            sb = total - sa
            for pa in partitions(sa):
                for pb in partitions(sb):
                    states.append((pa, pb))
    return states

def E(N):
    states = all_states_upto(N)
    cnt = 0
    for A, B in states:
        if outcome(A, B, 0) and outcome(A, B, 1):
            cnt += 1
    return cnt

if __name__ == "__main__":
    for N in range(1, 9):
        print(f"E({N}) = {E(N)}")
    # Also list E(4) winning states
    print("E(4) winning states:")
    for A, B in all_states_upto(4):
        if outcome(A, B, 0) and outcome(A, B, 1):
            print("  A:", list(A), "B:", list(B))
