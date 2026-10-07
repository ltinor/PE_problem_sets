# Problem 886（PE 886）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=886](https://projecteuler.net/problem=886)。

## **Coprime Permutations**

A permutation of $\\\{2,3,\ldots,n\\\}$ is a rearrangement of these numbers. A <i>coprime permutation</i> is a rearrangement such that all pairs of adjacent numbers are coprime.

Let $P(n)$ be the number of coprime permutations of $\\\{2,3,\ldots,n\\\}$.

For example, $P(4)=2$ as there are two coprime permutations, $(2,3,4)$ and $(4,3,2)$. You are also given $P(10)=576$.

Find $P(34)$ and give your answer modulo $83\ 456\ 729$.

## **互质重排**

$\\\{2,3,\ldots,n\\\}$的重排是将该集合中的所有数重新排列所得的结果，而<i class=zh>互质重排</i>则是相邻两数总是互质的重排。

记$P(n)$为$\\\{2,3,\ldots,n\\\}$的所有互质重排的数目。

例如，$P(4)=2$，即存在两种互质重排，分别是$(2,3,4)$和$(4,3,2)$。此外还已知$P(10)=576$。

求$P(34)$，并对$83\ 456\ 729$取余作为你的答案。

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
参考常量: PE_ANSWER = 178245463LL
