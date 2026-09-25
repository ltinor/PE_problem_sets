# 多项式相除的余数（PE 498）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=498](https://projecteuler.net/problem=498)。

对于正整数n和m，我们分别定义多项式 F<sub>n</sub>(x) = x<sup>n</sup>和G<sub>m</sub>(x) = (x-1)<sup>m</sup>。
另外，我们再定义多项式R<sub>n,m</sub>(x)为多项式F<sub>n</sub>(x)除以多项式G<sub>m</sub>(x)的余数。
例如，R<sub>6,3</sub>(x) = 15x<sup>2</sup> - 24x + 10。

记C(n, m, d)是R<sub>n,m</sub>(x)中d次项系数的绝对值。
我们可以验证C(6, 3, 1) = 24，C(100, 10, 4) = 227197811615775。

求C(10<sup>13</sup>, 10<sup>12</sup>, 10<sup>4</sup>) mod 999999937。

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
