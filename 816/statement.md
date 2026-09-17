# Problem 816（PE 816）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=816](https://projecteuler.net/problem=816)。

## **Shortest distance among points**

We create an array of points $P_n$ in a two dimensional plane using the following random number generator:<br />
$s_0=290797$<br />
$s_{n+1}=s_n^2 \bmod 50515093$<br />
$P_n=(s_{2n},s_{2n+1})$

Let $d(k)$ be the shortest distance of any two (distinct) points among $P_0, \cdots, P_{k - 1}$.<br />
E.g. $d(14)=546446.466846479$

Find $d(2000000)$. Give your answer rounded to $9$ places after the decimal point.

## **随机点集最短距离**

使用下列随机数生成器生成二维随机点列$P_n$：<br />
$s_0=290797$<br />
$s_{n+1}=s_n^2 \bmod 50515093$<br />
$P_n=(s_{2n},s_{2n+1})$

记$d(k)$为$P_0, \cdots, P_{k - 1}$中任意（不同的）两点间最短距离。<br />
已知$d(14)=546446.466846479$。

求$d(2000000)$，并将你的答案四舍五入至小数点后$9$位。

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

