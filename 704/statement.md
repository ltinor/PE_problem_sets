# Problem 704（PE 704）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=704](https://projecteuler.net/problem=704)。

## **Factors of Two in Binomial Coefficients**

Define $g(n, m)$ to be the largest integer $k$ such that $2^k$ divides $\binom{n}m$. For example, $\binom{12}5 = 792 = 2^3 \cdot 3^2 \cdot 11$, hence $g(12, 5) = 3$. Then define $F(n) = \max \{ g(n, m) : 0 \le m \le n \}$. $F(10) = 3$ and $F(100) = 6$.

Let $S(N)$ = $\displaystyle\sum_{n=1}^N{F(n)}$. You are given that $S(100) = 389$ and $S(10^7) = 203222840$.

Find $S(10^{16})$.

## **二项式系数中的质因数二**

记$g(n, m)$为使得$2^k$整除$\binom{n}m$的最大整数$k$。例如，$\binom{12}5 = 792 = 2^3 \cdot 3^2 \cdot 11$，因此$g(12, 5) = 3$。再定义$F(n) = \max \{ g(n, m) : 0 \le m \le n \}$。已知$F(10) = 3$，$F(100) = 6$。

记$S(N)$ = $\displaystyle\sum_{n=1}^N{F(n)}$。已知$S(100) = 389$，$S(10^7) = 203222840$。

求$S(10^{16})$。

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

