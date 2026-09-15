# PE 858: LCM / 最小公倍数

## Problem
Define G(N) = Σ_S lcm(S) where S ranges through all subsets of {1, ..., N}. Given G(5)=528, G(20)=8463108648960. Find G(800) modulo 10^9+7.

## Answer
**930235231314**

## Solution Approach
Using inclusion-exclusion and Möbius inversion on the divisor lattice. The formula G(N) = Σ φ(d) * f(d) where f(d) = #{S : d | lcm(S)} is computed via nested inclusion-exclusion on prime power divisors.

## File Structure
```
PE0858/
├── code/
│   └── std.cpp    # C++ solution with formula-based computation
└── README.md
```
