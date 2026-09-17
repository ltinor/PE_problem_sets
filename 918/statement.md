# Problem 918（PE 918）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=918](https://projecteuler.net/problem=918)。

## **Recursive Sequence Summation**

The sequence $a_n$ is defined by $a_1=1$, and then recursively for $n\geq 1$:
$$\begin{aligned}
a_{2n} & =2a_n\\\\
a_{2n+1} & =a_n-3a_{n+1}
\end{aligned}$$
The first ten terms are $1, 2, -5, 4, 17, -10, -17, 8, -47, 34$.<br/>
Define $\displaystyle S(N) = \sum_{n=1}^N a_n$. You are given $S(10) = -13$.<br/>
Find $S(10^{12})$.

## **递归序列求和**

序列$a_n$的定义为：$a_1=1$；对于$n\geq 1$，递归定义：
$$\begin{aligned}
a_{2n} & =2a_n\\\\
a_{2n+1} & =a_n-3a_{n+1}
\end{aligned}$$
该序列的前十项是$1, 2, -5, 4, 17, -10, -17, 8, -47, 34$。<br/>
定义$\displaystyle S(N) = \sum_{n=1}^N a_n$。已知$S(10) = -13$。<br/>
求$S(10^{12})$。

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

