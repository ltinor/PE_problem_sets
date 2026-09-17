# Problem 635（PE 635）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=635](https://projecteuler.net/problem=635)。

## **Subset sums**

Let $A_q(n)$ be the number of subsets, $B$, of the set $\{1,2,\ldots,q\cdot n\}$ that satisfy two conditions:
1) $B$ has exactly $n$ elements;
2) the sum of the elements of $B$ is divisible by $n$.

E.g. $A_2(5)=52$ and $A_3(5)=603$.

Let $S_q(L)$ be $\sum A_q(p)$ where the sum is taken over all primes $p\le L$. 
E.g. $S_2(10)=554$, $S_2(100) \mod 1\ 000\ 000\ 009 = 100433628$ and $S_3(100) \mod 1\ 000\ 000\ 009=855618282$.

Find $S_2(10^8)+S_3(10^8)$. Give your answer modulo $1\ 000\ 000\ 009$.

## **子集和**

考虑集合$\{1,2,\ldots,q\cdot n\}$的子集$B$，且$B$满足以下两个条件：
1) $B$中恰好有$n$个元素；
2) $B$中元素的和能够被$n$整除；
记所有此类子集$B$的数目为$A_q(n)$。

例如，$A_2(5)=52$，$A_3(5)=603$。

记$S_q(L)$为$\sum A_q(p)$，其中$p$取遍所有满足$p\le L$的质数。
例如，$S_2(10)=554$，$S_2(100) \mod 1\ 000\ 000\ 009 = 100433628$，$S_3(100) \mod 1\ 000\ 000\ 009=855618282$。

求$S_2(10^8)+S_3(10^8)$，并将答案对$1\ 000\ 000\ 009$取余。

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

