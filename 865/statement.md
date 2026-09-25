# Problem 865（PE 865）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=865](https://projecteuler.net/problem=865)。

## **Triplicate Numbers**

A <i>triplicate number</i> is a positive integer such that, after repeatedly removing three consecutive identical digits from it, all its digits can be removed.

For example, the integer $122555211$ is a triplicate number:
$$122{\color{red}555}211 \rightarrow 1{\color{red}222}11\rightarrow{\color{red}111}\rightarrow.$$
On the other hand, neither $663633$ nor $9990$ are triplicate numbers.

Let $T(n)$ be how many triplicate numbers are less than $10^n$.

For example, $T(6) = 261$ and $T(30) = 5576195181577716$.

Find $T(10^4)$. Give your answer modulo $998244353$.

## **三消数**

对于任意正整数，不断地从中消除连续三个相同数字，若最终可以将其完全消除，则称之为<i class=zh>三消数</i>。

例如，整数$122555211$是三消数：
$$122{\color{red}555}211 \rightarrow 1{\color{red}222}11\rightarrow{\color{red}111}\rightarrow.$$
反之，$663633$和$9990$都不是三消数。

记$T(n)$为所有小于$10^n$的三消数的数量.

例如，$T(6) = 261$，$T(30) = 5576195181577716$。

求$T(10^4)$，并对$998244353$取余作为你的答案。

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
