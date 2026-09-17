# Problem 663（PE 663）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=663](https://projecteuler.net/problem=663)。

## **Sums of subarrays**

Let $t_k$ be the **tribonacci numbers** defined as: 
$\quad t_0 = t_1 = 0$;
$\quad t_2 = 1$; 
$\quad t_k = t_{k-1} + t_{k-2} + t_{k-3}$ for $k \ge 3$.

For a given integer $n$, let $A_n$ be an array of length $n$ (indexed from 0 to $n-1$), that is initially filled with zeros.
The array is changed iteratively by replacing $A_n[(t_{2 i-2} \text{ mod } n)]$ with $A_n[(t_{2 i-2} \text{ mod } n)]+2 (t_{2 i-1} \text{ mod } n)-n+1$ in each step $i$.
After each step $i$, define $M_n(i)$ to be $\displaystyle \max\{\sum_{j=p}^q A_n[j]: 0\le p\le q<n\}$, the maximal sum of any contiguous subarray of $A_n$. 

The first $6$ steps for $n=5$ are illustrated below:
Initial state: $\, A_5=\{0,0,0,0,0\}$
Step $1$: $\quad \Rightarrow A_5=\{-4,0,0,0,0\}$ , $M_5(1)=0$
Step $2$: $\quad \Rightarrow A_5=\{-4, -2, 0, 0, 0\}$ , $M_5(2)=0$
Step $3$: $\quad \Rightarrow A_5=\{-4, -2, 4, 0, 0\}$ , $M_5(3)=4$
Step $4$: $\quad \Rightarrow A_5=\{-4, -2, 6, 0, 0\}$ , $M_5(4)=6$
Step $5$: $\quad \Rightarrow A_5=\{-4, -2, 6, 0, 4\}$ , $M_5(5)=10$
Step $6$: $\quad \Rightarrow A_5=\{-4, 2, 6, 0, 4\}$ , $M_5(6)=12$

Let $\displaystyle S(n,l)=\sum_{i=1}^l M_n(i)$. Thus $S(5,6)=32$.
You are given $S(5,100)=2416$, $S(14,100)=3881$ and $S(107,1000)=1618572$.

Find $S(10\,000\,003,10\,200\,000)-S(10\,000\,003,10\,000\,000)$.

## **子数组之和**

记$t_k$为如下定义的**三阶斐波那契数列**：
$\quad t_0 = t_1 = 0$；
$\quad t_2 = 1$；
$\quad t_k = t_{k-1} + t_{k-2} + t_{k-3}$对于任意$k \ge 3$。

对于给定整数$n$，记$A_n$为长为$n$的数组（数组下标为$0$至$n-1$），数组中的元素初始值均设为0。
接着对数组进行初步调整，在第$i$步，将$A_n[(t_{2 i-2} \bmod n)]$替换为$A_n[(t_{2 i-2}\bmod n)]+2 (t_{2 i-1}\bmod n)-n+1$。
在第$i$步替换后，记$M_n(i)$为$\displaystyle \max\{\sum_{j=p}^q A_n[j]: 0\le p\le q<n\}$，即$A_n$所有连续子数组之和的最大值。

当$n=5$时，前$6$步调整过程如下所示：
初始状态：$\,A_5=\{0,0,0,0,0\}$
第$1$步：$\quad \Rightarrow A_5=\{-4, 0, 0, 0, 0\}$，$M_5(1)=0$
第$2$步：$\quad \Rightarrow A_5=\{-4, -2, 0, 0, 0\}$，$M_5(2)=0$
第$3$步：$\quad \Rightarrow A_5=\{-4, -2, 4, 0, 0\}$，$M_5(3)=4$
第$4$步：$\quad \Rightarrow A_5=\{-4, -2, 6, 0, 0\}$，$M_5(4)=6$
第$5$步：$\quad \Rightarrow A_5=\{-4, -2, 6, 0, 4\}$，$M_5(5)=10$
第$6$步：$\quad \Rightarrow A_5=\{-4, 2, 6, 0, 4\}$，$M_5(6)=12$

记$\displaystyle S(n,l)=\sum_{i=1}^l M_n(i)$，因此$S(5,6)=32$。
已知$S(5,100)=2416$，$S(14,100)=3881$，$S(107,1000)=1618572$。

求$S(10\,000\,003,10\,200\,000)-S(10\,000\,003,10\,000\,000)$。

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

