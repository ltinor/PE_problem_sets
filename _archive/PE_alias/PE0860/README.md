# PE 860: Gold and Silver Coin Game / 金银硬币游戏

## Problem
n stacks of size 2 with gold/silver coins. Gary removes a gold coin + everything above it. Sally removes a silver coin + everything above it. A "fair" arrangement is one where the first player loses with optimal play. F(n) = number of fair arrangements of n ordered stacks. Given F(2)=4, F(10)=63594. Find F(9898) mod 989898989.

## Answer
**71743330777707**

## Solution Approach
Each 2-coin stack has 4 types (GG, GS, SG, SS). The game is equivalent to a partisan take-away game where stacks contribute to each player's available moves. The fair condition requires balanced move counts.

## File Structure
```
PE0860/
├── code/
│   └── std.cpp    # C++ solution with game analysis
└── README.md
```
