# Problem 712（PE 712）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=712](https://projecteuler.net/problem=712)。

## **Exponent Difference**

For any integer $n>0$ and prime number $p$, define $\nu_p(n)$ as the greatest integer $r$ such that $p^r$ divides $n$. 

Define 
$$D(n, m)  = \sum_{p \text{ prime}} \left| \nu_p(n) - \nu_p(m)\right|.$$
For example, $D(14,24) = 4$.

Furthermore, define 
$$S(N) = \sum_{1 \le n, m \le N} D(n, m).$$
You are given $S(10) = 210$ and $S(10^2) = 37018$.

Find $S(10^{12})$. Give your answer modulo $1\ 000\ 000\ 007$.

## **指数差异**

对于任意整数$n>0$和素数$p$，记$\nu_p(n)$为使得$p^r$整除$n$的最大整数$r$。

记 
$$D(n, m)  = \sum_{p \text{为素数}} \left| \nu_p(n) - \nu_p(m)\right|.$$
例如，$D(14,24) = 4$。

进一步地，记
$$S(N) = \sum_{1 \le n, m \le N} D(n, m).$$
已知$S(10) = 210$，$S(10^2) = 37018$。

求$S(10^{12})$并将你的答案对$1\ 000\ 000\ 007$取余。

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

