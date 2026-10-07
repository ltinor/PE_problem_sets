# 组合选择 (Combinatoric Selections)

来源：改编自 Project Euler Problem 53

## 原题意

对于 $1 \le n \le 100$，求有多少个组合数 $\binom{n}{r}$ 超过一百万。

## 题目

给定多组询问，每组询问给出 $N$ 和 $T$，求对于 $1 \le n \le N$，有多少个组合数 $\binom{n}{r}$（$0 \le r \le n$）的值严格大于 $T$。

## 数据范围

- 询问组数：不超过 $10$
- $1 \le N \le 100$
- $1 \le T \le 10^{12}$

## 算法

- **std**: 使用杨辉三角（Pascal's triangle）递推计算所有 $n \le 100$ 的组合数，使用 `long double` 避免溢出。对于每组询问，枚举 $1 \le n \le N$ 中所有 $r$ 统计大于 $T$ 的组合数个数。
- **brute**: 相同算法，独立实现。
