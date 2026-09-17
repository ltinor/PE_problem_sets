# Problem 795（PE 795）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=795](https://projecteuler.net/problem=795)。

## **Alternating GCD Sum**

For a positive integer $n$, the function $g(n)$ is defined as

$$\displaystyle g(n)=\sum_{i=1}^{n} (-1)^i \gcd \left(n,i^2\right)$$

For example, $g(4) = -\gcd \left(4,1^2\right) + \gcd \left(4,2^2\right) - \gcd \left(4,3^2\right) + \gcd \left(4,4^2\right) = -1+4-1+4=6$.<br />
You are also given $g(1234)=1233$.

Let $\displaystyle G(N) = \sum_{n=1}^N g(n)$. You are given $G(1234) = 2194708$.

Find $G(12345678)$.

## **交错最大公约数求和**

对于正整数$n$，定义函数$g(n)$为

$$\displaystyle g(n)=\sum_{i=1}^{n} (-1)^i \gcd \left(n,i^2\right)$$

例如，$g(4) = -\gcd \left(4,1^2\right) + \gcd \left(4,2^2\right) - \gcd \left(4,3^2\right) + \gcd \left(4,4^2\right) = -1+4-1+4=6$。<br />
已知$g(1234)=1233$。

记$\displaystyle G(N) = \sum_{n=1}^N g(n)$。已知$G(1234) = 2194708$。

求$G(12345678)$。

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

