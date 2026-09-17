# Problem 701（PE 701）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=701](https://projecteuler.net/problem=701)。

## **Random connected area**

Consider a rectangle made up of $W \times H$ square cells each with area $1$.
Each cell is independently coloured black with probability $0.5$ otherwise white. Black cells sharing an edge are assumed to be connected.
Consider the maximum area of connected cells.

Define $E(W,H)$ to be the expected value of this maximum area. For example, $E(2,2)=1.875$, as illustrated below.

![3 random connected area](/resources/images/0701_randcon.png)

You are also given $E(4, 4) = 5.76487732$, rounded to $8$ decimal places.

Find $E(7, 7)$, rounded to $8$ decimal places.

## **随机连通区域**

考虑由$W \times H$个面积为$1$的正方形方格组成的长方形。
每一格正方形独立地以$0.5$的概率染上黑色或白色。如果两个黑色正方形格共用一条边，则认为它们是连通的。
考虑最大连通区域的面积。

记$E(W,H)$为最大连通区域的面积的期望值。例如，$E(2,2)=1.875$，如下图所示（其中数字表示最大连通区域的面积）。

![随机连通区域](/resources/images/0701_randcon.png)

已知$E(4, 4) = 5.76487732$，保留$8$位小数。

求$E(7, 7)$并保留$8$位小数。

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

