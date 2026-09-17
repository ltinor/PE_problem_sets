# Problem 774（PE 774）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=774](https://projecteuler.net/problem=774)。

## **Conjunctive Sequences**

$\\\&$ denote the bitwise AND operation.<br>
For example, $10\ \\\&\ 12 = 1010_2\ \\\&\ 1100_2 = 1000_2 = 8$.

We shall call a finite sequence of non-negative integers $(a_1, a_2, \ldots, a_n)$ <i>conjunctive</i> if $a_i\ \\\&\ a_{i+1} \neq 0$ for all $i=1\ldots n-1$.

Define $c(n,b)$ to be the number of conjunctive sequences of length $n$ in which all terms are $\le b$.

You are given that $c(3,4)=18$, $c(10,6)=2496120$, and $c(100,200) \equiv 268159379 \pmod {998244353}$.

Find $c(123,123456789)$. Give your answer modulo $998244353$.

## **合取数列**

$\\\&$表示按位与操作。<br>
例如，$10\ \\\&\ 12 = 1010_2\ \\\&\ 1100_2 = 1000_2 = 8$。

若有限非负整数列$(a_1, a_2, \ldots, a_n)$满足，对所有$i=1\ldots n-1$均有$a_i\ \\\&\ a_{i+1} \neq 0$，则称之为<i class=zh>合取</i>数列。

记$c(n,b)$为所有长度为$n$且各项均$\le b$的合取数列的数目。

已知$c(3,4)=18$，$c(10,6)=2496120$，以及$c(100,200) \equiv 268159379 \pmod {998244353}$。

求$c(123,123456789)$，并将你的答案对$998244353$取余。

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

