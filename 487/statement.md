# 幂之和之和（PE 487）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=487](https://projecteuler.net/problem=487)。

记f<sub>k</sub>(n)是前n个正整数的k次方的和。

例如，f<sub>2</sub>(10) = 1<sup>2</sup> + 2<sup>2</sup> + 3<sup>2</sup> + 4<sup>2</sup> + 5<sup>2</sup> + 6<sup>2</sup> + 7<sup>2</sup> + 8<sup>2</sup> + 9<sup>2</sup> + 10<sup>2</sup> = 385。

记S<sub>k</sub>(n)是所有满足1 ≤ i ≤ n的f<sub>k</sub>(i)的和。例如，S<sub>4</sub>(100) = 35375333830。

对于所有在2 ⋅ 10<sup>9</sup>与2 ⋅ 10<sup>9</sup> + 2000之间的素数p，求∑ (S<sub>10000</sub>(10<sup>12</sup>) mod p)。

---

## 输入格式

参数模式：输入 K。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER = 24973710987372LL
