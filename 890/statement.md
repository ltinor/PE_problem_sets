# Problem 890（PE 890）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=890](https://projecteuler.net/problem=890)。

## **Binary Partitions**

Let $p(n)$ be the number of ways to write $n$ as the sum of powers of two, ignoring order.

For example, $p(7) = 6$, the partitions being
$$
\begin{aligned}
7 & = 1+1+1+1+1+1+1 \\\\
  & =1+1+1+1+1+2 \\\\
  & =1+1+1+2+2 \\\\
  & =1+1+1+4 \\\\
  & =1+2+2+2 \\\\
  & =1+2+4
\end{aligned}
$$
You are also given $p(7^7) \equiv 144548435 \pmod {10^9+7}$.

Find $p(7^{777})$. Give your answer modulo $10^9 + 7$.

## **二进制分拆**

记$p(n)$为将$n$写成二的幂之和的方法数，不计顺序。

例如，$p(7) = 6$，对应的分拆包括：
$$
\begin{aligned}
7 & = 1+1+1+1+1+1+1 \\\\
& =1+1+1+1+1+2 \\\\
& =1+1+1+2+2 \\\\
& =1+1+1+4 \\\\
& =1+2+2+2 \\\\
& =1+2+4
\end{aligned}
$$
已知$p(7^7) \equiv 144548435 \pmod {10^9+7}$。

求$p(7^{777})$，并对$10^9 + 7$取余作为你的答案。

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

