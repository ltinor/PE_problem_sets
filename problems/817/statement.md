# Problem 817（PE 817）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=817](https://projecteuler.net/problem=817)。

## **Digits in Squares**

Define $m = M(n, d)$ to be the smallest positive integer such that when $m^2$ is written in base $n$ it includes the base $n$ digit $d$. For example, $M(10,7) = 24$ because if all the squares are written out in base $10$ the first time the digit $7$ occurs is in $24^2 = 576$. $M(11,10) = 19$ as $19^2 = 361=2A9_{11}$.

Find $\displaystyle \sum_{d = 1}^{10^5}M(p, p - d)$ where $p = 10^9 + 7$.

## **平方中的数字**

考虑所有$n$进制表示包含数字$d$的平方数$m^2$，并记其算术平方根的最小值为$m = M(n, d)$。例如，$M(10,7) = 24$，因为$10$进制下最小的包含数字$7$的平方数是$25^2=576$。类似可得$M(11,10) = 19$，因为$19^2 = 361=2A9_{11}$。

求$\displaystyle \sum_{d = 1}^{10^5}M(p, p - d)$，其中$p = 10^9 + 7$。

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
参考常量: PE_ANSWER = 253868223968LL
