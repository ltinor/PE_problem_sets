# Problem 823（PE 823）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=823](https://projecteuler.net/problem=823)。

## **Factor Shuffle**

A list initially contains the numbers $2, 3, \dots, n$.<br />
At each round, every number in the list is divided by its smallest prime factor. Then the product of these smallest prime factors is added to the list as a new number. Finally, all numbers that become $1$ are removed from the list.

For example, below are the first three rounds for $n = 5$:
$$[2, 3, 4, 5] \xrightarrow{(1)} [2, 60] \xrightarrow{(2)} [30, 4] \xrightarrow{(3)} [15, 2, 4].$$
Let $S(n, m)$ be the sum of all numbers in the list after $m$ rounds.<br />
For example, $S(5, 3) = 15 + 2 + 4 = 21$. Also $S(10, 100) = 257$.

Find $S(10^4, 10^{16})$. Give your answer modulo $1234567891$.

## **因数重排**

考虑初始数列$2, 3, \dots, n$。<br />
在每一轮中，将数列中的每个数都除以其最小的质因数，再将这些质因数的乘积加入数列，最后将所有的$1$从数列中移除。

例如，当$n=5$时，前三轮的操作如下：
$$[2, 3, 4, 5] \xrightarrow{(1)} [2, 60] \xrightarrow{(2)} [30, 4] \xrightarrow{(3)} [15, 2, 4]$$
记$S(n, m)$为进行$m$轮后数列中所有数之和。<br />
例如，$S(5, 3) = 15 + 2 + 4 = 21$。已知$S(10, 100) = 257$。

求$S(10^4, 10^{16})$，并将你的答案对$1234567891$取余。

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
