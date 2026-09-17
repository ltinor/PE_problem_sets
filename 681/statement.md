# Problem 681（PE 681）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=681](https://projecteuler.net/problem=681)。

## **Maximal Area**

Given positive integers $a \le b \le c \le d$, it may be possible to form quadrilaterals with edge lengths $a$, $b$, $c$, $d$ (in any order). When this is the case, let $M(a,b,c,d)$ denote the maximal area of such a quadrilateral.
For example, $M(2,2,3,3)=6$, attained e.g. by a $2\times 3$ rectangle.

Let $SP(n)$ be the sum of $a+b+c+d$ over all choices $a \le b \le c \le d$ for which $M(a,b,c,d)$ is a positive integer not exceeding $n$.
$SP(10)=186$ and $SP(100)=23238$.

Find $SP(1\ 000\ 000)$.

## **最大面积**

对于给定正整数$a \le b \le c \le d$，有时能找到边长分别为$a$、$b$、$c$、$d$的四边形（未必按照这一顺序）。当存在这样的四边形时，记$M(a,b,c,d)$为所有此类四边形的最大面积。
例如，$M(2,2,3,3)=6$，这一最大面积在构成$2\times 3$的长方形时取得。

考虑所有满足$a \le b \le c \le d$且$M(a,b,c,d)$为不超过$n$的正整数的四元组$(a,b,c,d)$，并记所有这些四元组对应的$a+b+c+d$之和为$SP(n)$.
已知$SP(10)=186$，$SP(100)=23238$。

求$SP(1\ 000\ 000)$。

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

