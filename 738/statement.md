# Problem 738（PE 738）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=738](https://projecteuler.net/problem=738)。

## **Counting Ordered Factorisations**

Define $d(n,k)$ to be the number of ways to write $n$ as a product of $k$ ordered integers
$$n = x_1\times x_2\times x_3\times \ldots\times x_k\qquad 1\le x_1\le x_2\le\ldots\le x_k$$

Further define $D(N,K)$ to be the sum of $d(n,k)$ for $1\le n\le N$ and $1\le k\le K$.

You are given that $D(10, 10) = 153$ and $D(100, 100) = 35384$.

Find $D(10^{10},10^{10})$ giving your answer modulo $1\ 000\ 000\ 007$.

## **有序因数分解计数**

记$d(n,k)$为将$n$表示为$k$个递增整数之积的方式数
$$n = x_1\times x_2\times x_3\times \ldots\times x_k\qquad 1\le x_1\le x_2\le\ldots\le x_k$$

再记$D(N,K)$为所有$1\le n\le N$和$1\le k\le K$对应的$d(n,k)$之和。

已知$D(10, 10) = 153$，$D(100, 100) = 35384$。

求$D(10^{10},10^{10})$，并将你的答案对$1\ 000\ 000\ 007$取余。

---

## 输入格式

（待人工补充：请对照 code/std.cpp 的读取约定描述。）

## 输出格式

（待人工补充。）

## 样例

（无 data 数据，待人工补充。）

---

## 数据范围

（待人工补充；原题参数范围见上方原题描述。）

