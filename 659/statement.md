# Problem 659（PE 659）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=659](https://projecteuler.net/problem=659)。

## **Largest prime**

Consider the sequence $n^2+3$ with $n \ge 1$. 
If we write down the first terms of this sequence we get:
$4, 7, 12, 19, 28, 39, 52, 67, 84, 103, 124, 147, 172, 199, 228, 259, 292, 327, 364,\ldots$
We see that the terms for $n=6$ and $n=7$ ($39$ and $52$) are both divisible by $13$.
In fact $13$ is the largest prime dividing any two successive terms of this sequence.

Let $P(k)$ be the largest prime  that divides any two successive terms of the sequence $n^2+k^2$.

Find the last $18$ digits of $\displaystyle \sum_{k=1}^{10\,000\,000} P(k)$.

## **最大的素数**

考虑序列$n^2+3$，其中$n \ge 1$，该序列的一开始几项分别是：
$4, 7, 12, 19, 28, 39, 52, 67, 84, 103, 124, 147, 172, 199, 228, 259, 292, 327, 364,\ldots$
可以看出，$n=6$和$n=7$所对应的项（$39$和$52$）均能被$13$整除。
实际上，$13$是能够整除该序列相邻两项的最大的素数。

对于序列$n^2+k^2$，记$P(k)$为能够整除该序列相邻两项的最大的素数。

求$\displaystyle \sum_{k=1}^{10\,000\,000} P(k)$的最后$18$位数字。

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
参考常量: N = 10000000
