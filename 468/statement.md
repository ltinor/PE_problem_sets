# 二项式系数的光滑因数（PE 468）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
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

参数模式：输入 mode n。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
