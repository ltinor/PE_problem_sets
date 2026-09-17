# 图厄-摩尔斯序列的子序列（PE 361）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=361](https://projecteuler.net/problem=361)。

$A_n$|0&nbsp;|1&nbsp;|2&nbsp;|3&nbsp;|4&nbsp;|5&nbsp;|6&nbsp;|9&nbsp;|10|11|12|13|18|...

We can also verify that A<sub>100</sub> = 3251 and A<sub>1000</sub> = 80852364498.

Find the last 9 digits of $\sum\_{k=1}^{18}A\_{10^k}$.

**图厄-摩尔斯序列的子序列**

<b>图厄-摩尔斯序列</b> {T<sub>n</sub>}是满足下列条件的二进制序列：
- T<sub>0</sub> = 0
- T<sub>2n</sub> = T<sub>n</sub>
- T<sub>2n+1</sub> = 1 - T<sub>n</sub>

{T<sub>n</sub>}的前几项如下所示：
01101001<span style="color:red;">10010</span>1101001011001101001....

有些整数的二进制表示是序列{T<sub>n</sub>}的子序列，我们定义{A<sub>n</sub>}为将这些数排序后组成的序列。
例如，十进制数18的二进制表示为10010。10010出现在{T<sub>n</sub>}中（从T<sub>8</sub>到T<sub>12</sub>），因此18是{A<sub>n</sub>}中的元素。
十进制数14的二进制表示为1110。1110永远不会出现在{T<sub>n</sub>}中，因此14不是{A<sub>n</sub>}中的元素。

A<sub>n</sub>的前几项如下所示：

n    |0&nbsp;|1&nbsp;|2&nbsp;|3&nbsp;|4&nbsp;|5&nbsp;|6&nbsp;|7&nbsp;|8&nbsp;|9&nbsp;|10|11|12|...
-----|--|--|--|--|--|--|--|--|--|--|--|--|--|---
$A_n$|0&nbsp;|1&nbsp;|2&nbsp;|3&nbsp;|4&nbsp;|5&nbsp;|6&nbsp;|9&nbsp;|10|11|12|13|18|...

我们还可以验证A<sub>100</sub> = 3251以及A<sub>1000</sub> = 80852364498。

求$\sum\_{k=1}^{18}A\_{10^k}$的最后9位数字。

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

