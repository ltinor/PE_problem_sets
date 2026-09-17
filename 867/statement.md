# Problem 867（PE 867）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=867](https://projecteuler.net/problem=867)。

## **Tiling Dodecagon**

There are $5$ ways to tile a regular dodecagon of side $1$ with regular polygons of side $1$.

<div style="text-align:center">
<img src="/resources/images/0867_DodecaDiagram.jpg" alt="0867_DodecaDiagram.jpg">
</div>

Let $T(n)$ be the number of ways to tile a regular dodecagon of side $n$ with regular polygons of side 1. Then $T(1) = 5$. You are also given $T(2) = 48$.

Find $T(10)$. Give your answer modulo $10^9+7$.

## **密铺十二边形**

用边长为$1$的正多边形铺满边长为$1$的正十二边形，有$5$种不同的方案：

<div style="text-align:center">
<img src="/resources/images/0867_DodecaDiagram.jpg" alt="0867_DodecaDiagram.jpg">
</div>

记$T(n)$为用边长为$1$的正多边形铺满边长为$n$的正十二边形的方案数，因此$T(1) = 5$，而$T(2) = 48$。

求$T(10)$，并对$10^9+7$取余作为你的答案。

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

