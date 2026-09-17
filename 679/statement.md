# Problem 679（PE 679）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=679](https://projecteuler.net/problem=679)。

## **FREEFAREA**

Let $S$ be the set consisting of the four letters 
$\{\texttt{`A'},\texttt{`E'},\texttt{`F'},\texttt{`R'}\}$.
For $n\ge 0$, let $S^*(n)$ denote the set of words of length $n$ consisting of letters belonging to $S$.
We designate the words $\texttt{FREE}, \texttt{FARE}, \texttt{AREA}, \texttt{REEF}$ as <i>keywords</i>.

Let $f(n)$ be the number of words in $S^*(n)$ that contains all four keywords exactly once.

This first happens for $n=9$, and indeed there is a unique 9 lettered word that contain each of the keywords once: $\texttt{FREEFAREA}$
So, $f(9)=1$.

You are also given that $f(15)=72863$.

Find $f(30)$.

## **FREEFAREA**

记$S$为包含四个字母的集合$\{\texttt{`A'},\texttt{`E'},\texttt{`F'},\texttt{`R'}\}$。
对于$n\ge 0$，记$S^*(n)$为仅包含$S$中的字母且长度为$n$的字符串所组成的集合。
我们选择$\texttt{FREE}, \texttt{FARE}, \texttt{AREA}, \texttt{REEF}$作为<i class=zh>关键词</i>。

记$f(n)$为$S^*(n)$中恰好包含四个关键词各一次的字符串数目。

在$n=9$时首次出现满足要求的字符串，且唯一的拥有$9$个字母的此类字符串是$\texttt{FREEFAREA}$。
因此$f(9)=1$。

已知$f(15)=72863$。

求$f(30)$。

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

