# Problem 798（PE 798）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=798](https://projecteuler.net/problem=798)。

## **Card Stacking Game**

Two players play a game with a deck of cards which contains $s$ suits with each suit containing $n$ cards numbered from $1$ to $n$.

Before the game starts, a set of cards (which may be empty) is picked from the deck and placed face-up on the table, with no overlap. These are called the visible cards.

The players then make moves in turn.
A move consists of choosing a card X from the rest of the deck and placing it face-up on top of a visible card Y, subject to the following restrictions:
- X and Y must be the same suit;
- the value of X must be larger than the value of Y.

The card X then covers the card Y and replaces Y as a visible card.
The player unable to make a valid move loses and play stops.

Let $C(n, s)$ be the number of different initial sets of cards for which the first player will lose given best play for both players.

For example, $C(3, 2) = 26$ and $C(13, 4) \equiv 540318329 \pmod {1\ 000\ 000\ 007}$.

Find $C(10^7, 10^7)$. Give your answer modulo $1\ 000\ 000\ 007$.

## **叠卡游戏**

两位玩家正在玩一个游戏，这个游戏需要用到一副有$n$个花色、每个花色包含$1$到$n$共$n$种点数的牌。

在游戏开始前，从这副牌中拿出一部分（可以不拿），并将其面朝上互不接触地放在桌面上。这些牌被称为可见牌。

此后，两名玩家轮流行动。每一轮行动，玩家必须从剩下的牌中选择一张牌X，并将其面朝上放在一张可见牌Y上，且X和Y需要满足：
- X和Y的花色必须相同；
- X的点数必须大于Y的点数。

X会完全覆盖Y并取代Y成为可见牌。
首先无法进行合法行动的玩家失败，游戏结束。

若两位玩家均采取最优策略，记$C(n, s)$为先手玩家必败的可见牌布置局面的数目。

例如，$C(3, 2) = 26$，$C(13, 4) \equiv 540318329 \pmod {1\ 000\ 000\ 007}$。

求$C(10^7, 10^7)$，并将你的答案对$1\ 000\ 000\ 007$取余。

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

