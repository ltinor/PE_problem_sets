# Problem 848（PE 848）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=848](https://projecteuler.net/problem=848)。

## **Guessing with Sets**

Two players play a game. At the start of the game each player secretly chooses an integer; the first player from $1,\ldots,n$ and the second player from $1,\ldots,m$. Then they take alternate turns, starting with the first player. The player, whose turn it is, displays a set of numbers and the other player tells whether their secret number is in the set or not. The player to correctly guess a set with a single number is the winner and the game ends.

Let $p(m,n)$ be the winning probability of the first player assuming both players play optimally. For example $p(1, n) = 1$ and $p(m, 1) = 1/m$.

You are also given $p(7,5) \approx 0.51428571$.

Find $\displaystyle \sum_{i=0}^{20}\sum_{j=0}^{20} p(7^i, 5^j)$ and give your answer rounded to $8$ digits after the decimal point.

## **猜数游戏**

两位玩家正在进行如下游戏：游戏开始时，每位玩家需要秘密地选择一个整数，其中一号玩家在$1,\ldots,n$中选，而二号玩家在$1,\ldots,m$。然后，由一号玩家先开始，双方轮流进行猜测：轮到某位玩家时，他需要选择一个整数集合，并由另一位玩家告知其秘密选择的数是否在该集合中。若某位玩家选择的集合恰好只包含另一位玩家秘密选择的数，则该玩家获胜，游戏结束。

假设双方都采取最优策略，记$p(m,n)$为一号玩家获胜的概率。例如，$p(1, n) = 1$，$p(m, 1) = 1/m$。

已知$p(7,5) \approx 0.51428571$。

求$\displaystyle \sum_{i=0}^{20}\sum_{j=0}^{20} p(7^i, 5^j)$并将你的答案保留$8$位小数。

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

