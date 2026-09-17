# Problem 741（PE 741）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=741](https://projecteuler.net/problem=741)。

## **Binary grid colouring**

Let $f(n)$ be the number of ways an $n\times n$ square grid can be coloured, each cell either black or white, such that each row and each column contains exactly two black cells.
For example, $f(4)=90$, $f(7) = 3110940$ and $f(8) = 187530840$.

Let $g(n)$ be the number of colourings in $f(n)$ that are unique up to rotations and reflections.
You are given $g(4)=20$, $g(7) = 390816$ and $g(8) = 23462347$ giving $g(7)+g(8) = 23853163$.

Find $g(7^7) + g(8^8)$. Give your answer modulo $1\ 000\ 000\ 007$.

## **网格黑白染色**

对$n\times n$的网格进行黑白染色，记使得每行和每列都恰好有两个黑格的染色方法数目为$f(n)$。
例如，$f(4)=90$，$f(7) = 3110940$，$f(8) = 187530840$。

在$f(n)$中，将所有旋转或翻转后可重合的染色方法视为相同的方法，记不同染色方法数目为$g(n)$。
已知$g(4)=20$，$g(7) = 390816$，$g(8) = 23462347$，因此$g(7)+g(8) = 23853163$。

求$g(7^7) + g(8^8)$，并将你的答案对$1\ 000\ 000\ 007$取余。

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

