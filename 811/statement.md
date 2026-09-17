# Problem 811（PE 811）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=811](https://projecteuler.net/problem=811)。

## **Bitwise Recursion**

Let $b(n)$ be the largest power of $2$ that divides $n$. For example $b(24) = 8$.

Define the recursive function:
\begin{aligned}
\begin{split}
A(0) & = 1\\\\
A(2n) & = 3A(n) + 5A\big(2n - b(n)\big)  \qquad n \gt 0\\\\
A(2n+1) & = A(n)
\end{split}
\end{aligned}
and let $H(t,r) = A\big((2^t+1)^r\big)$.

You are given $H(3,2) = A(81) = 636056$.

Find $H(10^{14}+31,62)$. Give your answer modulo $1\ 000\ 062\ 031$. 

## **按位递归**

记$b(n)$为最大的整除$n$的$2$的幂，例如$b(24) = 8$。

定义如下递归关系式：
\begin{aligned}
\begin{split}
A(0) & = 1\\\\
A(2n) & = 3A(n) + 5A\big(2n - b(n)\big)  \qquad n \gt 0\\\\
A(2n+1) & = A(n)
\end{split}
\end{aligned}
并记$H(t,r) = A\big((2^t+1)^r\big)$。

已知$H(3,2) = A(81) = 636056$。

求$H(10^{14}+31,62)$，并将你的答案对$1\ 000\ 062\ 031$取余。

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

