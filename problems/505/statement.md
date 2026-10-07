# 双向递归（PE 505）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=505](https://projecteuler.net/problem=505)。

记：
$x(0)=0$
$x(1)=1$
$x(2k)=(3x(k)+2x(\lfloor \frac k 2 \rfloor)) \text{ mod } 2^{60} \text{ 对于 } k \ge 1 \text {，其中} \lfloor \text { } \rfloor \text {是下取整函数}$
$x(2k+1)=(2x(k)+3x(\lfloor \frac k 2 \rfloor)) \text{ mod } 2^{60} \text{ 对于 } k \ge 1$
$y_n(k)=x(k) \text{ if } k \ge n$
$y_n(k)=2^{60} - 1 - max(y_n(2k),y_n(2k+1)) \text{ if } k < n$
$A(n)=y_n(1)$

已知：
$x(2)=3$
$x(3)=2$
$x(4)=11$
$y_4(4)=11$
$y_4(3)=2^{60}-9$
$y_4(2)=2^{60}-12$
$y_4(1)=A(4)=8$
$A(10)=2^{60}-34$
$A(10^3)=101881$

求$A(10^{12})$。

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
