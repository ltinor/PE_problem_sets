# Problem 699（PE 699）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=699](https://projecteuler.net/problem=699)。

## **Triffle Numbers**

Let $\sigma(n)$ be the sum of all the divisors of the positive integer $n$, for example:
$\sigma(10) = 1+2+5+10 = 18$.

Define $T(N)$ to be the sum of all numbers $n \le N$ such that when the fraction $\frac{\sigma(n)}{n}$ is written in its lowest form $\frac{a}{b}$, the denominator is a power of $3$ i.e. $b = 3^k, k>0$.

You are given $T(100) = 270$ and $T(10^6) = 26089287$.

Find $T(10^{14})$.

## **三友数**

记$\sigma(n)$为正整数$n$的所有因数之和，例如：$\sigma(10) = 1+2+5+10 = 18$。

考虑所有正整数$n \le N$，并将$\frac{\sigma(n)}{n}$写成既约分数$\frac{a}{b}$，记所有使得分母$b$为$3$的幂的数$n$之和为$T(N)$。

已知$T(100) = 270$，$T(10^6) = 26089287$。

求$T(10^{14})$。

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
参考常量: PE_ANSWER = 37010438774467572LL
