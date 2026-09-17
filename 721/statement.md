# Problem 721（PE 721）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=721](https://projecteuler.net/problem=721)。

## **High powers of irrational numbers**

Given is the function $f(a,n)=\lfloor{(\lceil{\sqrt{a}\:\rceil}+\sqrt{a}\:)^n}\rfloor$.
$\lfloor{.}\rfloor$ denotes the floor function and $\lceil{.}\rceil$ denotes the ceiling function.
$f(5,2)=27$ and $f(5,5)=3935$.

$G(n) = \displaystyle \sum_{a=1}^n f(a, a^2).$
$G(1000) \bmod 999\ 999\ 937=163861845. $
Find $G(5\ 000\ 000).$ Give your answer modulo $999\ 999\ 937$.

## **无理数的高次幂**

考虑函数$f(a,n)=\lfloor{(\lceil{\sqrt{a}\:\rceil}+\sqrt{a}\:)^n}\rfloor$，其中$\lfloor{.}\rfloor$代表下取整函数，$\lceil{.}\rceil$代表上取整函数。
已知$f(5,2)=27$，$f(5,5)=3935$。

记$G(n) = \displaystyle \sum_{a=1}^n f(a, a^2)$。
已知$G(1000) \bmod 999\ 999\ 937=163861845$。
求$G(5\ 000\ 000)$，并将你的答案对$999\ 999\ 937$取余。

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

