# Problem 784（PE 784）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=784](https://projecteuler.net/problem=784)。

## **Reciprocal Pairs**

Let's call a pair of positive integers $p$, $q$ ($p \lt q$) <i>reciprocal</i>, if there is a positive integer $r\lt p$ such that $r$ equals both the inverse of $p$ modulo $q$ and the inverse of $q$ modulo $p$.

For example, $(3,5)$ is one reciprocal pair for $r=2$. <br />
Let $F(N)$ be the total sum of $p+q$ for all reciprocal pairs $(p,q)$ where $p \le N$.

$F(5)=59$ due to these four reciprocal pairs $(3,5)$, $(4,11)$, $(5,7)$ and $(5,19)$. <br />
You are also given $F(10^2) = 697317$.

Find $F(2\cdot 10^6)$.

## **模倒数对**

对于正整数$p$和$q$（满足$p \lt q$），若存在正整数$r \lt p$使得$r$同时是$p$同余$q$的逆元和$q$同余$p$的逆元，则称这两个正整数互为<i class=zh>模倒数</i>。

例如，$(3,5)$是一组模倒数对，其对应的$r=2$。<br />
对所有满足$p\le N$的模倒数对$(p,q)$，记$F(N)$为所有$p+q$之和。

例如，$F(5)=59$，因为共有四组模倒数对$(3,5)$、$(4,11)$、$(5,7)$和$(5,19)$。<br />
已知$F(10^2) = 697317$。

求$F(2\cdot 10^6)$。

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

