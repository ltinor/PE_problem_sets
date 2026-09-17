# Problem 793（PE 793）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=793](https://projecteuler.net/problem=793)。

## **Median of Products**

Let $S_i$ be an integer sequence produced with the following pseudo-random number generator:
- $S_0 = 290797$
- $S_{i+1} = S_i ^2 \bmod 50515093$

Let $M(n)$ be the median of the pairwise products $ S_i S_j $ for $0 \le i \lt j \lt n$.

You are given $M(3) = 3878983057768$ and $M(103) = 492700616748525$.

Find $M(1\ 000\ 003)$.

## **乘积的中位数**

记$S_i$为由如下伪随机数生成器给出的整数列：
- $S_0 = 290797$
- $S_{i+1} = S_i ^2 \bmod 50515093$

对于任意$0 \le i \lt j \lt n$，记$M(n)$为所有乘积$ S_i S_j $的中位数。

已知$M(3) = 3878983057768$，$M(103) = 492700616748525$。

求$M(1\ 000\ 003)$。

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

