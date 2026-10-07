# Problem 763（PE 763）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=763](https://projecteuler.net/problem=763)。

## **Amoebas in a 3D grid**

Consider a three dimensional grid of cubes. An amoeba in cube $(x, y, z)$ can divide itself into three amoebas to occupy the cubes $(x + 1, y, z)$, $(x, y + 1, z)$ and $(x, y, z + 1)$, provided these cubes are empty.

Originally there is only one amoeba in the cube $(0, 0, 0)$. After $N$ divisions there will be $2N+1$ amoebas arranged in the grid. An arrangement may be reached in several different ways but it is only counted once. Let $D(N)$ be the number of different possible arrangements after $N$ divisions.

For example, $D(2) = 3$, $D(10) = 44499$, $D(20)=9204559704$ and the last nine digits of $D(100)$ are $780166455$.

Find $D(10\ 000)$, enter the last nine digits as your answer.

## **三维格阵中的阿米巴原虫**

考虑一个三维格阵。原本位于方格$(x,y,z)$中的一只阿米巴原虫，在目标方格没有被占据的情况下，可以将自身分裂成三只阿米巴原虫，并分别占据方格$(x+1,y,z)$，$(x,y+1,z)$和$(x,y,z+1)$。

一开始只有一只阿米巴原虫位于方格$(0, 0,0)$。经过$N$次分裂之后，格阵中将会分布有$2N+1$只阿米巴原虫。不同的分裂顺序可能形成相同的分布情况，这些分布均算作相同的分布。记$D(N)$为经过$N$次分裂后所有可能的不同分布的总数。

例如，$D(2) = 3$，$D(10) = 44499$，$D(20)=9204559704$，而$D(100)$的最后九位数字是$780166455$。

求$D(10\ 000)$，并将其最后九位数字作为你的答案。

---

## 输入格式

参数模式：输入 N。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
