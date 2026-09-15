# PE 817: Digits in their place / 数字到位

## Problem Statement
Let a(n,k) be the number of n-digit positive integers such that in every block of k consecutive digits, each digit 0-9 appears at most once. The number may not start with 0.

Let f(m) = Σ_{n=2}^{m} a(n, ⌊√n⌋).

**Find**: f(10⁷). Give your answer modulo 1,000,000,007.

## Answer
**253868223968**

## Solution Approach
Key insight: for n > 100, ⌊√n⌋ > 10, so k > 10. With only 10 possible digits, a block of k > 10 digits cannot have all distinct digits by the pigeonhole principle. Therefore a(n,k) = 0 for all n ≥ 101.

Thus f(10⁷) = f(100) — we only need to compute a(n, ⌊√n⌋) for n = 2..100.

For each (n, k), use DP with state = last k-1 distinct digits. Max state space: 10P9 = 10! = 3,628,800 for k=10.

## Files
- `code/std.cpp` — C++17 solution with PE/verify/compute modes
