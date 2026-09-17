# Problem 772（PE 772）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=772](https://projecteuler.net/problem=772)。

## **Balanceable $k$-bounded partitions**

A $k$-bounded partition of a positive integer $N$ is a way of writing $N$ as a sum of positive integers not exceeding $k$.

A balanceable partition is a partition that can be further divided into two parts of equal sums.

For example, $3 + 2 + 2 + 2 + 2 + 1$ is a balanceable $3$-bounded partition of $12$ since $3 + 2 + 1 = 2 + 2 + 2$. Conversely, $3 + 3 + 3 + 1$ is a $3$-bounded partition of $10$ which is not balanceable.

Let $f(k)$ be the smallest positive integer $N$ all of whose $k$-bounded partitions are balanceable. For example, $f(3) = 12$ and $f(30) \equiv 179092994 \pmod {1\ 000\ 000\ 007}$.

Find $f(10^8)$. Give your answer modulo $1\ 000\ 000\ 007$.

## **可平衡$k$-有界分拆**

正整数$N$的分拆是指将$N$写作一系列正整数之和。若这些正整数均不超过$k$，则称之为$k$-有界分拆。若这些正整数能分成和相同的两组，则称之为可平衡分拆。

例如，$3 + 2 + 2 + 2 + 2 + 1$是$12$的一种可平衡$3$-有界分拆，因为$3 + 2 + 1 = 2 + 2 + 2$。反之，$3 + 3 + 3 + 1$是$10$的一种$3$-有界分拆，但不是可平衡分拆。

记$f(k)$是最小的正整数$N$，使得其所有的$k$-有界分拆都是可平衡分拆。例如，$f(3) = 12$，$f(30) \equiv 179092994 \pmod {1\ 000\ 000\ 007}$。

求$f(10^8)$，并将你的答案对$1\ 000\ 000\ 007$取余。

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

