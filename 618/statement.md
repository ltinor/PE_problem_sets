# Problem 618（PE 618）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=618](https://projecteuler.net/problem=618)。

## **Numbers with a given prime factor sum**

Consider the numbers 15, 16 and 18:  
$15=3\times5$ and $3+5=8$.  
$16=2\times2\times2\times2$ and $2+2+2+2=8$.  
$18=2\times3\times3$ and $2+3+3=8$.  
15, 16 and 18 are the only numbers that have 8 as sum of the prime factors (counted with multiplicity).

We define $S(k)$ to be the sum of all numbers $n$ where the sum of the prime factors (with multiplicity) of $n$ is $k$.  
Hence $S(8)=15+16+18=49$.  
Other examples: $S(1)=0$, $S(2)=2$, $S(3)=3$, $S(5)=5+6=11$.

The Fibonacci sequence is $F\_1=1$, $F\_2=1$, $F\_3=2$, $F\_4=3$, $F\_5=5$, $\ldots$  
Find the last nine digits of $\sum_{k=2}^{24}S(F\_k)$.

## **给定质因数和的整数**

考虑整数15，16和18的质因数分解：  
$15=3\times5$，而$3+5=8$。  
$16=2\times2\times2\times2$，而$2+2+2+2=8$。  
$18=2\times3\times3$，而$2+3+3=8$。  
15，16和18是仅有的质因数和（包括重复）为8的整数。

记$S(k)$为所有质因数和（包括重复）为$k$的整数$n$的和。  
因此$S(8)=15+16+18=49$。  
其它例子包括：$S(1)=0$，$S(2)=2$，$S(3)=3$，$S(5)=5+6=11$。

考虑斐波那契数列$F\_1=1$，$F\_2=1$，$F\_3=2$，$F\_4=3$，$F\_5=5$，$\ldots$  
求$\sum_{k=2}^{24}S(F\_k)$的最后九位数字。

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

