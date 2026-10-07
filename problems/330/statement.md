# 欧拉数（PE 330）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=330](https://projecteuler.net/problem=330)。

无穷实数序列$a(n)$按如下方式定义:

<center><img src="https://projecteuler.net/project/images/p330_formula.gif"></center>

例如，
$$a(0)=\frac{1}{1!}+\frac{1}{2!}+\frac{1}{3!}+...=e-1$$
$$a(1)=\frac{e-1}{1!}+\frac{1}{2!}+\frac{1}{3!}+...=2e-3$$
$$a(2)=\frac{2e-3}{1!}+\frac{e-1}{2!}+\frac{1}{3!}+...=\frac{7}{2}e-6$$
其中$e = 2.7182818\ldots$是欧拉常数。

可以发现$a(n)$总是可以表达为$\frac{A(n)e+B(n)}{n!}$的形式，其中$A(n)$和$B(n)$均为整数。 
例如$a(10) = \frac{328161643 e − 652694486}{10!}$。

求$A(10^9) + B(10^9)$，并将你的答案模$77\ 777\ 777$取余。

---

## 输入格式

参数模式：输入 N。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
