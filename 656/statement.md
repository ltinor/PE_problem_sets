# Problem 656（PE 656）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=656](https://projecteuler.net/problem=656)。

## **Palindromic sequences**

Given an irrational number $\alpha$, let $S_\alpha(n)$ be the sequence $S_\alpha(n)=\lfloor \alpha \cdot n \rfloor - \lfloor \alpha \cdot (n-1)\rfloor$ for $n\ge 1$.
($\lfloor \ldots \rfloor$ is the floor-function.)

It can be proven that for any irrational $\alpha$ there exist infinitely many values of $n$ such that the subsequence $\{S_\alpha(1),S_\alpha(2)\ldots S_\alpha(n)\}$ is palindromic.

The first $20$ values of $n$ that give a palindromic subsequence for $\alpha=\sqrt{31}$ are: $1$, $3$, $5$, $7$, $44$, $81$, $118$, $273$, $3158$, $9201$, $15244$, $21287$, $133765$, $246243$, $358721$, $829920$, $9600319$, $27971037$, $46341755$, $647124734.

Let $H_g(\alpha)$ be the sum of the first $g$ values of $n$ for which the corresponding subsequence is palindromic.
So $H_{20}(\sqrt{31})=150243655$.

Let $T=\{2, 3, 5, 6, 7, 8, 10, \ldots, 1000\}$ be the set of positive integers, not exceeding $1000$, excluding perfect squares.
Calculate the sum of $H_{100}(\sqrt{\beta})$ for $\beta \in T$. Give the last $15$ digits of your answer.

## **回文序列**

任取无理数$\alpha$，记$S_\alpha(n)$为序列$S_\alpha(n)=\lfloor \alpha \cdot n \rfloor - \lfloor \alpha \cdot (n-1)\rfloor$，其中$n\ge 1$。
（$\lfloor \ldots \rfloor$表示下取整函数。）

可以证明，对于任意无理数$\alpha$，存在无数个$n$，使得子序列$\{S_\alpha(1),S_\alpha(2)\ldots S_\alpha(n)\}$是回文的。

对于$\alpha=\sqrt{31}$，前$20$个满足上述条件的$n$分别是：$1$，$3$，$5$，$7$，$44$，$81$，$118$，$273$，$3158$，$9201$，$15244$，$21287$，$133765$，$246243$，$358721$，$829920$，$9600319$，$27971037$，$46341755$，$647124734$。

记$H_g(\alpha)$为前$g$个满足上述条件的$n$之和。
因此$H_{20}(\sqrt{31})=150243655$。

记$T=\{2, 3, 5, 6, 7, 8, 10, \ldots, 1000\}$为不超过$1000$且不包含完全平方数的正整数所组成的集合。
对于所有$\beta \in T$，求$H_{100}(\sqrt{\beta})$之和，并给出最后$15$位数字作为你的答案。

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

