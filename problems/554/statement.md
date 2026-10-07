# 棋盘上的半人马（PE 554）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=554](https://projecteuler.net/problem=554)。

在国际象棋棋盘上，半人马可以像国王或者骑士那样移动。如下的图象说明了半人马（用颠倒的国王表示）在8x8的棋盘上的有效移动范围。
 
<center><img src="/resources/images/0554-centaurs.png" alt="p554-centaurs.png"></center>

可以证明，在一个2nx2n的棋盘上，最多可以放置n<sup>2</sup>个互不攻击的半人马。
记C(n)为在2nx2n的的棋盘上放置n<sup>2</sup>个互不攻击的半人马的方式数。
例如，C(1)&nbsp;=&nbsp;4，C(2)&nbsp;=&nbsp;25，C(10)&nbsp;=&nbsp;1477721。

记F<sub>i</sub>为第i个斐波那契数，斐波那契数的定义为F<sub>1</sub>&nbsp;=&nbsp;F<sub>2</sub>&nbsp;=&nbsp;1且当i&nbsp;&gt;&nbsp;2时F<sub>i</sub>&nbsp;=&nbsp;F<sub>i-1</sub>&nbsp;+&nbsp;F<sub>i-2</sub>。

求$\displaystyle \left( \sum_{i=2}^{90} C(F_i) \right) \text{mod } (10^8+7)$。

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
