# Problem 804（PE 804）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=804](https://projecteuler.net/problem=804)。

## **Counting Binary Quadratic Representations**

Let $g(n)$ denote the number of ways a positive integer $n$ can be represented in the form: 
$$x^2+xy+41y^2$$
where $x$ and $y$ are integers. For example, $g(53)=4$ due to $(x,y) \in \{(-4,1),(-3,-1),(3,1),(4,-1)\}$.

Define $\displaystyle T(N)=\sum_{n=1}^{N}g(n)$. You are given $T(10^3)=474$ and $T(10^6)=492128$.

Find $T(10^{16})$.

## **二元二次型表示计数**

记$g(n)$为将正整数$n$表示成如下二元二次型的方式数目：
$$x^2+xy+41y^2$$
其中$x$和$y$均为整数。例如，$g(53)=4$，对应的方式为$(x,y) \in \{(-4,1),(-3,-1),(3,1),(4,-1)\}$。

定义$\displaystyle T(N)=\sum_{n=1}^{N}g(n)$。已知$T(10^3)=474$，$T(10^6)=492128$。

求$T(10^{16})$。

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

