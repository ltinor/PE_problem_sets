# 滑块（PE 244）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=244](https://projecteuler.net/problem=244)。

你可能知道<i>十五滑块谜题</i>这个游戏。现在，我们用7块红色滑块和8块蓝色滑块取代了原来标有数字的滑块。

我们用被滑动的滑块所滑的方向对应英文单词（左=left=L，右=right=R，上=up=U，下=down=D）的首字母记录每一步，例如，从布局(<b>S</b>)出发，经过滑动序列<b>LULUR</b>，我们得到了布局(<b>E</b>)：

<center><img src="/resources/images/0244_start.gif"></center>
<center>(S)</center>
<center><img src="/resources/images/0244_example.gif"></center>
<center>(E)</center>

对于每一步，我们按如下方式（伪代码）计算其校验和：
>checksum = 0
>checksum = (checksum × 243 + m<sub>1</sub>) mod 100&thinsp;000&thinsp;007
>checksum = (checksum × 243 + m<sub>2</sub>) mod 100&thinsp;000&thinsp;007
>&nbsp;&nbsp;&nbsp;…
>checksum = (checksum × 243 + m<sub>n</sub>) mod 100&thinsp;000&thinsp;007

其中m<sub>k</sub>是滑动序列中第k<sup>th</sup>个字母的ASCII码，具体数值如下：

&nbsp;|&nbsp;
:-:|:-:
L|76
R|82
U|85
D|68

对于上述滑动序列<b>LULUR</b>，校验和为19761398。

现在，找出所有从布局(<b>S</b>)出发得到布局(<b>T</b>)的最短序列。

<center><img src="/resources/images/0244_start.gif"></center>
<center>(S)</center>
<center><img src="/resources/images/0244_target.gif"></center>
<center>(T)</center>

所有这些最短序列的校验和之和是多少？

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

