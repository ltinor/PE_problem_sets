# Problem 708（PE 708）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=708](https://projecteuler.net/problem=708)。

## **Twos are all you need**

A positive integer, $n$, is factorised into prime factors. We define $f(n)$ to be the product when each prime factor is replaced with $2$. In addition we define $f(1)=1$.

For example, $90 = 2\times 3\times 3\times 5$, then replacing the primes, $2\times 2\times 2\times 2 = 16$, hence $f(90) = 16$.
 
Let $\displaystyle S(N)=\sum_{n=1}^{N} f(n)$. You are given $S(10^8)=9613563919$.

Find $S(10^{14})$.

## **只需要二**

对正整数$n$作质因数分解，并记$f(n)$为将所有质因数均替换为$2$时的新乘积；此外记$f(1)=1$。

例如，$90 = 2\times 3\times 3\times 5$，将质因数替换后得$2\times 2\times 2\times 2 = 16$，因此$f(90) = 16$。

记$\displaystyle S(N)=\sum_{n=1}^{N} f(n)$。已知$S(10^8)=9613563919$。

求$S(10^{14})$。

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

