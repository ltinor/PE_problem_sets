# Problem 791（PE 791）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=791](https://projecteuler.net/problem=791)。

## **Average and Variance**

Denote the average of $k$ numbers $x_1, ..., x_k$ by $\bar{x} = \frac{1}{k} \sum_i x_i$. Their variance is defined as $\frac{1}{k} \sum_i \left( x_i - \bar{x} \right) ^ 2$.

Let $S(n)$ be the sum of all quadruples of integers $(a,b,c,d)$ satisfying $1 \leq a \leq b \leq c \leq d \leq n$ such that their average is exactly twice their variance.

For $n=5$, there are $5$ such quadruples, namely: $(1, 1, 1, 3), (1, 1, 3, 3), (1, 2, 3, 4), (1, 3, 4, 4), (2, 2, 3, 5)$.

Hence $S(5)=48$. You are also given $S(10^3)=37048340$.

Find $S(10^8)$. Give your answer modulo $433494437$.

## **均值与方差**

记$k$个数$x_1, ..., x_k$的均值为$\bar{x} = \frac{1}{k} \sum_i x_i$，并记其方差为$\frac{1}{k} \sum_i \left( x_i - \bar{x} \right) ^ 2$。

考虑所有满足$1 \leq a \leq b \leq c \leq d \leq n$的整数四元组$(a,b,c,d)$，记$S(n)$为其中均值恰好为方差两倍的四元组之和。

对于$n=5$，共有$5$个满足上述条件的四元组，分别是$(1, 1, 1, 3), (1, 1, 3, 3), (1, 2, 3, 4), (1, 3, 4, 4), (2, 2, 3, 5)$。

因此，$S(5)=48$。已知$S(10^3)=37048340$。

求$S(10^8)$，并将你的答案对$433494437$取余。

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

