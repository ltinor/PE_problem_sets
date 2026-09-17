# Problem 854（PE 854）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=854](https://projecteuler.net/problem=854)。

## **Pisano Periods 2**

For every positive integer $n$ the Fibonacci sequence modulo $n$ is periodic. The period depends on the value of $n$. This period is called the **Pisano period** for $n$, often shortened to $\pi(n)$.

Define $M(p)$ as the largest integer $n$ such that $\pi(n) = p$, and define $M(p) = 1$ if there is no such $n$.<br />
For example, there are three values of $n$ for which $\pi(n)$ equals $18$: $19, 38, 76$. Therefore $M(18) = 76$.

Let the product function $P(n)$ be: 
$$P(n)=\prod_{p = 1}^{n}M(p).$$
You are given: $P(10)=264$.

Find $P(1\ 000\ 000)\bmod 1\ 234\ 567\ 891$.

## **皮萨诺周期（二）**

对任意正整数$n$，斐波那契数列对$n$取余的结果都是周期数列，其周期取决于$n$的取值。这一周期被称为$n$的**皮萨诺周期**，通常记为$\pi(n)$。

定义$M(p)$为最大的、满足$\pi(n) = p$的整数$n$。若不存在这样的$n$，定义$M(p)=1$。<br />
例如，有三个$n$满足$\pi(n)$等于$18$，分别是$19$、$38$和$76$，因此$M(18) = 76$。

记函数$P(n)$为：
$$P(n)=\prod_{p = 1}^{n}M(p)$$
已知$P(10)=264$。

求$P(1\ 000\ 000)\bmod 1\ 234\ 567\ 891$。

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

