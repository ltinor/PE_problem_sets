# Problem 929（PE 929）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=929](https://projecteuler.net/problem=929)。

## **Odd-Run Compositions**

A <b>composition</b> of $n$ is a sequence of positive integers which sum to $n$. Such a sequence can be split into <i>runs</i>, where a run is a maximal contiguous subsequence of equal terms.

For example, $2,2,1,1,1,3,2,2$ is a composition of $14$ consisting of four runs:

<div style="text-align:center">
$2, 2\quad 1, 1, 1\quad 3 \quad 2, 2$
</div>

Let $F(n)$ be the number of compositions of $n$ where every run has odd length.

For example, $F(5)=10$:
$$
\begin{aligned}
& 5 && 4,1 && 3,2 && 2,3 && 2,1,2\\\\
& 2,1,1,1 && 1,4 && 1,3,1 && 1,1,1,2 && 1,1,1,1,1
\end{aligned}
$$
Find $F(10^5)$. Give your answer modulo $1111124111$.

## **奇数长度分段组成**

$n$的一个<b>组成</b>是一个和为$n$的正整数序列；这一序列可以进一步分成若干<i class=zh>段</i>，每一段是由相等的数构成的最长连续子序列。

例如，$2,2,1,1,1,3,2,2$是$14$的一个组成，可以分成四段：

<div style="text-align:center">
$2, 2\quad 1, 1, 1\quad 3 \quad 2, 2$
</div>

令$F(n)$为$n$的所有组成中，满足每一段长度都为奇数的组成的数目。

例如，$F(5)=10$：
$$
\begin{aligned}
& 5 && 4,1 && 3,2 && 2,3 && 2,1,2\\\\
& 2,1,1,1 && 1,4 && 1,3,1 && 1,1,1,2 && 1,1,1,1,1
\end{aligned}
$$
求$F(10^5)$，并对$1111124111$取余作为你的答案。

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

