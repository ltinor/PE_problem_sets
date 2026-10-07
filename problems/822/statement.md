# Problem 822（PE 822）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=822](https://projecteuler.net/problem=822)。

## **Square the Smallest**

A list initially contains the numbers $2, 3, \dots, n$.<br />
At each round, the smallest number in the list is replaced by its square. If there is more than one such number, then only one of them is replaced.

For example, below are the first three rounds for $n = 5$:
$$[2, 3, 4, 5] \xrightarrow{(1)} [4, 3, 4, 5] \xrightarrow{(2)} [4, 9, 4, 5] \xrightarrow{(3)} [16, 9, 4, 5].$$

Let $S(n, m)$ be the sum of all numbers in the list after $m$ rounds.

For example, $S(5, 3) = 16 + 9 + 4 + 5 = 34$. Also $S(10, 100) \equiv 845339386 \pmod{1234567891}$.

Find $S(10^4, 10^{16})$. Give your answer modulo $1234567891$.

## **平方最小数**

考虑初始数列$2, 3, \dots, n$。<br />
在每一轮中，将数列中的最小值替换为其平方。如果有多个最小值，则只替换一个。

例如，当$n=5$时，前三轮的操作如下：
$$[2, 3, 4, 5] \xrightarrow{(1)} [4, 3, 4, 5] \xrightarrow{(2)} [4, 9, 4, 5] \xrightarrow{(3)} [16, 9, 4, 5]$$

记$S(n, m)$为进行$m$轮后数列中所有数之和。

例如，$S(5, 3) = 16 + 9 + 4 + 5 = 34$。已知$S(10, 100) \equiv 845339386 \pmod{1234567891}$。

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
参考常量: PE_ANSWER = 1098139348878744681LL
