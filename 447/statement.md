# 撤销函数 C（PE 447）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=447](https://projecteuler.net/problem=447)。

对于任意整数n&gt;1，函数族f<sub>n,a,b</sub>按如下方式定义：f<sub>n,a,b</sub>(x)≡ax+b mod n，其中a,b,x都是整数，且0&lt;a&lt;n，0≤b&lt;n，0≤x&lt;n。
我们称f<sub>n,a,b</sub>为撤销函数，当对于0≤x&lt;n均有在模n意义下f<sub>n,a,b</sub>(f<sub>n,a,b</sub>(x))≡f<sub>n,a,b</sub>(x)。
记R(n)是给定n下撤销函数的数目。

记F(N)=∑R(n)，其中2≤n≤N。
已知F(10<sup>7</sup>)≡638042271 (mod 1 000 000 007)。
 
求F(10<sup>14</sup>) (mod 1 000 000 007)。

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
参考常量: MAXN = 20000000
