# 撤销函数 B（PE 446）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=446](https://projecteuler.net/problem=446)。

对于任意整数n&gt;1，函数族f<sub>n,a,b</sub>按如下方式定义：f<sub>n,a,b</sub>(x)≡ax+b mod n，其中a,b,x都是整数，且0&lt;a&lt;n，0≤b&lt;n，0≤x&lt;n。
我们称f<sub>n,a,b</sub>为撤销函数，当对于0≤x&lt;n均有在模n意义下f<sub>n,a,b</sub>(f<sub>n,a,b</sub>(x))≡f<sub>n,a,b</sub>(x)。
记R(n)是给定n下撤销函数的数目。

记F(N)=∑R(n<sup>4</sup>+4)，其中1≤n≤N。  
已知F(1024)=77532377300600。
 
求F(10<sup>7</sup>) (mod 1 000 000 007)。

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

