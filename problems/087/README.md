# Prime Power Triples

来源：改编自 Project Euler Problem 87

## 原题意

求在小于五千万的数中，可以表示为 $p^2 + q^3 + r^4$（$p,q,r$ 均为素数）的不同值的个数。

## 题目

给定正整数 $N$，求所有满足 $p^2 + q^3 + r^4 < N$（$p,q,r$ 均为素数）的不同值的个数。

## 数据范围

$1 \leq N \leq 5 \times 10^7$

## 算法

筛素数（上限 $\sqrt{N}$），分别预计算所有 $p^2, q^3, r^4 < N$，三重循环枚举并用 `unordered_set` 去重。std 与 brute 使用相同算法。

时间复杂度：约 $O(\pi(\sqrt{N}) \cdot \pi(\sqrt[3]{N}) \cdot \pi(\sqrt[4]{N}))$
