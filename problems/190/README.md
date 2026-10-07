# 190 — 最大化加权乘积

来源：改编自 Project Euler Problem 190

## 原题意

对于正整数 $m$，定义 $P_m = \prod_{i=1}^m x_i^i$，其中 $x_i$ 为正实数且满足 $\sum_{i=1}^m x_i = m$。记 $P_m$ 的最大值为 $[P_m]$。求 $\sum_{m=2}^{15} \lfloor P_m \rfloor$。

答案：371048281

## 题目

参数化版本：输入 $M$（$M \le 15$），求 $\sum_{m=2}^{M} \lfloor P_m \rfloor$。

## 数据范围

- $2 \le M \le 15$

## 算法

使用拉格朗日乘数法。在约束 $\sum x_i = m$ 下最大化 $\prod x_i^i$。

取对数 $L = \sum i \ln x_i - \lambda(\sum x_i - m)$。

对 $x_i$ 求偏导：$\frac{i}{x_i} - \lambda = 0 \implies x_i = i/\lambda$。

代入约束：$\sum i/\lambda = m \implies \lambda = \frac{m(m+1)}{2m} = \frac{m+1}{2}$。

所以 $x_i = \frac{2i}{m+1}$，$P_m = \prod_{i=1}^m \left(\frac{2i}{m+1}\right)^i$。

直接用浮点计算 $P_m$ 并取 floor。
