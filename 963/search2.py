from itertools import combinations_with_replacement, product
from functools import lru_cache

def tern(n):
    if n == 0: return "0"
    s = ""
    while n:
        s = str(n % 3) + s
        n //= 3
    return s

def removals(n, digit, lead_mode):
    s = tern(n)
    L = len(s)
    res = set()
    for i in range(L):
        if s[i] != digit: continue
        t = s[:i] + s[i+1:]
        if t == "": continue
        if t[0] == '0':
            if lead_mode == 'strip':
                t = t.lstrip('0'); t = t or "0"
            else:
                continue
        res.add(int(t, 3))
    return res

def make_solver(assign, lead_mode):
    @lru_cache(maxsize=None)
    def win(a,b,c,d,turn):
        own = (a,b) if turn==0 else (c,d)
        opp = (c,d) if turn==0 else (a,b)
        def moves_on(x, is_own):
            out = set()
            for d in '012':
                rule = assign[d]
                ok = (rule=='either') or (rule=='own' and is_own) or (rule=='opp' and not is_own)
                if ok: out |= removals(x, d, lead_mode)
            return out
        for idx, x in enumerate(own):
            for r in moves_on(x, True):
                nxt = (r,b,c,d) if (turn==0 and idx==0) else ((a,r,c,d) if (turn==0 and idx==1) else ((a,b,r,d) if (turn==1 and idx==0) else (a,b,c,r)))
                if not win(*nxt, 1-turn): return True
        for idx, x in enumerate(opp):
            for r in moves_on(x, False):
                nxt = (a,b,r,d) if (turn==0 and idx==0) else ((a,b,c,r) if (turn==0 and idx==1) else ((r,b,c,d) if (turn==1 and idx==0) else (a,r,c,d)))
                if not win(*nxt, 1-turn): return True
        return False
    return win

for lead in ['strip','invalid']:
    for assign in [{'0':'own','1':'opp','2':'opp'}, {'0':'own','1':'opp','2':'own'}, {'0':'own','1':'opp','2':'either'}]:
        win = make_solver(assign, lead)
        fair = lambda a,b,c,d: (not win(a,b,c,d,0)) and (not win(a,b,c,d,1))
        ex = fair(1,5,2,4)
        nums = list(range(1,6))
        pairs = list(combinations_with_replacement(nums,2))
        cnt = sum(1 for (a,b) in pairs for (c,d) in pairs if fair(a,b,c,d))
        print(f"lead={lead} assign={assign}: example_fair={ex} F(5)={cnt}")
