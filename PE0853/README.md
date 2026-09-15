# PE853 — Pisano Periods 1（Pisano周期1）

来源：改编自 Project Euler Problem 853

## 原题意

Pisano 周期 $\\pi(m)$ 定义为斐波那契数列模 $m$ 的最小正周期。即最小的正整数 $k$ 使得：
$$F_k \\equiv 0 \\pmod{m}, \\quad F_{k+1} \\equiv 1 \\pmod{m}$$
其中 $F_0 = 0$，$F_1 = 1$。

Pisano 周期有丰富的数论性质：
- $\\pi(1) = 1$，$\\pi(2) = 3$，$\\pi(5) = 20$
- 对于奇素数 $p \\neq 5$：若 $p \\equiv \\pm 1 \\pmod{5}$，则 $\\pi(p) \\mid p-1$；若 $p \\equiv \\pm 2 \\pmod{5}$，则 $\\pi(p) \\mid 2(p+1)$
- $\\pi(p^k) = p^{k-1} \\cdot \\pi(p)$（通常成立，Wall-Sun-Sun 素数为例外）
- $\\pi(\\operatorname{lcm}(a,b)) = \\operatorname{lcm}(\\pi(a), \\pi(b))$ 当 $\\gcd(a,b)=1$

PE 答案：44511058204。

## 算法

1. **暴力模拟**：逐对计算 $(F_k \\bmod m, F_{k+1} \\bmod m)$ 直到回到 $(0,1)$，时间复杂度 $O(\\pi(m))$。
2. **矩阵快速幂（快速加倍）**：使用 Fibonacci 快速加倍公式在 $O(\\log n)$ 时间内计算 $F_n \\bmod m$，用于验证周期。
3. **质因数分解**：利用 $\\pi$ 的乘性，先分解 $m$，然后分别计算各质数幂的周期，取 LCM。
4. **素数周期快速计算**：利用 Legendre 符号 $(5|p)$ 的性质，在 $p-1$ 或 $2(p+1)$ 的因子中搜索。

## 改编方向

1. 计算 $\\sum_{m=1}^{N} \\pi(m)$ 或 $\\sum_{m=1}^{N} m \\cdot \\pi(m)$
2. 研究 Wall-Sun-Sun 素数（$\\pi(p^2) = \\pi(p)$ 的素数）
3. 将 Pisano 周期推广到广义 Fibonacci 数列
4. 研究 $\\pi(m)$ 的分布与增长速率
5. 寻找满足 $\\pi(m) = m$ 的 $m$（Wall 猜想：仅 $m=24 \\cdot 5^k$）
