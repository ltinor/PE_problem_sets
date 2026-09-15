# 234 — Semidivisible numbers

来源：改编自 Project Euler Problem 234

## 原题意

对一个整数 $n \ge 4$，定义：
- $\operatorname{lps}(n)$：$\le \sqrt{n}$ 的最大素数
- $\operatorname{ups}(n)$：$\ge \sqrt{n}$ 的最小素数

若 $\operatorname{lps}(n) \mid n$ 和 $\operatorname{ups}(n) \mid n$ 恰有一个成立（异或），则称 $n$ 为「半可除数」。

求所有 $n \le 999966663333$ 的半可除数之和。原题答案：1259187438574927161。

## 题目

参数化上界 $N$：输入 $N$，求所有 $n \le N$ 的半可除数之和。

## 数据范围

$1 \le N \le 10^{12}$

## 算法

**std**: 对相邻素数对 $(p_k, p_{k+1})$，考虑区间 $[p_k^2, p_{k+1}^2)$ 内的 $n$，此时 $\operatorname{lps}(n) = p_k$, $\operatorname{ups}(n) = p_{k+1}$。

对每对相邻素数，计算区间内被 $p_k$ 或 $p_{k+1}$ 之一整除（但不是同时）的数的和：

$$\text{sum} = \sum(\text{被 }p_k\text{ 整除}) + \sum(\text{被 }p_{k+1}\text{ 整除}) - 2 \times \sum(\text{被 }p_k p_{k+1}\text{ 整除})$$

使用等差数列求和公式 $O(1)$ 计算每对素数的贡献。总复杂度 $O(\pi(\sqrt{N}))$。

**brute**: 对每个 $n$ 搜索 $\operatorname{lps}$ 和 $\operatorname{ups}$ 并判断，适用于 $N \le 200000$。

## 改编方向

1. **参数化 N**：将固定上界改为输入参数。
2. **仅计数**：可改为求个数而非和。
3. **扩展定义**：参数化 $\operatorname{lps}/\operatorname{ups}$ 的偏移量。
