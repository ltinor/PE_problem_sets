# Problem 711（PE 711）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=711](https://projecteuler.net/problem=711)。

## **Binary Blackboard**

Oscar and Eric play the following game. First, they agree on a positive integer $n$, and they begin by writing its binary representation on a blackboard. They then take turns, with Oscar going first, to write a number on the blackboard in binary representation, such that the sum of all written numbers does not exceed $2n$.

The game ends when there are no valid moves left. Oscar wins if the number of $1$s on the blackboard is odd, and Eric wins if it is even.

Let $S(N)$ be the sum of all $n \le 2^N$ for which Eric can guarantee winning, assuming optimal play.

For example, the first few values of $n$ for which Eric can guarantee winning are $1,3,4,7,15,16$. Hence $S(4)=46$.
You are also given that $S(12) = 54532$ and $S(1234) \equiv 690421393 \pmod{1\ 000\ 000\ 007}$.

Find $S(12\ 345\ 678)$. Give your answer modulo $1\ 000\ 000\ 007$.

## **二进制黑板**

奥斯卡和埃里克正在玩游戏。首先，他们共同选择一个整数$n$，然后将其二进制表示写在黑板上。然后，由奥斯卡先行，两人轮流在黑板上写上一个数的二进制表示，同时要求所有写在黑板上的数之和不能超过$2n$。

当不能够再写任何数时，游戏结束。若游戏结束时黑板上的$1$的数目为奇数，则奥斯卡获胜，若为偶数则埃里克获胜。

在双方都采用最优策略的情况下，记$S(N)$为在$n \le 2^N$的范围内埃里克能够保证获胜的$n$之和。

例如，最小的几个埃里克能够保证获胜的$n$分别是$1,3,4,7,15,16$。因此$S(4)=46$。
已知$S(12) = 54532$，$S(1234) \equiv 690421393 \pmod{1\ 000\ 000\ 007}$。

求$S(12\ 345\ 678)$并将你的答案对$1\ 000\ 000\ 007$取余。

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

