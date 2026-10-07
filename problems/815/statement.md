# Problem 815（PE 815）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=815](https://projecteuler.net/problem=815)。

## **Group by Value**

A pack of cards contains $4n$ cards with four identical cards of each value. The pack is shuffled and cards are dealt one at a time and placed in piles of equal value. If the card has the same value as any pile it is placed in that pile. If there is no pile of that value then it begins a new pile. When a pile has four cards of the same value it is removed.

Throughout the process the maximum number of non empty piles is recorded. Let $E(n)$ be its expected value. You are given $E(2) = 1.97142857$ rounded to $8$ decimal places.

Find $E(60)$. Give your answer rounded to $8$ digits after the decimal point. 

## **点数分组**

一副共$4n$张牌有$n$种点数，每种点数四张。将这副牌洗牌后，每次打出一张牌，并根据点数加入牌堆：如果已有该点数的牌堆，则将牌加入该堆；如果没有该点数的牌堆，则将该牌单独作为新牌堆。如果某个牌堆集齐了四张牌，则将该牌堆移除。

记录在上述过程中任意时刻非空牌堆数量的最大值，并记$E(n)$为其期望值。已知$E(2) = 1.97142857$，四舍五入至小数点后$8$位。

求$E(60)$，并将你的答案四舍五入至小数点后$8$位。

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
参考常量: PE_ANSWER_INT = 263959319LL
