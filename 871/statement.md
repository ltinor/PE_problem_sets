# Problem 871（PE 871）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=871](https://projecteuler.net/problem=871)。

## **Drifting Subsets**

Let $f$ be a function from a finite set $S$ to itself. A <i>drifting subset</i> for $f$ is a subset $A$ of $S$ such that the number of elements in the union $A \cup f(A)$ is equal to twice the number of elements of $A$.<br />
We write $D(f)$ for the maximal number of elements among all drifting subsets for $f$.

For a positive integer $n$, define $f_n$ as the function from $\\\{0, 1, \dots, n - 1\\\}$ to itself sending $x$ to $x^3 + x + 1 \bmod n$.<br />
You are given $D(f_5) = 1$ and $D(f_{10}) = 3$.

Find $\displaystyle\sum_{i = 1}^{100} D(f_{10^5 + i})$.

## **漂移子集**

记$f$为从有限集$S$到其本身的函数。若$S$的一个子集$A$满足，并集$A \cup f(A)$的元素数目是$A$的元素数目的两倍，则称$A$为$f$的<i class=zh>漂移子集</i>。<br />
记$D(f)$为$f$所有漂移子集的元素数目最大值。

对于正整数$n$，定义$f_n$为从集合$\\\{0, 1, \dots, n - 1\\\}$到其本身的函数，将任意元素$x$映射到$x^3 + x + 1 \bmod n$。<br />
已知$D(f_5) = 1$，$D(f_{10}) = 3$。

求$\displaystyle\sum_{i = 1}^{100} D(f_{10^5 + i})$。

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

