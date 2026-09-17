# Problem 654（PE 654）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=654](https://projecteuler.net/problem=654)。

## **Neighbourly Constraints**

Let $T(m,n)$ be the number of $m$-tuples of positive integers such that the sum of any two neighbouring elements of the tuple is $\le n$.

For example, $T(3,4)=8$, via the following eight $4$-tuples:
$(1, 1, 1, 1)$
$(1, 1, 1, 2)$
$(1, 1, 2, 1)$
$(1, 2, 1 ,1)$
$(1, 2, 1 ,2)$
$(2, 1, 1 ,1)$
$(2, 1, 1 ,2)$
$(2, 1, 2 ,1)$

You are also given that $T(5,5)=246$, 
$T(10,10^2)\equiv 862820094 \pmod{1\ 000\ 000\ 007}$ and
$T(10^2,10)\equiv 782136797 \pmod{1\ 000\ 000\ 007}$.

Find $T(5000,10^{12})\mod 1\ 000\ 000\ 007$.

## **相邻约束**

记$T(m,n)$为任意相邻元素之和$\le n$的所有$m$-元正整数组的数目。

例如，$T(3,4)=8$这八个$4$元组分别是：
$(1, 1, 1, 1)$
$(1, 1, 1, 2)$
$(1, 1, 2, 1)$
$(1, 2, 1 ,1)$
$(1, 2, 1 ,2)$
$(2, 1, 1 ,1)$
$(2, 1, 1 ,2)$
$(2, 1, 2 ,1)$

已知$T(5,5)=246$，
$T(10,10^2)\equiv 862820094 \pmod{1\ 000\ 000\ 007}$，
$T(10^2,10)\equiv 782136797 \pmod{1\ 000\ 000\ 007}$。

求$T(5000,10^{12})\mod 1\ 000\ 000\ 007$。

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

