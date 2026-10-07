# 最大公约数与摆方格（PE 440）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=440](https://projecteuler.net/problem=440)。

我们想要用1 × 2的空白方格或是1 × 1写有一个十进制数字的方格（如下所示）铺满长为n高为1的版面：

<center><img src="/resources/images/0440_tiles.png"></center>

例如，下面是铺满长为n = 8的版面的一些方式：

<center><img src="/resources/images/0440_some8.png"></center>

记铺满长为n的版面的方式数为T(n)。

例如，T(1) = 10，T(2) = 101。

对于1 ≤ a, b, c ≤ L，记S(L)是三重求和∑<sub>a,b,c</sub> gcd(T(c<sup>a</sup>), T(c<sup>b</sup>)) 。
例如：
S(2) = 10444
S(3) = 1292115238446807016106539989
S(4) mod 987&nbsp;898&nbsp;789 = 670616280.

求 S(2000) mod 987&nbsp;898&nbsp;789。

---

## 输入格式

参数模式：输入 mode n。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANS = 970746056
