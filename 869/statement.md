# Problem 869（PE 869）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=869](https://projecteuler.net/problem=869)。

## **Prime Guessing**

A prime is drawn uniformly from all primes not exceeding $N$. The prime is written in binary notation, and a player tries to guess it bit-by-bit starting at the least significant bit. The player scores one point for each bit they guess correctly. Immediately after each guess, the player is informed whether their guess was correct, and also whether it was the last bit in the number - in which case the game is over.

Let $E(N)$ be the expected number of points assuming that the player always guesses to maximize their score. For example, $E(10)=2$, achievable by always guessing "$1$". You are also given $E(30)=2.9$.

Find $E(10^8)$. Give your answer rounded to eight digits after the decimal point.

## 猜质数

均匀随机地选择一个不超过$N$的质数，将其转为二进制表示，并让一名玩家从最低位开始逐位猜测这个质数。玩家每猜对一位数字可得一分；每次猜测之后，玩家可以立即知道猜测是否正确，以及是否是这个质数的最后一位，若是则游戏结束。

假设玩家总是采取最优策略，记$E(N)$为玩家的期望得分。例如，$E(10)=2$，对应的最优策略是始终猜测"$1$"。此外，还已知$E(30)=2.9$。

求$E(10^8)$，并四舍五入保留八位小数作为你的答案。

---

## 输入格式

字符 `PE`：输出原题官方答案。

## 输出格式

原题官方答案。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
