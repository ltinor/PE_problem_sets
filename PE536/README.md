# PE536 - 模幂恒等式 (Modulo Power Identity)

来源：改编自 Project Euler Problem 536

## 原题意

设 $S(n) = \sum_{a=1}^{n} (a^n \bmod n)$，即所有 $a^n$ 除以 $n$ 的余数之和。
求 $\sum_{n=1}^{N} S(n)$ 对于 $N = 2 \times 10^7$ 的值。

PE 答案：75874595。

## 题目

给定 N，计算 $\sum_{n=1}^{N} \sum_{a=1}^{n} (a^n \bmod n)$。

## 算法

- 暴力枚举法（仅适用于小 N）：对每个 n 从 1 到 N，对每个 a 从 1 到 n，用快速幂计算 $a^n \bmod n$ 并累加。
- 时间复杂度：$O(N^2 \log N)$（小数据）。
- 大规模数据需要利用数论性质优化：
  - 对于素数 p：由费马小定理 $a^p \equiv a \pmod p$，故 $\sum_{a=1}^{p} (a^p \bmod p) = \frac{p(p-1)}{2} \bmod p$。
  - 对于合数 n：可利用中国剩余定理分解。

## 改编方向

1. **修改指数**：计算 $\sum a^k \bmod n$ 而非 $a^n$。
2. **不同模数**：对结果取模 $10^9+7$。
3. **条件筛选**：只对满足某些条件的 n（如素数、无平方因子数）求和。
4. **变体函数**：使用 $\sum \gcd(a, n)$ 或 $\sum \text{lcm}(a, n)$。
