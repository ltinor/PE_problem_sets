# 钟摆序列（PE 506）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=506](https://projecteuler.net/problem=506)。

考虑下面这个无限重复的数字序列：

<center>1234321234321234321...</center>

神奇的是，你可以将这个序列分解成一个整数的序列，使得第n个整数的各位数字之和恰好是n。

这个整数序列如下所示：

<center>1, 2, 3, 4, 32, 123, 43, 2123, 432, 1234, 32123, ...</center>

记v<sub>n</sub>是这个整数序列的第n个整数，例如，v<sub>2</sub>&nbsp;=&nbsp;2，v<sub>5</sub>&nbsp;=&nbsp;32，以及v<sub>11</sub>&nbsp;=&nbsp;32123。

记S(n)为v<sub>1</sub>&nbsp;+&nbsp;v<sub>2</sub>&nbsp;+&nbsp;...&nbsp;+&nbsp;v<sub>n</sub>。例如，S(11)&nbsp;=&nbsp;36120，以及S(1000)&nbsp;mod&nbsp;123454321&nbsp;=&nbsp;18232686。

求S(10<sup>14</sup>)&nbsp;mod&nbsp;123454321。

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
