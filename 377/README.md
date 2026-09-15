# 377 - 数字和 (Sum of Digits, experience 13)

来源：改编自 Project Euler Problem 377

## 原题意

记 f(n) 为所有无零数字且各位和为 n 的正整数之和。
求 Σ_{i=1}^{17} f(13^i) 的最后 9 位。

## 题目

输入 K，求 Σ_{i=1}^K f(13^i) mod 10^9。

## 数据范围

- K ≤ 17

## 算法

DP + 矩阵快速幂。cnt[n] = 和为 n 的无零数字个数，sum[n] = 这些数字之和。
递推：cnt[n] = Σ cnt[n-d]，sum[n] = Σ (10·sum[n-d] + d·cnt[n-d])。
使用 18×18 矩阵快速幂计算 f(13^i)。

## 验证

PE: Σ f(13^i) mod 10^9 = 732385277 ✓
