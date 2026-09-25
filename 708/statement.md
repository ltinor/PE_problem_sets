# Problem 708（PE 708）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=708](https://projecteuler.net/problem=708)。

## **Twos are all you need**

A positive integer, $n$, is factorised into prime factors. We define $f(n)$ to be the product when each prime factor is replaced with $2$. In addition we define $f(1)=1$.

For example, $90 = 2\times 3\times 3\times 5$, then replacing the primes, $2\times 2\times 2\times 2 = 16$, hence $f(90) = 16$.
 
Let $\displaystyle S(N)=\sum_{n=1}^{N} f(n)$. You are given $S(10^8)=9613563919$.

Find $S(10^{14})$.

## **只需要二**

对正整数$n$作质因数分解，并记$f(n)$为将所有质因数均替换为$2$时的新乘积；此外记$f(1)=1$。

例如，$90 = 2\times 3\times 3\times 5$，将质因数替换后得$2\times 2\times 2\times 2 = 16$，因此$f(90) = 16$。

记$\displaystyle S(N)=\sum_{n=1}^{N} f(n)$。已知$S(10^8)=9613563919$。

求$S(10^{14})$。

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
参考常量: N = 100000000000000LL
