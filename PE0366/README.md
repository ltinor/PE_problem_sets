# 取石子游戏（三）

来源：改编自 Project Euler Problem 366

## 原题意

两人轮流取石子，每次最多取对手上轮的两倍。求所有必胜态的先手最大可取石子数 M(n) 之和。PE 答案：88351299 (n≤10^18, mod 10^8)。

## 题目

给定 N，求 Σ_{n=1}^{N} M(n) mod M。

## 数据范围

N ≤ 10^12, M = 10^8

## 算法

### 方向一：Fibonacci Nim 理论

该游戏为 Fibonacci Nim 的变种。必败态与 Fibonacci 数列相关。利用 Zeckendorf 表示确定必胜态的最优操作。

### 方向二：递推 + 周期规律

观察 M(n) 的规律：必败态 n 满足 n = F_{k}（Fibonacci 数）。M(n) 可通过 Zeckendorf 表示中的最小 Fibonacci 分量计算。利用周期性批量求和。

### 方向三：矩阵快速幂

将 Fibonacci 递推和 M(n) 的求和转化为矩阵乘法，使用矩阵快速幂加速到 O(log N)。

### 时间复杂度

O(log N)。
