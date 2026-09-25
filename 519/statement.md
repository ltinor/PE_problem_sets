# 三色硬币喷泉（PE 519）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=519](https://projecteuler.net/problem=519)。

将硬币排成一行或多行，最下面一行为一整块没有间隙，上一行的每一枚硬币恰好和下一行的两枚硬币接触，这样的排列方式称为硬币**喷泉**。记f(n)是用n枚硬币所能组成的喷泉数目。对于4枚硬币，有三种可能的排列方式：

<center><img src="/resources/images/0519_coin_fountain.png"></center>

因此f(4)&nbsp;=&nbsp;3，同时我们已知f(10)&nbsp;=&nbsp;78。

将所有f(n)种不同的喷泉上的n枚硬币都染上三种不同颜色之一，且相邻硬币所染颜色不能相同，所有的染色方法数记为T(n)。下图所示为对4枚硬币组成的三种可行喷泉中的一种进行染色的所有可能结果：

<center><img src="/resources/images/0519_tricolored_coin_fountain.png"></center>

已知T(4)&nbsp;=&nbsp;48以及T(10)&nbsp;=&nbsp;17760。

求T(20000)的最后9位数字。

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
