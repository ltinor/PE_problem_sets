# Problem 829（PE 829）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=829](https://projecteuler.net/problem=829)。

## **Integral Fusion**

Given any integer $n>1$ a <i>binary factor tree</i> $T(n)$ is defined to be:
- A tree with the single node $n$ when $n$ is prime.
- A binary tree that has root node $n$, left subtree $T(a)$ and right subtree $T(b)$, when $n$ is not prime. Here $a$ and $b$ are positive integers such that $n = ab$, $a\le b$ and $b-a$ is the smallest.

For example $T(20)$:

<cemter>
<img src="/resources/images/0829_example1.jpg" alt="p829_example1.jpg" />
</center>

We define $M(n)$ to be the smallest number that has a factor tree identical in shape to the factor tree for $n!!$, the <b>double factorial</b> of $n$.

For example, consider $9!! = 9\times 7\times 5\times 3\times 1 = 945$. The factor tree for $945$ is shown below together with the factor tree for $72$ which is the smallest number that has a factor tree of the same shape. Hence $M(9) = 72$.

<center>
<img src="/resources/images/0829_example2.jpg" alt="p829_example2.jpg" />
</center>

Find $\displaystyle\sum_{n=2}^{31} M(n)$.

## **整数合成**

给定任意整数$n>1$，定义其对应的<i class=zh>二叉因子树</i> $T(n)$如下：
- 若$n$是质数，则该树只有一个单独的结点$n$。
- 若$n$不是质数，则该树有根结点$n$、左子树$T(a)$和右子树$T(b)$，其中$a$和$b$都是正整数，且满足$n=ab$，$a\le b$，$b-a$取得最小值。

例如，$T(20)$如下图所示:

<cemter>
<img src="/resources/images/0829_example1.jpg" alt="p829_example1.jpg" />
</center>

记$M(n)$为二叉因子树和$n!!$的二叉因子树形状相同的最小正整数，其中$n!!$表示$n$的<b>双阶乘</b>。

例如，$9!! = 9\times 7\times 5\times 3\times 1 = 945$。如下图所示，$945$和$72$的二叉因子树形状相同，且$72$是满足该条件的最小整数，因此$M(9) = 72$。

<center>
<img src="/resources/images/0829_example2.jpg" alt="p829_example2.jpg" />
</center>

求$\displaystyle\sum_{n=2}^{31} M(n)$。

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

