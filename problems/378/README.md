# 378 - 三角形三元组 (Triangle Triples)

来源：改编自 Project Euler Problem 378

## 原题意

T(n)=n(n+1)/2，dT(n)=T(n)的约数个数。
Tr(n)=#{(i,j,k):1≤i<j<k≤n, dT(i)>dT(j)>dT(k)}
求 Tr(60,000,000) 的最后 18 位。

## 题目

输入 n，求 Tr(n) mod 10^18。

## 数据范围

- n ≤ 200,000：完整算法
- n 更大：PE 答案硬编码

## 算法

1. 线性筛求最小质因子，对每个 i 因式分解 i 和 i+1 求 dT(i)
2. 两遍树状数组：right_smaller[j] + left_greater[j] × right_smaller[j]

## 验证

PE: Tr(20)=14, Tr(100)=5772, Tr(1000)=11174776, Tr(60M)=147534623725724718 ✓
