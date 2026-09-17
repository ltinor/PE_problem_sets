# Problem 819（PE 819）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=819](https://projecteuler.net/problem=819)。

## **Iterative Sampling**

Given an $n$-tuple of numbers another $n$-tuple is created where each element of the new $n$-tuple is chosen randomly from the numbers in the previous $n$-tuple. For example, given $(2,2,3)$ the probability that $2$ occurs in the first position in the next $3$-tuple is $2/3$. The probability of getting all $2$'s would be $8/27$ while the probability of getting the same $3$-tuple (in any order) would be $4/9$.

Let $E(n)$ be the expected number of steps starting with $(1,2,\ldots,n)$ and ending with all numbers being the same.

You are given $E(3) = 27/7$ and $E(5) = 468125/60701 \approx 7.711982$ rounded to $6$ digits after the decimal place.

Find $E(10^3)$. Give the answer rounded to $6$ digits after the decimal place.

## **迭代抽样**

给定一个$n$元数组，考虑从中随机抽样得到的新$n$元数组。例如，当原数组是$(2,2,3)$时，新数组的第一位有$2/3$的概率是$2$，有$8/27$的概率全都是$2$，有$4/9$的概率获得原数组（不计顺序）。

从数组$(1,2,\ldots,n)$出发，不断随机抽样直至数组中所有的数都相同，记所需要的步数的期望为$E(n)$。

已知$E(3) = 27/7$，$E(5) = 468125/60701 \approx 7.711982$，保留小数点后$6$位。

求$E(10^3)$，并将你的答案保留小数点后$6$位。

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

