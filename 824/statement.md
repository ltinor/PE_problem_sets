# Problem 824（PE 824）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=824](https://projecteuler.net/problem=824)。

## **Chess Sliders**

A <i>Slider</i> is a chess piece that can move one square left or right.

This problem uses a cylindrical chess board where the left hand edge of the board is connected to the right hand edge. This means that a Slider that is on the left hand edge of the chess board can move to the right hand edge of the same row and vice versa.

Let $L(N,K)$ be the number of ways $K$ non-attacking Sliders can be placed on an $N \times N$ cylindrical chess-board.

For example, $L(2,2)=4$ and $L(6,12)=4204761$.

Find $L(10^9,10^{15}) \bmod \left(10^7+19\right)^2$.

## **滑块**

有一种新的国际象棋棋子<i class=zh>滑块</i>，每次可以向左或向右移动一格。

考虑一个圆柱形棋盘，其左侧边界和右侧边界相连。也就是说，一个位于棋盘最左侧的滑块可以移动一步到达同一行的最右侧，反之亦然。

记$L(N,K)$为在$N \times N$的圆柱形棋盘上摆放$K$个互不攻击的滑块的方案数。

例如，$L(2,2)=4$，$L(6,12)=4204761$。

求$L(10^9,10^{15}) \bmod \left(10^7+19\right)^2$。

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
