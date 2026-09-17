# Problem 924（PE 924）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=924](https://projecteuler.net/problem=924)。

## **Larger Digit Permutation II**

Let $B(n)$ be the smallest number larger than $n$ that can be formed by rearranging digits of $n$, or $0$ if no such number exists. For example, $B(245) = 254$ and $B(542) = 0$.

Define $a_0 = 0$ and $a_n = a_{n - 1}^2 + 2$ for $n > 0$.
Let $\displaystyle U(N) = \sum_{n = 1}^N B(a_n)$. You are given $U(10) \equiv 543870437 \pmod{10^9+7}$.

Find $U(10^{16})$. Give your answer modulo $10^9 + 7$.

## **更大的数字重排（二）**

令$B(n)$为通过重排$n$的数字所能形成的比$n$大的最小数，如果不存在这样的数则为$0$。例如，$B(245) = 254$，$B(542) = 0$。

定义$a_0 = 0$，且对于$n > 0$有$a_n = a_{n - 1}^2 + 2$。
令$\displaystyle U(N) = \sum_{n = 1}^N B(a_n)$。已知$U(10) \equiv 543870437 \pmod{10^9+7}$。

求$U(10^{16})$，并对$10^9 + 7$取余作为你的答案。

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

