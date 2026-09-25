# Problem 944（PE 944）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=944](https://projecteuler.net/problem=944)。

## **Sum of Elevisors** 

Given a set $E$ of positive integers, an element $x$ of $E$ is called an *element divisor (elevisor)* of $E$ if $x$ divides **another** element of $E$.

The sum of all elevisors of $E$ is denoted $\operatorname{sev}(E)$.<br />
For example, $\operatorname{sev}(\\\{1, 2, 5, 6\\\}) = 1 + 2 = 3$.

Let $S(n)$ be the sum of $\operatorname{sev}(E)$ for all subsets $E$ of $\\\{1, 2, \dots, n\\\}$.<br/>
You are given $S(10) = 4927$.

Find $S(10^{14}) \bmod 1234567891$.

*** 
## **元素因数之和**

给定正整数集合$E$，如果$E$的一个元素$x$能整除$E$的**另一个**元素，则称$x$为$E$的<i class=zh>元素因数</i>。

$E$的所有元素因数之和记作$\operatorname{sev}(E)$。<br />
例如，$\operatorname{sev}(\\\{1, 2, 5, 6\\\}) = 1 + 2 = 3$。

记$S(n)$为$\\\{1, 2, \dots, n\\\}$的所有子集$E$对应的$\operatorname{sev}(E)$之和。<br/>
已知$S(10) = 4927$。

求$S(10^{14}) \bmod 1234567891$。

---

## 输入格式

见 code/std.cpp 的读取约定。

## 输出格式

计算结果。

---

## 样例

见原题描述中的样例。

---

## 数据范围

见原题参数范围。
