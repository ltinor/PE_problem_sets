# Problem 654（PE 654）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=654](https://projecteuler.net/problem=654)。

## **Neighbourly Constraints**

Let $T(m,n)$ be the number of $m$-tuples of positive integers such that the sum of any two neighbouring elements of the tuple is $\le n$.

For example, $T(3,4)=8$, via the following eight $4$-tuples:
$(1, 1, 1, 1)$
$(1, 1, 1, 2)$
$(1, 1, 2, 1)$
$(1, 2, 1 ,1)$
$(1, 2, 1 ,2)$
$(2, 1, 1 ,1)$
$(2, 1, 1 ,2)$
$(2, 1, 2 ,1)$

You are also given that $T(5,5)=246$, 
$T(10,10^2)\equiv 862820094 \pmod{1\ 000\ 000\ 007}$ and
$T(10^2,10)\equiv 782136797 \pmod{1\ 000\ 000\ 007}$.

Find $T(5000,10^{12})\mod 1\ 000\ 000\ 007$.

## **相邻约束**

记$T(m,n)$为任意相邻元素之和$\le n$的所有$m$-元正整数组的数目。

例如，$T(3,4)=8$这八个$4$元组分别是：
$(1, 1, 1, 1)$
$(1, 1, 1, 2)$
$(1, 1, 2, 1)$
$(1, 2, 1 ,1)$
$(1, 2, 1 ,2)$
$(2, 1, 1 ,1)$
$(2, 1, 1 ,2)$
$(2, 1, 2 ,1)$

已知$T(5,5)=246$，
$T(10,10^2)\equiv 862820094 \pmod{1\ 000\ 000\ 007}$，
$T(10^2,10)\equiv 782136797 \pmod{1\ 000\ 000\ 007}$。

求$T(5000,10^{12})\mod 1\ 000\ 000\ 007$。

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
参考常量: PE_ANSWER = 815868280
