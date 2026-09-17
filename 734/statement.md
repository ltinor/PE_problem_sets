# Problem 734（PE 734）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=734](https://projecteuler.net/problem=734)。

## **A bit of prime**

The <i>logical-OR</i> of two bits is $0$ if both bits are $0$, otherwise it is $1$.
The <i>bitwise-OR</i> of two positive integers performs a <i>logical OR</i> operation on each pair of corresponding bits in the binary expansion of its inputs.

For example, the bitwise-OR of $10$ and $6$ is $14$ because $10 = 1010_2$, $6 = 0110_2$ and $14 = 1110_2$.

Let $T(n, k)$ be the number of $k$-tuples $(x_1, x_2,\cdots,x_k)$ such that
- every $x_i$ is a prime $\leq n$
- the bitwise-OR of the tuple is a prime $\leq n$

For example, $T(5, 2)=5$. The five $2$-tuples are $(2, 2)$, $(2, 3)$, $(3, 2)$, $(3, 3)$ and $(5, 5)$.

You are given $T(100, 3) = 3355$ and $T(1000, 10) \equiv 2071632 \pmod{1\ 000\ 000\ 007}$.

Find $T(10^6,999983)$. Give your answer modulo $1\ 000\ 000\ 007$.

## **质数与位运算**

在数的二进制表示下，每一位数字称为一个比特。两个比特之间的<i class-zh>逻辑或</i>定义如下：若这两个比特均为$0$，则结果为$0$，否则结果为$1$。
两个正整数的<i class=zh>按位或</i>定义如下：将这两个正整数表示成二进制，并将对应位置的比特进行<i class=zh>逻辑或</i>运算。

例如，$10$和$6$的按位或结果为$14$，这是因为$10 = 1010_2$，$6 = 0110_2$，而$14 = 1110_2$。

记$T(n, k)$为满足以下条件的$k$-元组$(x_1, x_2,\cdots,x_k)$的数目：
- 每个$x_i$均为小于等于$n$的质数；
- 元组中所有数按位或的结果是一个小于等于$n$的质数。

例如，$T(5, 2)=5$，这五个$2$-元组分别是$(2, 2)$、$(2, 3)$、$(3, 2)$、$(3, 3)$和$(5, 5)$。

已知$T(100, 3) = 3355$，$T(1000, 10) \equiv 2071632 \pmod{1\ 000\ 000\ 007}$。

求$T(10^6,999983)$，并将你的答案对$1\ 000\ 000\ 007$取余。

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

