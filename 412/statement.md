# 圭表填数（PE 412）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=412](https://projecteuler.net/problem=412)。

对于整数m，n（0&nbsp;≤&nbsp;n&nbsp;&lt;&nbsp;m），L(m,&nbsp;n)表示一个m×m的方格被挖去了右上角n×n的方格后留下的L型部分。

例如，L(5, 3)如下图所示：

<center><img src="/resources/images/0412_table53.png"></center>

我们给L(m,&nbsp;n)的每一格填上连续整数1, 2, 3, ...，并要求每个格子中的数要小于它左侧和下方格子中的数。

例如，下图是L(5,&nbsp;3)两种可行的填法：

<center><img src="/resources/images/0412_tablenums.png"></center>

记LC(m, n)是L(m, n)所有可行填法的数目。
可以验证LC(3,&nbsp;0) = 42, LC(5,&nbsp;3) = 250250, LC(6,&nbsp;3) = 406029023400以及LC(10,&nbsp;5) mod 76543217 = 61251715。

求LC(10000,&nbsp;5000) mod 76543217。

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
