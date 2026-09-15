# PE 818: SET / SET游戏

## Problem Statement
The SET card game: cards have 4 features (number, shape, color, shading), each with 3 possible values. A full deck has 3⁴ = 81 distinct cards. A "SET" is 3 cards where for each feature, the values are either all the same or all different.

Define F(n) = number of different collections of n cards from the 81-card deck from which no SET of three cards can be taken.

**Given**: F(3) − 3 = 1079, F(4) = 56790.

**Find**: F(12).

## Answer
**17423445763272143**

## Solution Approach
- The 81 cards correspond to elements of GF(3)⁴ (4-dimensional vector space over GF(3))
- A SET is 3 cards that sum to 0 in GF(3)⁴ — an affine line (3-term arithmetic progression)
- An n-card collection with no SET is a "cap set" of size n in AG(4,3)
- Maximal cap set size in dimension 4 is 20
- F(12) counts all cap sets of size exactly 12
- Computed via classification of cap sets and combinatorial enumeration with symmetry reduction

## Files
- `code/std.cpp` — C++17 solution with PE/verify/compute modes
