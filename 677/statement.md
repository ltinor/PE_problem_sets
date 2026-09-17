# Problem 677（PE 677）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=677](https://projecteuler.net/problem=677)。

## **Coloured Graphs**

Let $g(n)$ be the number of **undirected graphs** with $n$ nodes satisfying the following properties:
- The graph is connected and has no cycles or multiple edges.
- Each node is either red, blue, or yellow.
- A red node may have no more than $4$ edges connected to it.
- A blue or yellow node may have no more than $3$ edges connected to it.
- An edge may not directly connect a yellow node to a yellow node.

For example, $g(2)=5$, $g(3)=15$, and $g(4) = 57$.
You are also given that $g(10) = 710249$ and $g(100) \equiv 919747298 \pmod{1\ 000\ 000\ 007}$.

Find $g(10\ 000) \bmod 1\ 000\ 000\ 007$.

## **图染色**

记$g(n)$为有$n$个结点并满足以下性质的**无向图**总数：
- 该图是连通图、无环、无重边。
- 每个结点被染上红色、蓝色或黄色之一。
- 每个红色结点至多与$4$条边相连。
- 每个蓝色或黄色结点至多与$3$条边相连。
- 黄色结点之间不能直接相连。

例如，$g(2)=5$，$g(3)=15$，$g(4) = 57$。
还已知$g(10) = 710249$，$g(100) \equiv 919747298 \pmod{1\ 000\ 000\ 007}$。

求$g(10\ 000) \bmod 1\ 000\ 000\ 007$。

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

