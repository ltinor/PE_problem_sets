import sys
from functools import lru_cache
from itertools import combinations_with_replacement

def tern(n):
    if n == 0:
        return "0"
    s = ""
    while n:
        s = str(n % 3) + s
        n //= 3
    return s

def strip(s):
    s = s.lstrip('0')
    return s if s else "0"

# interpretation of leading-zero removal
MODE = sys.argv[1] if len(sys.argv) > 1 else 'strip'  # 'strip' or 'invalid'

def make_moves(n):
    """Return set of numbers reachable by removing one trit from n.
    Also return which digits are removable."""
    s = tern(n)
    L = len(s)
    results = set()
    for i in range(L):
        t = s[:i] + s[i+1:]
        if t == "":
            continue
        if t[0] == '0':
            if MODE == 'strip':
                t = strip(t)
            else:
                continue  # invalid (leading zero)
        results.add(int(t, 3))
    return results

@lru_cache(maxsize=None)
def can_win(a, b, c, d, turn):
    # turn: 0 = player1 (owns a,b), 1 = player2 (owns c,d)
    # returns True if current player (turn) wins
    own = (a, b) if turn == 0 else (c, d)
    opp = (c, d) if turn == 0 else (a, b)
    # generate all moves
    def moves_from(x, is_own):
        s = tern(x)
        L = len(s)
        res = set()
        for i in range(L):
            dig = s[i]
            ok = (dig == '2') or (dig == '0' and is_own) or (dig == '1' and not is_own)
            if not ok:
                continue
            t = s[:i] + s[i+1:]
            if t == "":
                continue
            if t[0] == '0':
                if MODE == 'strip':
                    t = strip(t)
                else:
                    continue
            res.add(int(t, 3))
        return res

    # collect moves
    moves = []
    # own numbers (a,b) or (c,d)
    na, nb = own
    for x in [na, nb]:
        for r in moves_from(x, True):
            if turn == 0:
                moves.append((r, b, c, d) if x == a else (a, r, c, d))
            else:
                moves.append((a, b, r, d) if x == c else (a, b, c, r))
    nc, nd = opp
    for x in [nc, nd]:
        for r in moves_from(x, False):
            if turn == 0:
                moves.append((a, b, r, d) if x == c else (a, b, c, r))
            else:
                moves.append((r, b, c, d) if x == a else (a, r, c, d))
    # if any move leads to a state where opponent loses -> current player wins
    nt = 1 - turn
    for (aa, bb, cc, dd) in moves:
        # normalize order within paper for memoization (a<=b, c<=d)
        if aa > bb: aa, bb = bb, aa
        if cc > dd: cc, dd = dd, cc
        if not can_win(aa, bb, cc, dd, nt):
            return True
    return False

def fair(a, b, c, d):
    return (not can_win(a, b, c, d, 0)) and (not can_win(a, b, c, d, 1))

def F(N):
    nums = list(range(1, N+1))
    cnt = 0
    pairs = list(combinations_with_replacement(nums, 2))
    for (a, b) in pairs:
        for (c, d) in pairs:
            if fair(a, b, c, d):
                cnt += 1
    return cnt

if __name__ == "__main__":
    for N in range(1, 6):
        print(f"F({N}) = {F(N)}  (MODE={MODE})")
