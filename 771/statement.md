# Problem 771（PE 771）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=771](https://projecteuler.net/problem=771)。

## **Pseudo Geometric Sequences**

We define a <i>pseudo-geometric sequence</i> to be a finite sequence $a_0, a_1, \ldots, a_n$ of positive integers, satisfying the following conditions:
- $n \geq 4$, i.e. the sequence has at least 5 terms.
- $0 < a_0 < a_1 < \ldots < a_n$, i.e. the sequence is strictly increasing.
- $| a_i^2 - a_{i - 1}a_{i + 1} | \le 2$ for $1 \le i \le n-1$.

Let $G(N)$ be the number of different pseudo-geometric sequences whose terms do not exceed $N$.<br />
For example, $G(6) = 4$, as the following $4$ sequences give a complete list:

$$1, 2, 3, 4, 5 \qquad 1, 2, 3, 4, 6 \qquad 2, 3, 4, 5, 6 \qquad 1, 2, 3, 4, 5, 6$$

Also, $G(10) = 26$, $G(100) = 4710$ and $G(1000) = 496805$.

Find $G(10^{18})$. Give your answer modulo $1\ 000\ 000\ 007$.

## **伪等比数列**

我们定义满足如下条件的有限正整数数列$a_0, a_1, \ldots, a_n$为<i class=zh>伪等比数列</i>：
- $n \geq 4$，即数列至少有5项。
- $0 < a_0 < a_1 < \ldots < a_n$，即数列严格递增。
- 对于$1 \le i \le n-1$，均有$| a_i^2 - a_{i - 1}a_{i + 1} | \le 2$。

记$G(N)$为各项均不超过$N$的不同伪等比数列的总数。<br />
例如，$G(6) = 4$，这$4$种数列如下所示：

$$1, 2, 3, 4, 5 \qquad 1, 2, 3, 4, 6 \qquad 2, 3, 4, 5, 6 \qquad 1, 2, 3, 4, 5, 6$$

此外还已知$G(10) = 26$，$G(100) = 4710$以及$G(1000) = 496805$。

求$G(10^{18})$，并将你的答案对$1\ 000\ 000\ 007$取余。

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

