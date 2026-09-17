# 变种考拉兹序列（PE 277）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=277](https://projecteuler.net/problem=277)。

由a<sub>1</sub>开始根据下列规则生成的整数数列被称为变种考拉兹序列：

a<sub>n+1</sub> = a<sub>n</sub>/3，如果a<sub>n</sub>能被3整除。这是一个较大的下降，我们记这一步操作为“D”。

a<sub>n+1</sub> = (4a<sub>n</sub> + 2)/3，如果a<sub>n</sub>除以3余1。这是一个较大的上升，我们记这一步操作为“U”。

a<sub>n+1</sub> = (2a<sub>n</sub> - 1)/3，如果a<sub>n</sub>除以3余2。这是一个较小的下降，我们记这一步操作为“d”。

一旦有a<sub>n</sub> = 1，序列结束。

给定任意正整数，我们可以列出其操作步骤。
例如，若a<sub>1</sub>=231，整数数列{a<sub>n</sub>}={231,77,51,17,11,7,10,14,9,3,1}对应的操作步骤是"DdDddUUdDD"。

当然，存在其它的整数数列其操作步骤的开头同样是"DdDddUUdDD...."。
例如，若a<sub>1</sub>=1004064，则操作步骤是DdDddUUdDDDdUDUUUdDdUUDDDUdDD。
事实上，1004064是在a<sub>1</sub> &gt; 10<sup>6</sup>范围内，操作步骤以DdDddUUdDD开头的最小值。

在a<sub>1</sub> &gt; 10<sup>15</sup>范围内，操作步骤以"UDDDUdddDDUDDddDdDddDDUDDdUUDd"开头的最小值是多少？

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

