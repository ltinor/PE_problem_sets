# Problem 747（PE 747）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=747](https://projecteuler.net/problem=747)。

## **Triangular Pizza**

Mamma Triangolo baked a triangular pizza. She wants to cut the pizza into $n$ pieces. She first chooses a point $P$ in the interior (not boundary) of the triangle pizza, and then performs $n$ cuts, which all start from $P$ and extend straight to the boundary of the pizza so that the $n$ pieces are all triangles and all have the same area.

Let $\psi(n)$ be the number of different ways for Mamma Triangolo to cut the pizza, subject to the constraints.
For example, $\psi(3)=7$.

![](/resources/images/0747_PizzaDiag.jpg)

Also $\psi(6)=34$, and $\psi(10)=90$.

Let $\Psi(m)=\displaystyle\sum_{n=3}^m \psi(n)$. You are given $\Psi(10)=345$ and $\Psi(1000)=172166601$.

Find $\Psi(10^8)$. Give your answer modulo $1\ 000\ 000\ 007$.

## **三角形披萨**

特莱格伦夫人打算把一块三角形的披萨分成$n$片。她先在三角形披萨的内部（而非边缘）选择一个点$P$，然后从点$P$出发切$n$刀至披萨边缘，将披萨分成$n$个面积相同的小三角形。

记$\psi(n)$为满足特莱格伦夫人上述要求的披萨切法。
例如，$\psi(3)=7$。

![](/resources/images/0747_PizzaDiag.jpg)

此外，$\psi(6)=34$，$\psi(10)=90$。

记$\Psi(m)=\displaystyle\sum_{n=3}^m \psi(n)$。已知$\Psi(10)=345$，$\Psi(1000)=172166601$。

求$\Psi(10^8)$，并将你的答案对$1\ 000\ 000\ 007$取余。

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

