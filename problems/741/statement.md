# Problem 741（PE 741）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
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

字符 `PE`：输出原题官方答案。

## 输出格式

原题官方答案。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER = 512895223LL
