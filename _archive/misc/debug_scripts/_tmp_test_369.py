# PE369: Quick verification for n=4 using cover approach
from math import comb

# For n=4: f(4) = 17160 (Badugis)
# Verify: g(4) = C(52,4) - 17160 = 253565

# k=1 term: sum over all covers of C(|A(C)|, 4)
k1 = 0
for a,b in [(1,0),(2,0),(3,0),(0,1),(0,2),(0,3),(1,1),(2,1),(1,2)]:
    size = 4*a + 13*b - a*b
    count = comb(13,a) * comb(4,b)
    k1 += count * comb(size, 4)
print(f"k=1: {k1}")
print(f"C(52,4) = {comb(52,4)}")
print(f"Expected g(4) = C(52,4) - 17160 = {comb(52,4) - 17160}")
print()

# k=2 term: subtract intersections of cover pairs
# For two covers (R1,S1) and (R2,S2), |A(C1)∩A(C2)| = 52 - |F1∪F2|
# |F1∪F2| = |F1| + |F2| - |F1∩F2|
# |F1| = (13-a1)*(4-b1), |F2| = (13-a2)*(4-b2)
# |F1∩F2| = (13 - |R1∪R2|) * (4 - |S1∪S2|)
# |R1∪R2| = a1 + a2 - overlap_r, |S1∪S2| = b1 + b2 - overlap_s
# where overlap_r = |R1∩R2|, overlap_s = |S1∩S2|

# This depends on the specific choice of R1,R2 (how much they overlap).
# For covers of type (a1,b1) and (a2,b2), the intersection depends on 
# the overlap sizes o_r, o_s where 0 ≤ o_r ≤ min(a1,a2), 0 ≤ o_s ≤ min(b1,b2).

# Number of pairs with given overlap: 
# For ranks: choose o_r shared ranks, a1-o_r unique to R1, a2-o_r unique to R2
# C(13, o_r) * C(13-o_r, a1-o_r) * C(13-a1, a2-o_r)
# Similarly for suits.

# This is getting complex but manageable. Let me compute k=2 for n=4.

print("Computing k=2 term for n=4...")

def count_cover_pairs(a1,b1,a2,b2):
    """Count pairs of covers (R1,S1) and (R2,S2) grouped by overlap, 
    returning dict: (overlap_r, overlap_s) -> count"""
    result = {}
    for o_r in range(max(0, a1+a2-13), min(a1,a2)+1):
        cnt_r = comb(13, o_r) * comb(13-o_r, a1-o_r) * comb(13-a1, a2-o_r)
        for o_s in range(max(0, b1+b2-4), min(b1,b2)+1):
            cnt_s = comb(4, o_s) * comb(4-o_s, b1-o_s) * comb(4-b1, b2-o_s)
            result[(o_r, o_s)] = cnt_r * cnt_s
    return result

cover_types = [(1,0),(2,0),(3,0),(0,1),(0,2),(0,3),(1,1),(2,1),(1,2)]

k2 = 0
# Ordered pairs (R1,S1), (R2,S2) distinguished
for i, (a1,b1) in enumerate(cover_types):
    for j, (a2,b2) in enumerate(cover_types):
        if i == j:  # same type, handle carefully to avoid double counting?
            pass  # we want all ordered pairs
        pairs = count_cover_pairs(a1,b1,a2,b2)
        for (o_r, o_s), cnt in pairs.items():
            r_union = a1 + a2 - o_r
            s_union = b1 + b2 - o_s
            f1 = (13-a1)*(4-b1)
            f2 = (13-a2)*(4-b2)
            f12 = (13 - r_union) * (4 - s_union)
            union_f = f1 + f2 - f12
            allowed = 52 - union_f
            if allowed >= 4:
                k2 += cnt * comb(allowed, 4)

# But this counts each unordered pair twice (once as (i,j) and once as (j,i))
# And for i=j, we're counting ordered pairs from the same type
# Let me handle this properly.

# Actually, for the PIE on sets, the k=2 term is Σ_{C1<C2} C(|A(C1)∩A(C2)|, n)
# Sum over unordered pairs.

# My k2 above sums over all ordered pairs within each type pair.
# For i≠j, each unordered pair with one cover of type i and one of type j is counted once.
# For i=j, each unordered pair of same-type covers is counted twice in my loop 
# (since I'm iterating all (a1,b1) and (a2,b2) = same type).
# But the count_cover_pairs function counts (R1,R2) as ordered. 
# So for i=j, the function counts each unordered pair twice (R1,R2) and (R2,R1).
# For i≠j, it counts (R1,R2) but not (R2,R1) where types are swapped.

# This is getting confusing. Let me just compute correctly.

# Sum over UNORDERED pairs of covers.
# For each unordered pair, compute |A(C1)∩A(C2)| and add C(|∩A|, n).

# Let me simplify: for n=4 only (since only 4-card hands matter for verification),
# compute g(4) using exhaustive enumeration of all possible hand structures.

# A 4-card hand can be described by which 4 (rank,suit) pairs are selected.
# 52 cards, choose 4 = 270725 hands.
# This is small enough to enumerate!

print("\n--- Direct enumeration for n=4 ---")
total_hands = comb(52, 4)
print(f"Total 4-card hands: {total_hands}")

# Enumerate all 4-card hands (inefficient but just for verification)
# Instead, count hands WITHOUT Badugi using conditions.
# A 4-card hand lacks Badugi iff:
# - Two cards share a rank, OR
# - Two cards share a suit
# (Since with 4 cards, the only way to have all different ranks and suits is to be a Badugi)

# So count hands where at least two cards share a rank or suit.
# Use PIE: 
# A: hands where ≥2 cards share a rank
# B: hands where ≥2 cards share a suit
# g(4) = |A ∪ B| = |A| + |B| - |A ∩ B|

# |A|: hands with at least one rank appearing ≥2 times.
# Count complement: no rank appears >1 time.
# For no repeated ranks: choose 4 distinct ranks from 13: C(13,4). 
# For each, choose any suit for each: 4^4 = 256.
# BUT: we also need to avoid hands that are Badugis (all suits distinct from all ranks distinct).
# Actually, "no repeated ranks" includes Badugis (all distinct ranks, all distinct suits).
# And "no repeated ranks AND no repeated suits" = Badugis.

# Hands with no repeated ranks: C(13,4) * 4^4 = 715 * 256 = 183040.
# Hands with no repeated suits: 4^13? No, that's wrong.

# Better: use direct enumeration.

# Number of hands where all 4 ranks are distinct:
# Choose 4 ranks: C(13,4) = 715
# For each rank, choose any suit: 4 choices each = 4^4 = 256
# Total: 715 * 256 = 183040

# Among these, the ones with all suits distinct are Badugis: 17160.
# So hands with all ranks distinct but NOT all suits distinct = 183040 - 17160 = 165880.

# Hands with a repeated rank: total - hands with all distinct ranks
# = 270725 - 183040 = 87685.

# Hands with all suits distinct: 
# Each suit appears at most once. Choose which 4 cards from the 13 of each suit.
# From 4 suits, choose 1 card each: 13^4 = 28561.
# But wait, these 4 cards might have repeated ranks.
# Among these, Badugis = 17160.
# So hands with all suits distinct but repeated ranks = 28561 - 17160 = 11401.

# |A| = hands with at least one repeated rank = 87685
# |B| = hands with at least one repeated suit = total - hands with all suits distinct
#      = 270725 - 28561 = 242164

# |A ∩ B| = hands with both a repeated rank AND a repeated suit
#         = total - (all distinct ranks) - (all distinct suits) + Badugis
#         = 270725 - 183040 - 28561 + 17160
#         = 76284

# g(4) = |A| + |B| - |A∩B| = 87685 + 242164 - 76284 = 253565
g4 = 87685 + 242164 - 76284
f4 = total_hands - g4
print(f"|A| = 87685")
print(f"|B| = 242164") 
print(f"|A∩B| = 76284")
print(f"g(4) = {g4}")
print(f"f(4) = C(52,4) - g(4) = {f4}")
print(f"Expected f(4): 17160")
print(f"Match: {f4 == 17160}")
