# 给长方形铺地砖（PE 405）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=405](https://projecteuler.net/problem=405)。

我们希望给一个长是宽的两倍的长方形铺上地砖。
T(0)表示只用一个长方形的铺法。
对于n &gt; 0，T(n)表示以T(n-1)为基础，将后者的每一块地砖作如下替换得到的新铺法：

<center><img src="/resources/images/0405_tile1.png"></center>

以下动画演示了n从0到5时的T(n)：

<center><img src="/resources/images/0405_tile2.gif"></center>

记f(n)是T(n)中有四块地砖相遇的点的数目。
已知f(1) = 0，f(4) = 82，以及f(10<sup>9</sup>) mod 17<sup>7</sup> = 126897180。

当k = 10<sup>18</sup>时，求f(10<sup>k</sup>)，并将其模17<sup>7</sup>取余作为你的答案。

---

## 输入格式

参数模式：输入 n。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
