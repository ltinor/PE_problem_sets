# Problem 827（PE 827）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=827](https://projecteuler.net/problem=827)。

## **Pythagorean Triple Occurrence**

Define $Q(n)$ to be the smallest number that occurs in exactly $n$ <b>Pythagorean triples</b> $(a,b,c)$ where $a \lt b \lt c$.

For example, $15$ is the smallest number occurring in exactly $5$ Pythagorean triples:
$$(9,12,\mathbf{15})\quad (8,\mathbf{15},17)\quad (\mathbf{15},20,25)\quad (\mathbf{15},36,39)\quad (\mathbf{15},112,113)$$
and so $Q(5) = 15$.

You are also given $Q(10)=48$ and $Q(10^3)=8064000$.

Find $\displaystyle \sum_{k=1}^{18} Q(10^k)$. Give your answer modulo $409120391$.

## **毕达哥拉斯三元组频数**

记$Q(n)$为最小的、恰好出现在$n$个<b>毕达哥拉斯三元组</b>$(a,b,c)$中的数，其中$a \lt b \lt c$。

例如，$15$是最小的、恰好出现在$5$个毕达哥拉斯三元组中的数：
$$(9,12,\mathbf{15})\quad (8,\mathbf{15},17)\quad (\mathbf{15},20,25)\quad (\mathbf{15},36,39)\quad (\mathbf{15},112,113)$$
因此$Q(5) = 15$。

已知$Q(10)=48$，$Q(10^3)=8064000$。

求$\displaystyle \sum_{k=1}^{18} Q(10^k)$，并将你的答案对$409120391$取余。

---

## 输入格式

（待人工补充：请对照 code/std.cpp 的读取约定描述。）

## 输出格式

（待人工补充。）

## 样例

（无 data 数据，待人工补充。）

---

## 数据范围

（待人工补充；原题参数范围见上方原题描述。）

