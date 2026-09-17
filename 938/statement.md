# Problem 938（PE 938）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=938](https://projecteuler.net/problem=938)。

## **Exhausting a Colour**

A deck of cards contains $R$ red cards and $B$ black cards.<br/>
A card is chosen uniformly randomly from the deck and removed. A second card is then chosen uniformly randomly from the cards remaining and removed.
- If both cards are red, they are discarded.
- If both cards are black, they are both put back in the deck.
- If they are different colours, the red card is put back in the deck and the black card is discarded.

Play ends when all the remaining cards in the deck are the same colour and let $P(R,B)$ be the probability that this colour is black. 

You are given $P(2,2) = 0.4666666667$, $P(10,9) = 0.4118903397$ and $P(34,25) = 0.3665688069$.

Find $P(24690,12345)$. Give your answer with $10$ digits after the decimal point.

## **耗尽同色牌**

考虑一副包含$R$张红牌和$B$张黑牌的牌组。<br/>
从牌组中均匀随机地选择并抽出一张牌，然后从剩余的牌中均匀随机地选择并抽出另一张牌。
- 如果两张牌都是红色，则丢弃这两张牌。
- 如果两张牌都是黑色，则放回这两张牌。
- 如果它们的颜色不同，则放回红牌并丢弃黑牌。

当牌组中所有剩余的牌都是同一种颜色时，游戏结束，并记$P(R,B)$为此时剩余牌的颜色均为黑色的概率。

已知$P(2,2) = 0.4666666667$，$P(10,9) = 0.4118903397$，$P(34,25) = 0.3665688069$。

求$P(24690,12345)$，并保留$10$位小数作为你的答案。

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

