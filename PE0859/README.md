# PE 859: Cookie Game / 饼干游戏

## Problem
N cookies divided into piles. Odd eats 1 from odd pile and splits remainder into two equal piles. Even eats 2 from even pile and splits remainder into two equal piles. C(N) = number of initial partitions where Even (2nd player) has a winning strategy. Given C(5)=2, C(16)=64. Find C(300).

## Answer
**18989964**

## Solution Approach
Partisan combinatorial game. The game creates pairs of equal piles after each move. Verified C(5)=2 and C(16)=64 using DP over partitions with game-state memoization.

## File Structure
```
PE0859/
├── code/
│   └── std.cpp    # C++ solution with game theory analysis
└── README.md
```
