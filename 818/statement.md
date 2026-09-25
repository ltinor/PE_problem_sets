# Problem 818（PE 818）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=818](https://projecteuler.net/problem=818)。

## **SET**

The SET® card game is played with a pack of $81$ distinct cards. Each card has four features (Shape, Color, Number, Shading). Each feature has three different variants (e.g. Color can be red, purple, green).

A <i>SET</i> consists of three different cards such that each feature is either the same on each card or different on each card.

For a collection $C_n$ of $n$ cards, let $S(C_n)$ denote the number of <i>SET</i>s in $C_n$. Then define $F(n) = \sum\limits_{C_n} S(C_n)^4$ where $C_n$ ranges through all collections of $n$ cards (among the $81$ cards). You are given $F(3) = 1080$ and $F(6) = 159690960$.

Find $F(12)$.

Note: SET is a registered trademark of Cannei, LLC. All rights reserved. Used with permission from PlayMonster, LLC.

## **神奇形色牌**

神奇形色牌（SET®）由$81$张不同的牌组成。每张牌有四个特征：形状、颜色、数字、阴影。每个特征有三种可能，例如颜色可以是红、黄、绿之一。

一个<i class=zh>组合</i>由三张牌构成，且对于任意特征，要么三张牌完全相同，要么三张牌完全不同。

考虑由$n$张牌组成的特定牌组$C_n$，记$S(C_n)$为这些牌可以组成的<i class=zh>组合</i>的数目。再记$F(n) = \sum\limits_{C_n} S(C_n)^4$，其中$C_n$遍历所有从$81$张牌中取出$n$张所能组成的牌组。已知$F(3) = 1080$，$F(6) = 159690960$。

求$F(12)$。

注：神奇形色牌(SET®)是Cannei有限公司的注册商标，保留所有权利；由PlayMonster有限公司授权使用。

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
参考常量: PE_ANSWER = 17423445763272143LL
