# Problem 689（PE 689）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=689](https://projecteuler.net/problem=689)。

## **Binary Series**

For $0 \le x \lt 1$, define $d_i(x)$ to be the $i$th digit after the binary point of the binary representation of $x$.
For example $d_2(0.25) = 1$, $d_i(0.25) = 0$ for $i \ne 2$.

Let $f(x) = \displaystyle{\sum_{i=1}^{\infty}\frac{d_i(x)}{i^2}}$.

Let $p(a)$ be probability that $f(x) \gt a$, given that $x$ is uniformly distributed between $0$ and $1$.

Find $p(0.5)$. Give your answer rounded to $8$ digits after the decimal point.

## **二进制级数**

对于任意$0 \le x \lt 1$，记$d_i(x)$为$x$的二进制表示中小数点后第$i$位数字。
例如，$d_2(0.25) = 1$，而对所有$i \ne 2$则有$d_i(0.25)=0$。

记$f(x) = \displaystyle{\sum_{i=1}^{\infty}\frac{d_i(x)}{i^2}}$。

若$x$在$0$和$1$之间均匀分布，记$p(a)$为$f(x) \gt a$的概率。

求$p(0.5)$，并将你的答案保留小数点后$8$位数字。

---

## 输入格式

见 code/std.cpp 的读取约定。

## 输出格式

计算结果。

---

## 样例

见原题描述中的样例。

---

## 数据范围

见原题参数范围。
