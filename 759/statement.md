# Problem 759（PE 759）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=759](https://projecteuler.net/problem=759)。

## **A squared recurrence relation**

The function $f$ is defined for all positive integers as follows:
$$f(1)=1$$
$$f(2n)=2f(n)$$
$$f(2n+1)=2n+1+2f(n)+\frac{1}{n}f(n)$$
It can be proven that $f(n)$ is integer for all values of $n$.

The function $S(n)$ is defined as $S(n) = \displaystyle \sum_{i=1}^n f(i) ^2$.

For example, $S(10)=1530$ and $S(10^2)=4798445$.

Find $S(10^{16})$. Give your answer modulo $1\ 000\ 000\ 007$.

## **递推数列的平方和**

定义在正整数上的函数$f$满足以下递推关系：
$$f(1)=1$$
$$f(2n)=2f(n)$$
$$f(2n+1)=2n+1+2f(n)+\frac{1}{n}f(n)$$
可以证明，对于任意$n$，$f(n)$的取值均为整数。

再定义函数$S(n)$为$S(n) = \displaystyle \sum_{i=1}^n f(i) ^2$。

例如，$S(10)=1530$，$S(10^2)=4798445$。

求$S(10^{16})$，并将你的答案对$1\ 000\ 000\ 007$取余。

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

