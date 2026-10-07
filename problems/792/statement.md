# Problem 792（PE 792）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=792](https://projecteuler.net/problem=792)。

## **Too Many Twos**

We define $\nu_2(n)$ to be the largest integer $r$ such that $2^r$ divides $n$. For example, $\nu_2(24) = 3$.

Define $\displaystyle S(n)  = \sum_{k = 1}^n (-2)^k\binom{2k}k$ and $u(n) = \nu_2\Big(3S(n)+4\Big)$.

For example, when $n = 4$ then $S(4) = 980$ and $3S(4) + 4 = 2944 = 2^7 \cdot 23$, hence $u(4) = 7$.<br />
You are also given $u(20) = 24$.

Also define $\displaystyle U(N) = \sum_{n = 1}^N u(n^3)$. You are given $U(5) = 241$.

Find $U(10^4)$.

## **太多个二**

记$\nu_2(n)$为使得$2^r$整除$n$的最大整数$r$。例如，$\nu_2(24) = 3$。

定义函数$\displaystyle S(n)  = \sum_{k = 1}^n (-2)^k\binom{2k}k$和$u(n) = \nu_2\Big(3S(n)+4\Big)$。

例如，当$n = 4$时，有$S(4) = 980$，$3S(4) + 4 = 2944 = 2^7 \cdot 23$，因此$u(4) = 7$。<br />
已知$u(20) = 24$。

再定义函数$\displaystyle U(N) = \sum_{n = 1}^N u(n^3)$。已知$U(5) = 241$。

求$U(10^4)$。

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
参考常量: PE_ANSWER = 475019340LL
