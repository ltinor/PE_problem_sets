import sys
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
    """resulting numbers from removing one occurrence of 'digit' from tern(n)"""
    s = tern(n)
    L = len(s)
    res = set()
    for i in range(L):
        if s[i] != digit: continue
        t = s[:i] + s[i+1:]
        if t == "":
            continue  # empty invalid
        if t[0] == '0':
            if lead_mode == 'strip':
                t = t.lstrip('0')
                if t == "": t = "0"
            else:
                continue  # invalid leading zero
        res.add(int(t, 3))
    return res

def make_solver(assign, lead_mode):
    # assign: dict digit char -> 'own'/'opp'/'either'
    @lru_cache(maxsize=None)
    def win(a,b,c,d,turn):
        if turn == 0:
            own = (a,b); opp = (c,d)
        else:
            own = (c,d); opp = (a,b)
        def moves_on(x, is_own):
            out = set()
            for d in '012':
                rule = assign[d]
                if rule == 'either': ok = True
                elif rule == 'own': ok = is_own
                elif rule == 'opp': ok = not is_own
                else: ok = False
                if ok:
                    out |= removals(x, d, lead_mode)
            return out
        # own numbers
        for idx, x in enumerate(own):
            for r in moves_on(x, True):
                if turn == 0:
                    nxt = (r,b,c,d) if idx==0 else (a,r,c,d)
                else:
                    nxt = (a,b,r,d) if idx==0 else (a,b,c,r)
                if not win(*nxt, 1-turn): return True
        # opp numbers
        for idx, x in enumerate(opp):
            for r in moves_on(x, False):
                if turn == 0:
                    nxt = (a,b,r,d) if idx==0 else (a,b,c,r)
                else:
                    nxt = (r,b,c,d) if idx==0 else (a,r,c,d)
                if not win(*nxt, 1-turn): return True
        return False
    return win

def check(assign, lead_mode, N=5):
    win = make_solver(assign, lead_mode)
    fair = lambda a,b,c,d: (not win(a,b,c,d,0)) and (not win(a,b,c,d,1))
    ex = fair(1,5,2,4)
    nums = list(range(1,N+1))
    pairs = list(combinations_with_replacement(nums,2))
    cnt = 0
    for (a,b) in pairs:
        for (c,d) in pairs:
            if fair(a,b,c,d):
                cnt += 1
    return ex, cnt

if __name__ == "__main__":
    rules = ['own','opp','either']
    text_assign = {'0':'own','1':'opp','2':'either'}
    for lead_mode in ['strip','invalid']:
        print(f"--- lead_mode={lead_mode} ---")
        # text assignment
        ex, cnt = check(text_assign, lead_mode)
        print(f"text assign own0/opp1/either2: example_fair={ex}, F(5)={cnt}")
        # all assignments
        for combo in product(rules, repeat=3):
            assign = {'0':combo[0],'1':combo[1],'2':combo[2]}
            ex, cnt = check(assign, lead_mode)
            if cnt == 21 and ex:
                print(f"  MATCH: {assign} example_fair={ex} F(5)={cnt}")
