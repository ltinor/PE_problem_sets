# 099 — Largest Exponential

来源：改编自 Project Euler Problem 99

## 原题意

给定 `base_exp.txt` 中 1000 行 $(a, b)$，比较 $a^b$ 的大小，找出最大的 $a^b$ 所在的行号（1-indexed）。

答案：709。

## 题目

输入 $N$ 和 $N$ 行 $(a, b)$，输出最大的 $a^b$ 所在的行号（1-indexed）。

## 数据范围

- $1 \le N \le 1000$
- $2 \le a, b \le 1000$

## 算法

比较 $b \cdot \ln(a)$。时间复杂度 $O(N)$。
