# Problem 787（PE 787）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=787](https://projecteuler.net/problem=787)。

## **Bézout's Game**

Two players play a game with two piles of stones. They take alternating turns. If there are currently $a$ stones in the first pile and $b$ stones in the second, a turn consists of removing $c\ge 0$ stones from the first pile and $d\ge 0$ from the second in such a way that $ad-bc=\pm1$. The winner is the player who first empties one of the piles.

Note that the game is only playable if the sizes of the two piles are coprime.

A game state $(a, b)$ is a winning position if the next player can guarantee a win with optimal play. Define $H(N)$ to be the number of winning positions $(a, b)$ with $\gcd(a,b)=1$, $a &gt; 0$, $b &gt; 0$ and $a+b \leq N$. Note the order matters, so for example $(2,1)$ and $(1,2)$ are distinct positions.

You are given $H(4)=5$ and $H(100)=2043$.

Find $H(10^9)$.

## **裴蜀游戏**

两名玩家正在用两堆石子玩游戏。他们轮流行动，若当前第一堆有$a$枚石子而第二堆有$b$枚，则这一轮的玩家可以从第一堆移除$c \ge 0$枚石子并从第二堆移除$d \ge 0$枚石子且满足$ad-bc=\pm 1$。首先将其中一堆石子清空的玩家获胜。

注意这个游戏只有在两堆石子的数目互质时才能进行。

若玩家面对游戏状态$(a,b)$时按照最优策略必定获胜，则称该游戏状态为必胜态。记$H(N)$为满足$\gcd(a,b)=1$，$a>0$，$b>0$和$a+b \leq N$的必胜态$(a,b)$的数目。在计算数目时需要注意顺序，例如$(2,1)$和$(1,2)$应视为不同的游戏状态。

已知$H(4)=5$和$H(100)=2043$。

求$H(10^9)$。

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

