# Problem 694（PE 694）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=694](https://projecteuler.net/problem=694)。

## **Cube-full Divisors**

A positive integer $n$ is considered <i>cube-full</i>, if for every prime $p$ that divides $n$, so does $p^3$. Note that $1$ is considered cube-full.

Let $s(n)$ be the function that counts the number of cube-full divisors of $n$. For example, $1$, $8$ and $16$ are the three cube-full divisors of $16$. Therefore, $s(16)=3$.

Let $S(n)$ represent the summatory function of $s(n)$, that is $S(n)=\displaystyle\sum_{i=1}^n s(i)$.

You are given $S(16) =  19$, $S(100) = 126$ and $S(10000) = 13344$.

Find $S(10^{18})$.

## **满立方约数**

考虑正整数$n$，若对于任意整除$n$的质数$p$，总有$p^3$也整除$n$，则称$n$为<i class=zh>满立方</i>数。作为特例，$1$也是满立方数。

记$s(n)$为$n$的所有约数中满立方数的数目。例如，$16$的约数中有$1$、$8$和$16$三个满立方数，因此$s(16)=3$。

记$S(n)$为$s(n)$的部分和函数，也即$S(n)=\displaystyle\sum_{i=1}^n s(i)$。

已知$S(16) =  19$，$S(100) = 126$，$S(10000) = 13344$。

求$S(10^{18})$。

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

