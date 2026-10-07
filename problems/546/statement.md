# 地板的复仇（PE 546）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=546](https://projecteuler.net/problem=546)。

记$f_k(n)=\sum^{n}_{i=0}f_k(\lfloor \frac{i}{k} \rfloor)$，其中$f_k(0)=1$ ，$\lfloor x \rfloor$表示地板函数（下取整函数）。

例如，f<sub>5</sub>(10) = 18，f<sub>7</sub>(100) = 1003，以及f<sub>2</sub>(10<sup>3</sup>) = 264830889564。

求$(\sum^{10}_{k=2}f_k(10^{14})) \text{ mod } (10^9+7)$。

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
