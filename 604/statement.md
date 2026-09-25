# Problem 604（PE 604）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=604](https://projecteuler.net/problem=604)。

## **Convex path in square**

Let $F(N)$ be the maximum number of lattice points in an axis-aligned $N\times N$ square that the graph of a single <b>strictly convex</b> increasing function can pass through.

You are given that $F(1) = 2$, $F(3) = 3$,  $F(9) = 6$, $F(11) = 7$, $F(100) = 30$ and $F(50000) = 1898$.
Below is the graph of a function reaching the maximum 3 for $N=3$:

<center><img src="/resources/images/0604_convex3.png" alt="p604_convex3.png"></center>

Find $F(10^{18})$.

## **正方形中的凹路径**

记$F(N)$为，在一个和坐标系对齐的$N\times N$正方形中，一个<b>严格凹</b>单调增函数所能够穿过的格点数目最大值。

已知$F(1) = 2$，$F(3) = 3$，$F(9) = 6$，$F(11) = 7$，$F(100) = 30$以及$F(50000) = 1898$。
以下是$N=3$时达成最大值的函数图象：

<center><img src="/resources/images/0604_convex3.png" alt="p604_convex3.png"></center>

求$F(10^{18})$。

---

## 输入格式

字符 `PE`：输出原题官方答案。

## 输出格式

原题官方答案。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER = 1170060
