# Nim 游戏

来源：改编自 Project Euler Problem 301

## 原题意

三堆 Nim，求 $n \le 2^{30}$ 中使 $X(n, 2n, 3n) = 0$ 的个数。PE 答案：7454。

## 题目

输入 $N$（$1 \le N \le 2^{30}$），求满足 $n \oplus 2n \oplus 3n = 0$ 的正整数 $n \le N$ 的个数。

## 数据范围

$1 \le N \le 2^{30}$。

## 算法

### 方向一：数位 DP / 无连续 1 计数（核心）

关键观察：$n \oplus 2n \oplus 3n = 0 \iff n \oplus 2n = n + 2n \iff n \;\&\; 2n = 0 \iff n$ 的二进制表示中没有相邻的 1。

计数 $[1, N]$ 中无相邻 1 的数即为 Fibonacci 数位 DP。设 $f[i]$ 为 $i$ 位二进制数中无相邻 1 的个数：$f[0]=1, f[1]=2, f[i]=f[i-1]+f[i-2]$。遍历 $N$ 的二进制位，遇到 1 时累加 $f[i]$，遇到连续两个 1 则提前终止。

时间复杂度 $O(\log N)$。

### 方向二：暴力枚举验证（小数据）

直接枚举 $1 \sim N$，对每个 $n$ 检查 $n \oplus 2n \oplus 3n == 0$。复杂度 $O(N)$，仅适用于 $N \le 10^6$。

### 方向三：Zeckendorf 表示

利用 Zeckendorf 定理（每个正整数可唯一表示为不连续 Fibonacci 数之和），计数本质是 Fibonacci 计数系统下的问题。

### 时间复杂度

标准解法 $O(\log N)$，$N = 2^{30}$ 时瞬间完成。
