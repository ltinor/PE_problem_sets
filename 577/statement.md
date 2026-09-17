# Problem 577（PE 577）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=577](https://projecteuler.net/problem=577)。

## **Counting hexagons**

An equilateral triangle with integer side length $n \ge 3$ is divided into $n^2$ equilateral triangles with side length 1 as shown in the diagram below.
The vertices of these triangles constitute a triangular lattice with $\frac{(n+1)(n+2)} 2$ lattice points.

Let $H(n)$ be the number of all regular hexagons that can be found by connecting 6 of these points.

<center><img src="/resources/images/0577_counting_hexagons.png" alt="p577_counting_hexagons.png"></center>

For example, $H(3)=1$, $H(6)=12$ and $H(20)=966$.

Find $\displaystyle \sum_{n=3}^{12345} H(n)$.

## **数六边形**

边长为整数$n \ge 3$的等边三角形可以被分成$n^2$个边长为1的小等边三角形，如下图所示。
这些小三角形的$\frac{(n+1)(n+2)} 2$个顶点构成了一个三角形的格阵。

记$H(n)$为从这些顶点中取6个点构成的正六边形的数目。

<center><img src="/resources/images/0577_counting_hexagons.png" alt="p577_counting_hexagons.png">
<p>当$n=3$时只有一个六边形</p></center>

例如，$H(3)=1$，$H(6)=12$，而$H(20)=966$。

求$\displaystyle \sum_{n=3}^{12345} H(n)$。

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

