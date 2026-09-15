# 941 de Bruijn 组合锁（简单版本）

来源：改编自 Project Euler Problem 941 (de Bruijn's Combination Lock)

## 原题意

C(k,n) 为字典序最小的、包含所有 k^n 个 n 位串的最短序列（de Bruijn 序列）。
原题对 C(10,12) 算每个 12 位串的首次出现位置（Lyndon 排名）并对 10^7 个 LCG 串求和。

## 题目（简单版本）

输入两个整数 k 和 n，输出 C(k,n)。

## 数据范围

- 简单版本：2 ≤ k ≤ 10，2 ≤ n ≤ 6（k^n ≤ 10^6）。

## 算法

FKM：字典序最小的 de Bruijn 序列 = 所有「长度整除 n 的 Lyndon 词」按字典序拼接，
再取周期串前 k^n+n-1 个字符；Lyndon 词用 Duval 算法按字典序生成。

验证：C(3,2)=0010211220。
