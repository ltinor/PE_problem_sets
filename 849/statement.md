# Problem 849（PE 849）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=849](https://projecteuler.net/problem=849)。

## **The Tournament**

In a tournament there are $n$ teams and each team plays each other team twice. A team gets two points for a win, one point for a draw and no points for a loss.

With two teams there are three possible outcomes for the total points. $(4,0)$ where a team wins twice, $(3,1)$ where a team wins and draws, and $(2,2)$ where either there are two draws or a team wins one game and loses the other. Here we do not distinguish the teams and so $(3,1)$ and $(1,3)$ are considered identical.

Let $F(n)$ be the total number of possible final outcomes with $n$ teams, so that $F(2) = 3$.<br />
You are also given $F(7) = 32923$.

Find $F(100)$. Give your answer modulo $10^9+7$.

## **锦标赛**

在一场锦标赛中，共有$n$支队伍参赛，每支队伍需与任意其它队伍各对战两次。获胜的队伍得两分，平局得一分，落败不得分。

只有两支队伍时，共有三种可能的得分结果。若一支队伍两次都获胜则结果是$(4,0)$，若一支队伍赢一次平一次则结果是$(3,1)$，若两次都是平局或者各自一胜一负则结果是$(2,2)$。得分结果不区分队伍，因此$(3,1)$和$(1,3)$视为相同的结果。

记$F(n)$为有$n$支队伍时所有可能的最终得分结果的数目，因此$F(2) = 3$。<br />
已知$F(7) = 32923$。

求$F(100)$，并将你的答案对$10^9+7$取余。

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

