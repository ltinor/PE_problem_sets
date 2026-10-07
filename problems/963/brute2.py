import sys
from functools import lru_cache

def tern(n):
    if n == 0: return "0"
    s = ""
    while n:
        s = str(n % 3) + s
        n //= 3
    return s

def all_removals(n):
    """dict digit -> set of resulting numbers, removing one occurrence of that digit"""
    s = tern(n)
    L = len(s)
    res = {}
    for i in range(L):
        d = s[i]
        t = s[:i] + s[i+1:]
        if t == "":
            continue
        if t[0] == '0':
            # both interpretations: strip vs invalid
            continue  # treat as invalid (leading zero not allowed)
        res.setdefault(d, set()).add(int(t, 3))
    return res

@lru_cache(maxsize=None)
def win(a,b,c,d,turn):
    # turn 0 = player1 owns (a,b); turn 1 = player2 owns (c,d)
    # returns True if player 'turn' (to move) wins
    if turn == 0:
        own = [a,b]; opp = [c,d]
    else:
        own = [c,d]; opp = [a,b]
    def move_on(x, is_own):
        # returns list of resulting values for legal moves on x
        rm = all_removals(x)
        out = set()
        for d in '012':
            if d not in rm: continue
            if d == '2': out |= rm[d]  # either
            elif d == '0' and is_own: out |= rm[d]
            elif d == '1' and not is_own: out |= rm[d]
        return out
    for idx, x in enumerate(own):
        for r in move_on(x, True):
            if turn == 0:
                nxt = (r,b,c,d) if idx==0 else (a,r,c,d)
            else:
                nxt = (a,b,r,d) if idx==0 else (a,b,c,r)
            if not win(*nxt, 1-turn):
                return True
    for idx, x in enumerate(opp):
        for r in move_on(x, False):
            if turn == 0:
                nxt = (a,b,r,d) if idx==0 else (a,b,c,r)
            else:
                nxt = (r,b,c,d) if idx==0 else (a,r,c,d)
            if not win(*nxt, 1-turn):
                return True
    return False

def fair(a,b,c,d):
    return (not win(a,b,c,d,0)) and (not win(a,b,c,d,1))

# test example
print("(1,5|2,4) fair?", fair(1,5,2,4))
print("win P1 moves first:", win(1,5,2,4,0), "win P2 first:", win(1,5,2,4,1))

# enumerate fair settings for N=5 with explanation
from itertools import combinations_with_replacement
nums = list(range(1,6))
pairs = list(combinations_with_replacement(nums,2))
fair_list = []
for (a,b) in pairs:
    for (c,d) in pairs:
        if fair(a,b,c,d):
            fair_list.append((a,b,c,d))
print("F(5) =", len(fair_list))
for f in fair_list:
    print("  ", f)
