# Lexicographic Permutations

来源：改编自 Project Euler Problem 24

## 原题意

数字0-9的字典序排列中，第1000000个排列是 2783915460。

## 题目

给定 N 和 K，求数字 0 ~ (N-1) 的字典序排列中第 K 个排列（排列编号从 1 开始）。

## 数据范围

- $1 \le N \le 10$
- $1 \le K \le N!$

## 算法

std: 康托展开（阶乘数制），逐位确定每一位数字。  
brute: 使用 C++ STL `next_permutation` 生成所有排列，取第 K 个。

时间复杂度：std $O(N^2)$，brute $O(K \cdot N)$。
