# Problem 821（PE 821）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=821](https://projecteuler.net/problem=821)。

## **$123$-Separable**

A set, $S$, of integers is called <i>$123$-separable</i> if $S$, $2S$ and $3S$ are disjoint. Here $2S$ and $3S$ are obtained by multiplying all the elements in $S$ by $2$ and $3$ respectively.

Define $F(n)$ to be the maximum number of elements of
$$(S\cup 2S \cup 3S)\cap \\\{1,2,3,\ldots,n\\\}$$
where $S$ ranges over all $123$-separable sets.

For example, $F(6) = 5$ can be achieved with either $S = \\\{1,4,5\\\}$ or $S = \\\{1,5,6\\\}$.<br />
You are also given $F(20) = 19$.

Find $F(10^{16})$.

## **$123$可分离集合**

若整数集合$S$满足$S$、$2S$和$3S$互不相交，则称其为<i class=zh>$123$可分离集合</i>。其中，$2S$和$3S$分别指将$S$中的所有元素乘以$2$或$3$所构成的集合。

考虑所有$123$可分离集合$S$，定义$F(n)$为集合
$$(S\cup 2S \cup 3S)\cap \\\{1,2,3,\ldots,n\\\}$$
中元素的最大数目。

例如，$F(6) = 5$，对应的集合为$S = \\\{1,4,5\\\}$或$S = \\\{1,5,6\\\}$。<br />
已知$F(20) = 19$。

求$F(10^{16})$。

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
参考常量: PE_ANSWER = 139851300873331129LL
