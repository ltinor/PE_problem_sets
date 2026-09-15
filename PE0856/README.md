# PE 856: Waiting for a Pair / 等待对子

## Problem
A standard 52-card deck comprises 13 ranks in four suits. A pair is a set of two cards of the same rank. Cards are drawn, without replacement, from a well shuffled 52-card deck waiting for consecutive cards that form a pair. Cards are drawn until either such a pair is found or the pack is exhausted. Find the expected number of cards drawn, rounded to 8 decimal places.

## Answer
**2.59149127**

## Solution Approach
Dynamic programming on the state of remaining cards. State space: (a4, a3, a2, a1, k) where a_i = number of ranks with i cards remaining, k = cards remaining of the last drawn rank. Total states ≈ C(17,4) × 4 = 9520.

## File Structure
```
PE0856/
├── code/
│   └── std.cpp    # C++ solution with DP
└── README.md
```
