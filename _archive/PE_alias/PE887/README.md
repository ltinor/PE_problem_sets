# PE887 — Bounded Primes（有界素数）

来源：改编自 Project Euler Problem 887

## 原题意

定义 $Q(n)$ 为满足 $p \leq \sqrt{n}$ 且 $p \mid n$ 的素数 $p$ 的个数。

对于从 $[1, M]$ 中均匀随机选取的 $N$，计算 $Q(N)$ 的期望值 $E[Q(N)]$。

## 算法

1. **计数公式**：
   - 对固定素数 $p$，$p \mid n$ 且 $p \leq \sqrt{n} \iff n \geq p^2$ 且 $p \mid n$
   - 满足条件的 $n \leq M$ 的数量为 $\max(0, \lfloor M/p \rfloor - p + 1)$

2. **期望值计算**：
   - $E[Q] = \frac{1}{M} \sum_{p \leq \sqrt{M}} \max(0, \lfloor M/p \rfloor - p + 1)$
   - 使用素数筛法枚举所有素数

3. **渐近分析**：
   - $E[Q] \sim \sum_{p \leq \sqrt{M}} \frac{1}{p} \sim \log\log\sqrt{M} = \log\log M - \log 2$
   - 增长非常缓慢

## 改编方向

1. 高阶矩：$E[Q^2]$、方差等
2. 限制 $n$ 为特定形式（平方数、无平方因子数等）
3. 多个 $n$ 的联合分布
4. 推广到 $p \leq n^{1/k}$ 的条件
