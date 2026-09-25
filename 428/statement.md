# 圆圈项链（PE 428）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=428](https://projecteuler.net/problem=428)。

取a，b，c均为正整数。
取共线的四点W，X，Y，Z，满足|WX| = a，|XY| = b，|YZ| = c而|WZ| = a + b + c。
圆C<sub>in</sub>是以XY为直径的圆。
圆C<sub>out</sub>是以WZ为直径的圆。

三元组(a, b, c)被称为<em>项链三元组</em>，如果存在k ≥ 3个不同的圆C<sub>1</sub>，C<sub>2</sub>，……，C<sub>k</sub>满足：
- 对于任意1 ≤ i, j ≤ k且i ≠ j，C<sub>i</sub>和C<sub>j</sub>没有公共内部点。
- 对于任意1 ≤ i ≤ k，C<sub>i</sub>和C<sub>in</sub>与C<sub>out</sub>均相切。
- 对于任意1 ≤ i &lt; k，C<sub>i</sub>和C<sub>i+1</sub>相切。
- C<sub>k</sub>和C<sub>1</sub>相切。

例如，(5, 5, 5)和(4, 3, 21)都是项链三元组，而(2, 2, 5)则不是。

<center><img src="/resources/images/0428_necklace.png"></center>

记T(n)是项链三元组(a, b, c)的数量，其中a，b，c均为正整数，且b ≤ n。例如，T(1)&nbsp;=&nbsp;9，T(20)&nbsp;=&nbsp;732以及T(3000)&nbsp;=&nbsp;438106。

求T(1&nbsp;000&nbsp;000&nbsp;000)。

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
参考常量: PE428_ANS = 747215561862LL
