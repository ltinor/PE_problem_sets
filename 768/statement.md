# Problem 768（PE 768）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=768](https://projecteuler.net/problem=768)。

## **Chandelier**

A certain type of chandelier contains a circular ring of $n$ evenly spaced candleholders.<br>
If only one candle is fitted, then the chandelier will be imbalanced. However, if a second identical candle is placed in the opposite candleholder (assuming $n$ is even) then perfect balance will be achieved and the chandelier will hang level.

Let $f(n,m)$ be the number of ways of arranging $m$ identical candles in distinct sockets of a chandelier with $n$ candleholders such that the chandelier is perfectly balanced.

For example, $f(4, 2) = 2$: assuming the chandelier's four candleholders are aligned with the compass points, the two valid arrangements are "North & South" and "East & West". Note that these are considered to be different arrangements even though they are related by rotation.

You are given that $f(12,4) = 15$ and $f(36, 6) = 876$.

Find $f(360, 20)$.

## **枝形吊灯**

某种枝形吊灯上等距离安置了一圈共$n$个烛台。<br>
如果只摆上一根蜡烛，那么吊灯将会失去平衡。必须在与第一根蜡烛相对的烛台上（假设$n$是偶数）摆上第二根完全相同的蜡烛，才能让吊灯保持平衡。

对于安置有$n$个烛台的吊灯，记$f(n,m)$为在不同的烛台上摆上共$m$根完全相同的蜡烛且仍能让吊灯保持平衡的方案总数。

例如，$f(4, 2) = 2$：不妨假设吊灯上的四个烛台恰好指向正东、正西、正南、正北方向，那么符合要求的两种方案是“正北和正南”以及“正东和正西”。注意尽管这两种方案可以经过旋转重合，但仍视为不同的方案。

此外，还已知$f(12,4) = 15$以及$f(36, 6) = 876$。

求$f(360, 20)$。

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

