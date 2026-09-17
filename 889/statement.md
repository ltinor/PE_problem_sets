# Problem 889（PE 889）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=889](https://projecteuler.net/problem=889)。

## **Rational Blancmange**

Recall the blancmange function from <a href="/226">Problem 226</a>: $T(x) = \sum\limits_{n = 0}^\infty\dfrac{s(2^nx)}{2^n}$, where $s(x)$ is the distance from $x$ to the nearest integer.

For positive integers $k, t, r$, we write 
$$F(k, t, r) = (2^{2k} - 1)T\left(\frac{(2^t + 1)^r}{2^k + 1}\right).$$
It can be shown that $F(k, t, r)$ is always an integer.<br/>
For example, $F(3, 1, 1) = 42$, $F(13, 3, 3) = 23093880$ and $F(103, 13, 6) \equiv 878922518\pmod {1\ 000\ 062\ 031}$.

Find $F(10^{18} + 31, 10^{14} + 31, 62)$. Give your answer modulo $1\ 000\ 062\ 031$.

## **有理牛奶冻**

考虑<a href="/226">226题</a>中提及的牛奶冻函数：$T(x) = \sum\limits_{n = 0}^\infty\dfrac{s(2^nx)}{2^n}$，其中$s(x)$是$x$到最近整数的距离。

对于正整数$k, t, r$，记：
$$F(k, t, r) = (2^{2k} - 1)T\left(\frac{(2^t + 1)^r}{2^k + 1}\right)$$
可以证明$F(k, t, r)$总是一个整数。<br/>
例如，$F(3, 1, 1) = 42$，$F(13, 3, 3) = 23093880$，$F(103, 13, 6) \equiv 878922518\pmod {1\ 000\ 062\ 031}$。

求$F(10^{18} + 31, 10^{14} + 31, 62)$，并对$1\ 000\ 062\ 031$取余作为你的答案。

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

