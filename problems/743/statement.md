# Problem 743（PE 743）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=743](https://projecteuler.net/problem=743)。

## **Window into a Matrix**

A window into a matrix is a contiguous sub matrix.

Consider a $2\times n$ matrix where every entry is either $0$ or $1$.
Let $A(k,n)$ be the total number of these matrices such that the sum of the entries in every $2\times k$ window is $k$.

You are given that $A(3,9) = 560$ and $A(4,20) = 1060870$.

Find $A(10^8,10^{16})$. Give your answer modulo $1\ 000\ 000\ 007$.

## **矩阵窗口**

矩阵的窗口是指矩阵中一个连续的子矩阵。

考虑一个$2\times n$的矩阵，其中的元素均为$0$或$1$。
若矩阵中任意一个$2\times k$的窗口中元素之和都为$k$，记所有这样的矩阵数目为$A(k,n)$。

已知$A(3,9) = 560$，$A(4,20) = 1060870$。

求$A(10^8,10^{16})$，并将你的答案对$1\ 000\ 000\ 007$取余。

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
参考常量: PE_ANSWER = 259158998LL
