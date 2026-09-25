# 几乎是π（PE 461）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=461](https://projecteuler.net/problem=461)。

对于所有非负整数k，记f<sub>n</sub>(k)&nbsp;=&nbsp;e<sup>k/n</sup>&nbsp;-&nbsp;1。

令人惊讶的是，f<sub>200</sub>(6)&nbsp;+&nbsp;f<sub>200</sub>(75)&nbsp;+&nbsp;f<sub>200</sub>(89)&nbsp;+&nbsp;f<sub>200</sub>(226)&nbsp;= <u>3.1415926</u>44529…&nbsp;≈&nbsp;π.

事实上，这是当n&nbsp;=&nbsp;200时，形如f<sub>n</sub>(a)&nbsp;+&nbsp;f<sub>n</sub>(b)&nbsp;+&nbsp;f<sub>n</sub>(c)&nbsp;+&nbsp;f<sub>n</sub>(d)的式子对π的最好近似值。

当a，b，c，d使得误差|&nbsp;f<sub>n</sub>(a)&nbsp;+&nbsp;f<sub>n</sub>(b)&nbsp;+&nbsp;f<sub>n</sub>(c)&nbsp;+&nbsp;f<sub>n</sub>(d)&nbsp;-&nbsp;π|取最小值时，记g(n)&nbsp;=&nbsp;a<sup>2</sup>&nbsp;+&nbsp;b<sup>2</sup>&nbsp;+&nbsp;c<sup>2</sup>&nbsp;+&nbsp;d<sup>&thinsp;2</sup>
（其中|x|指的是x的绝对值）。

已知g(200)&nbsp;=&nbsp;6<sup>2</sup>&nbsp;+&nbsp;75<sup>2</sup>&nbsp;+&nbsp;89<sup>2</sup>&nbsp;+&nbsp;226<sup>2</sup>&nbsp;=&nbsp;64658。

求g(10000)。

---

## 输入格式

参数模式：输入 mode。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
