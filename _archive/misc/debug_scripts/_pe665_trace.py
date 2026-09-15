#!/usr/bin/env python3
"""Debug mex generator: trace a=47"""
import sys
sys.setrecursionlimit(10000)

def mex_generate(limit, trace=False):
    p_set = {(0, 0)}
    seen = {0}
    mex_candidate = 1
    
    while True:
        a = mex_candidate
        while a in seen:
            a += 1
        
        if a > 1000:
            break
        
        b = a + 1
        found = False
        while a + b <= limit:
            if b in seen:
                b += 1
                continue
            
            is_p = True
            for n in range(1, a + 1):
                na, nb = a - n, b
                if na > nb: na, nb = nb, na
                if (na, nb) in p_set:
                    if trace and a == 47:
                        print(f"  (47,{b}) -> remove {n} from first: ({na},{nb}) in P-set")
                    is_p = False; break
            if not is_p:
                if trace and a == 47:
                    print(f"  (47,{b}) is N (first pile move)")
                b += 1; continue
            
            for n in range(1, b + 1):
                na, nb = a, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in p_set:
                    if trace and a == 47:
                        print(f"  (47,{b}) -> remove {n} from second: ({na},{nb}) in P-set")
                    is_p = False; break
            if not is_p:
                if trace and a == 47:
                    print(f"  (47,{b}) is N (second pile move)")
                b += 1; continue
            
            for n in range(1, min(a, b) + 1):
                na, nb = a - n, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in p_set:
                    if trace and a == 47:
                        print(f"  (47,{b}) -> remove {n} from both: ({na},{nb}) in P-set")
                    is_p = False; break
            if not is_p:
                if trace and a == 47:
                    print(f"  (47,{b}) is N (both piles move)")
                b += 1; continue
            
            for n in range(1, min(a, b // 2) + 1):
                na, nb = a - n, b - 2*n
                if na > nb: na, nb = nb, na
                if (na, nb) in p_set:
                    if trace and a == 47:
                        print(f"  (47,{b}) -> remove (n={n},2n): ({na},{nb}) in P-set")
                    is_p = False; break
            if not is_p:
                if trace and a == 47:
                    print(f"  (47,{b}) is N (n,2n move)")
                b += 1; continue
            
            for n in range(1, min(a // 2, b) + 1):
                na, nb = a - 2*n, b - n
                if na > nb: na, nb = nb, na
                if (na, nb) in p_set:
                    if trace and a == 47:
                        print(f"  (47,{b}) -> remove (2n={2*n},n={n}): ({na},{nb}) in P-set")
                    is_p = False; break
            if not is_p:
                if trace and a == 47:
                    print(f"  (47,{b}) is N (2n,n move)")
                b += 1; continue
            
            # Found P-position!
            if trace and a == 47:
                print(f"  (47,{b}) is P (no winning move found)")
            p_set.add((a, b))
            seen.add(a)
            seen.add(b)
            mex_candidate = a + 1
            found = True
            break
        
        if not found:
            if trace:
                print(f"  a={a}: No P-position found within limit")
            break
    
    return p_set

# Run with trace
print("Tracing a=47...")
p_set = mex_generate(200, trace=True)

# Check if (19,31) is in p_set (should be)
print(f"\n(19,31) in p_set: {(19,31) in p_set}")
print(f"Total P-positions: {len(p_set)}")
