# Problem 684（PE 684）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=684](https://projecteuler.net/problem=684)。

## **Inverse Digit Sum**

Define $s(n)$ to be the smallest number that has a digit sum of $n$. For example $s(10) = 19$.
Let $\displaystyle S(k) = \sum_{n=1}^k s(n)$. You are given $S(20) = 1074$.

Further let $f_i$ be the Fibonacci sequence defined by $f_0=0, f_1=1$ and $f_i=f_{i-2}+f_{i-1}$ for all $i \ge 2$.

Find $\displaystyle \sum_{i=2}^{90} S(f_i)$. Give your answer modulo $1\ 000\ 000\ 007$.

## **数字和的逆函数**

记 $s(n)$为最小的数字和为$n$的数。例如$s(10) = 19$。
记$\displaystyle S(k) = \sum_{n=1}^k s(n)$。已知$S(20) = 1074$。

记$f_i$为斐波那契数列，其中$f_0=0$，$f_1=1$，对任意$i \ge 2$有$f_i=f_{i-2}+f_{i-1}$。

求$\displaystyle \sum_{i=2}^{90} S(f_i)$。将你的答案对$1\ 000\ 000\ 007$取余。

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

