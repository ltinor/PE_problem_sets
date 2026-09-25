# Problem 619（PE 619）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=619](https://projecteuler.net/problem=619)。

## **Square subsets**

For a set of positive integers $\{a,a+1,a+2,\ldots,b\}$, let $C(a,b)$ be the number of non-empty subsets in which the product of all elements is a perfect square.

For example $C(5,10)=3$, since the products of all elements of $\{5,8,10\}$, $\{5,8,9,10\}$ and $\{9\}$ are perfect squares, and no other subsets of $\{5,6,7,8,9,10\}$ have this property.

You are given that $C(40,55)=15$, and $C(1000,1234)\text{ mod }1000000007=975523611$.

Find $C(1000000,1234567)\text{ mod }1000000007$.

## **平方子集**

对于正整数集$\{a,a+1,a+2,\ldots,b\}$，记$C(a,b)$为其非空子集中满足所有元素之积为完全平方数的子集的数目。

例如，$C(5,10)=3$，因为除了$\{5,8,10\}$，$\{5,8,9,10\}$和$\{9\}$中所有元素之积为完全平方数外，不存在其它$\{5,6,7,8,9,10\}$的子集满足这一性质。

已知$C(40,55)=15$，以及$C(1000,1234)\text{ mod }1000000007=975523611$。

求$C(1000000,1234567)\text{ mod }1000000007$。

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
参考常量: PE_ANSWER = 3268573801LL
