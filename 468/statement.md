# 二项式系数的光滑因数（PE 468）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=468](https://projecteuler.net/problem=468)。

当一个正整数的所有质因数都不大于 B时，这个整数被称为<strong>B-光滑数</strong>。

记S<sub>B</sub>(n)是n的最大的B-光滑因数。
例如：

S<sub>1</sub>(10) = 1
S<sub>4</sub>(2100) = 12
S<sub>17</sub>(2496144) = 5712

记F(n) = ∑<sub>1≤B≤n</sub> ∑<sub>0≤r≤n</sub> S<sub>B</sub>(C(n,r))，其中C(n,r)表示二项式系数。
例如:

F(11) = 3132
F(1&nbsp;111) mod 1&nbsp;000&nbsp;000&nbsp;993 = 706036312
F(111&nbsp;111) mod 1&nbsp;000&nbsp;000&nbsp;993 = 22156169

求F(11&nbsp;111&nbsp;111) mod 1&nbsp;000&nbsp;000&nbsp;993。

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

