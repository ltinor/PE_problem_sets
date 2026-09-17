# Problem 908（PE 908）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=908](https://projecteuler.net/problem=908)。

## **Clock Sequence II**

A <i>clock sequence</i> is a periodic sequence of positive integers that can be broken into contiguous segments such that the sum of the $n$-th segment is equal to $n$.

For example, the sequence
$$1\ 2\ 3\ 4\ 3\ 2\ 1\ 2\ 3\ 4\ 3\ 2\ 1\ 2\ 3\ 4\ 3\ 2\ 1\ \cdots$$
is a clock sequence with period $6$, as it can be broken into 
$$1\Big |2\Big |3\Big |4\Big |3\ 2\Big |1\ 2\ 3\Big |4\ 3\Big |2\ 1\ 2\ 3\Big |4\ 3\ 2\Big |1\ 2\ 3\ 4\Big |3\ 2\ 1\ 2\ 3\Big |\cdots$$
Let $C(N)$ be the number of different clock sequences with period at most $N$. For example, $C(3) = 3$, $C(4) = 7$ and $C(10) = 561$.

Find $C(10^4) \bmod 1111211113$.

## **钟摆序列（二）**

<i class=zh>钟摆序列</i>是一种具有周期性的正整数序列。这种序列可以被分成连续的片段，使得第$n$个片段之和等于$n$。

例如，序列
$$1\ 2\ 3\ 4\ 3\ 2\ 1\ 2\ 3\ 4\ 3\ 2\ 1\ 2\ 3\ 4\ 3\ 2\ 1\ \cdots$$
是一个周期为$6$的钟摆序列，因为它可以被分成
$$1\Big |2\Big |3\Big |4\Big |3\ 2\Big |1\ 2\ 3\Big |4\ 3\Big |2\ 1\ 2\ 3\Big |4\ 3\ 2\Big |1\ 2\ 3\ 4\Big |3\ 2\ 1\ 2\ 3\Big |\cdots$$

令$C(N)$为周期至多为$N$的不同钟摆序列的数量。例如，$C(3) = 3$，$C(4) = 7$，$C(10) = 561$。

求$C(10^4) \bmod 1111211113$。

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

