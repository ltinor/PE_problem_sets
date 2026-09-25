# Problem 952（PE 952）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=952](https://projecteuler.net/problem=952)。

## **Order Modulo Factorial** 

Given a prime $p$ and a positive integer $n \lt p$, let $R(p, n)$ be the **multiplicative order** of $p$ modulo $n!$.<br/>
In other words, $R(p, n)$ is the minimal positive integer $r$ such that
$$p^r \equiv 1 \pmod{n!}$$
For example, $R(7, 4) = 2$ and $R(10^9 + 7, 12) = 17280$.

Find $R(10^9 + 7, 10^7)$. Give your answer modulo $10^9 + 7$.

*** 
## **模阶乘的阶**

给定质数$p$和正整数$n \lt p$，记$R(p, n)$为$p$模$n!$的**阶**。
换句话说，$R(p, n)$是满足下式的最小正整数$r$：
$$p^r \equiv 1 \pmod{n!}$$
例如，$R(7, 4) = 2$，$R(10^9 + 7, 12) = 17280$。

求$R(10^9 + 7, 10^7)$，并对$10^9 + 7$取余作为你的答案。

---

## 输入格式

参数模式：输入 n。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
