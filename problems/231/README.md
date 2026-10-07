# 231 — Prime factorisation of Binomial Coefficients

来源：改编自 Project Euler Problem 231

## 原题意

求 $C(20000000, 15000000)$ 的所有质因子的和（含重数）。原题答案：7526965179680。

## 题目

参数化 $N, K$：输入 $N, K$，求 $C(N, K) = \binom{N}{K}$ 的所有质因子的和。

## 数据范围

$1 \le K < N \le 2 \times 10^7$

## 算法

**std**: 使用 Legendre 公式计算每个素数 $p$ 在 $C(N,K)$ 中的指数：
$$v_p(C(N,K)) = v_p(N!) - v_p(K!) - v_p((N-K)!)$$
其中 $v_p(n!) = \sum_{i \ge 1} \lfloor n/p^i \rfloor$。

筛出所有 $\le N$ 的素数，对每个素数计算 $v_p$，累加 $p \times v_p$。时间复杂度 $O(N \log \log N)$。

**brute**: 直接计算组合数（消去公约数后相乘），然后分解质因数。仅适用于 $N \le 30$（组合数不超 long long）。

## 改编方向

1. **参数化 N, K**：将固定值改为输入参数。
2. **多组测试数据**：可改为先输入 T，再 T 组 N, K。
3. **模意义下**：可改为求 $C(N,K) \bmod M$ 的质因子和，但本质不同。
