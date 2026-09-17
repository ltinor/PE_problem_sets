# Problem 755（PE 755）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=755](https://projecteuler.net/problem=755)。

## **Not Zeckendorf**

Consider the Fibonacci sequence $\{1,2,3,5,8,13,21,\ldots\}$.

We let $f(n)$ be the number of ways of representing an integer $n\ge 0$ as the sum of different Fibonacci numbers.
For example, $16 = 3+13 = 1+2+13 = 3+5+8 = 1+2+5+8$ and hence $f(16) = 4$. By convention $f(0) = 1$.

Further we define
$$\displaystyle S(n) = \sum_{k=0}^n f(k)$$
You are given $S(100) = 415$ and $S(10^4) = 312807$.

Find $\displaystyle S(10^{13})$.

## **非齐肯多夫表示**

考虑斐波那契数列$\{1,2,3,5,8,13,21,\ldots\}$。

记$f(n)$为将整数$n\ge 0$表示为不同斐波那契数之和的方法数。
例如，$16 = 3+13 = 1+2+13 = 3+5+8 = 1+2+5+8$，因此$f(16) = 4$。按照惯例，记$f(0) = 1$。

我们进一步定义
$$\displaystyle S(n) = \sum_{k=0}^n f(k)$$
已知$S(100) = 415$，$S(10^4) = 312807$。

求$\displaystyle S(10^{13})$。

<i class=zh>译注</i>：齐肯多夫表示是指将一个整数表示为<i class=zh>不连续</i>的不同斐波那契数之和，根据齐肯多夫定理可知该表示唯一；而本题不要求不连续。

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

