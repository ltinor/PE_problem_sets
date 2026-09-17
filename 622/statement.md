# Problem 622（PE 622）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=622](https://projecteuler.net/problem=622)。

## **Riffle Shuffle**

A riffle shuffle is executed as follows: a deck of cards is split into two equal halves, with the top half taken in the left hand and the bottom half taken in the right hand. Next, the cards are interleaved exactly, with the top card in the right half inserted just after the top card in the left half, the 2nd card in the right half just after the 2nd card in the left half, etc. (Note that this process preserves the location of the top and bottom card of the deck)

Let $s(n)$ be the minimum number of consecutive riffle shuffles needed to restore a deck of size $n$ to its original configuration, where $n$ is a positive even number.

Amazingly, a standard deck of $52$ cards will first return to its original configuration after only $8$ perfect shuffles, so $s(52)=8$. It can be verified that a deck of $86$ cards will also return to its original configuration after exactly $8$ shuffles, and the sum of all values of $n$ that satisfy $s(n)=8$ is $412$.

Find the sum of all values of $n$ that satisfy $s(n)=60$.

# **交叠洗牌**

交叠洗牌的操作流程如下：将牌堆分成相同数量的两半，上半部分置于左手，下半部分置于右手。接着将牌准确地交叉叠合，也就是说，将右手中的第一张牌放在左手中的第一张牌下方，将右手中的第二张牌放在左手中的第二张牌下方，依此类推。（注意这一操作并不改变原牌堆的第一张和最后一张牌的位置）

记$s(n)$为对$n$张牌组成的牌堆连续进行交叠洗牌直至牌堆恢复原样所需的次数，其中$n$是一个正偶数。

令人惊奇的是，对于52张牌的标准牌堆，首次回复原样仅需要$8$次完美的交叠洗牌。可以验证对于86张牌的牌堆，恢复原样同样只需要$8$次洗牌，而所有满足$s(n)=8$的$n$取值之和为$412$。

求所有满足$s(n)=60$的$n$取值之和。

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

