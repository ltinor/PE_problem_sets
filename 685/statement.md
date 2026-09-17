# Problem 685（PE 685）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=685](https://projecteuler.net/problem=685)。

## **Inverse Digit Sum II**

Writing down the numbers which have a digit sum of $10$ in ascending order, we get: $19, 28, 37, 46, 55, 64, 73, 82, 91, 109, 118, \dots$

Let $f(n,m)$ be the $m^{\text{th}}$ occurrence of the digit sum $n$. For example, $f(10,1)=19$, $f(10,10)=109$ and $f(10,100)=1423$.

Let $\displaystyle S(k)=\sum_{n=1}^k f(n^3,n^4)$. For example $S(3)=7128$ and $S(10)\equiv 32287064 \mod 1\ 000\ 000\ 007$.

Find $S(10\ 000)$ modulo $1\ 000\ 000\ 007$.

## **数字和的逆函数II**

从小到大排列，数字和为$10$的数包括：$19, 28, 37, 46, 55, 64, 73, 82, 91, 109, 118, \dots$

记$f(n,m)$为第$m$个数字和为$n$的数。例如，$f(10,1)=19$，$f(10,10)=109$，$f(10,100)=1423$。

记$\displaystyle S(k)=\sum_{n=1}^k f(n^3,n^4)$。例如$S(3)=7128$，$S(10)\equiv 32287064 \bmod 1\ 000\ 000\ 007$。

求$S(10\ 000)$并对$1\ 000\ 000\ 007$取余。

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

