# Problem 839（PE 839）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=839](https://projecteuler.net/problem=839)。

## **Beans in Bowls**

The sequence $S_n$ is defined by $S_0 = 290797$ and $S_n = S_{n - 1}^2 \bmod 50515093$ for $n>0$.

There are $N$ bowls indexed $0,1,\dots ,N-1$. Initially there are $S_n$ beans in bowl $n$.

At each step, the smallest index $n$ is found such that bowl $n$ has strictly more beans than bowl $n+1$. Then one bean is moved from bowl $n$ to bowl $n+1$.

Let $B(N)$ be the number of steps needed to sort the bowls into non-descending order.<br />
For example, $B(5) = 0$, $B(6) = 14263289$ and $B(100)=3284417556$.

Find $B(10^7)$.

## **碗中豆**

序列$S_n$按如下方式定义：$S_0 = 290797$；对于$n>0$，$S_n = S_{n - 1}^2 \bmod 50515093$。

有$N$个碗，其编号分别为$0,1,\dots,N-1$。一开始，编号为$n$的碗中放有$S_n$颗豆子。

接下来的每一步中，先选择编号最小的、豆子数目比后一个碗严格更多的碗$n$，再从碗$n$中移动一颗豆子到碗$n+1$。

记$B(N)$为将碗中豆子数目调整为非递降序列所需的步数。<br />
例如，$B(5) = 0$，$B(6) = 14263289$，$B(100)=3284417556$。

求$B(10^7)$。

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

