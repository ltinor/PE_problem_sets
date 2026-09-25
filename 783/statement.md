# Problem 783（PE 783）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=783](https://projecteuler.net/problem=783)。

## **Urns**

Given $n$ and $k$ two positive integers we begin with an urn that contains $kn$ white balls. We then proceed through $n$ turns where on each turn $k$ black balls are added to the urn and then $2k$ random balls are removed from the urn.

We let $B_t(n,k)$ be the number of black balls that are removed on turn $t$.

Further define $E(n,k)$ as the expectation of $\displaystyle \sum_{t=1}^n B_t(n,k)^2$.

You are given $E(2,2) = 9.6$

Find $E(10^6,10)$. Round your answer to the nearest whole number.

## **罐子**

对于给定的正整数$n$和$k$，考虑一个一开始装有$kn$个白球的罐子。在之后的$n$轮中，每一轮我们向罐中加入$k$个黑球，再随机拿出$2k$个任意颜色的球，

记$B_t(n,k)$为在第$t$轮拿出的黑球的数目。

再记$E(n,k)$为$\displaystyle \sum_{t=1}^n B_t(n,k)^2$的期望值。

已知$E(2,2) = 9.6$。

求$E(10^6,10)$，并将你的答案四舍五入至整数。

---

## 输入格式

参数模式：输入 S。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER = 506132494LL
