# Problem 925（PE 925）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=925](https://projecteuler.net/problem=925)。

## **Larger Digit Permutation III**

Let $B(n)$ be the smallest number larger than $n$ that can be formed by rearranging digits of $n$, or $0$ if no such number exists. For example, $B(245) = 254$ and $B(542) = 0$.

Define $\displaystyle T(N) = \sum_{n=1}^N B(n^2)$. You are given $T(10)=270$ and $T(100)=335316$.

Find $T(10^{16})$. Give your answer modulo $10^9 + 7$.

## **更大的数字重排（三）**

令$B(n)$为通过重排$n$的数字所能形成的比$n$大的最小数，如果不存在这样的数则为$0$。例如，$B(245) = 254$，$B(542) = 0$。

定义$\displaystyle T(N) = \sum_{n=1}^N B(n^2)$。已知$T(10)=270$，$T(100)=335316$。

求$T(10^{16})$，并对$10^9 + 7$取余作为你的答案。

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
参考常量: PE_ANSWER = 275586123
