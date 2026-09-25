# 贝塞尔曲线（PE 363）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=363](https://projecteuler.net/problem=363)。

一条立方贝塞尔曲线由四个点确定：P<sub>0</sub>、P<sub>1</sub>、P<sub>2</sub>和P<sub>3</sub>。

<center><img src="/resources/images/0363_bezier.png"></center>

曲线的构造方式如下所述：
在线段P<sub>0</sub>P<sub>1</sub>、P<sub>1</sub>P<sub>2</sub>和P<sub>2</sub>P<sub>3</sub>上，取点Q<sub>0</sub>、Q<sub>1</sub>和Q<sub>2</sub>，满足
P<sub>0</sub>Q<sub>0</sub> / P<sub>0</sub>P<sub>1</sub> = P<sub>1</sub>Q<sub>1</sub> / P<sub>1</sub>P<sub>2</sub> = P<sub>2</sub>Q<sub>2</sub> / P<sub>2</sub>P<sub>3</sub> = t (t 属于 [0,1])。
在线段Q<sub>0</sub>Q<sub>1</sub>和Q<sub>1</sub>Q<sub>2</sub>上，取点R<sub>0</sub>和R<sub>1</sub>，满足
Q<sub>0</sub>R<sub>0</sub>  / Q<sub>0</sub>Q<sub>1</sub> = Q<sub>1</sub>R<sub>1</sub> / Q<sub>1</sub>Q<sub>2</sub> = t，t的值同上。
在线段R<sub>0</sub>R<sub>1</sub>上，取点B，满足R<sub>0</sub>B / R<sub>0</sub>R<sub>1</sub> = t，t的值同上。
由点P<sub>0</sub>、P<sub>1</sub>、P<sub>2</sub>、P<sub>3</sub>确定的贝塞尔曲线即为Q<sub>0</sub>在线段P<sub>0</sub>P<sub>1</sub>上取遍所有位置时点B的轨迹。
（请注意，对于所有的取点过程，t的值都是相同的。）

在<a href="http://home.kpn.nl/hklein/bezier/bezier.html" target="_blank">这个（外部链接）网址</a>，你会找到一个应用，允许你拖动点P<sub>0</sub>、P<sub>1</sub>、P<sub>2</sub>和P<sub>3</sub>，以观察由这些点确定的贝塞尔曲线（绿色曲线）的外观。你也可以在线段P<sub>0</sub>P<sub>1</sub>上拖动点Q<sub>0</sub>。

根据构造过程，显然贝塞尔曲线在P<sub>0</sub>处与线段P<sub>0</sub>P<sub>1</sub>相切，在P<sub>3</sub>处于P<sub>2</sub>P<sub>3</sub>相切。

由P<sub>0</sub>=(1,0)、P<sub>1</sub>=(1,v)、P<sub>2</sub>=(v,1)和P<sub>3</sub>=(0,1)确定的贝塞尔曲线被用于近似表示四分之一圆.
适当地选取v &gt; 0，以使由线段OP<sub>0</sub>、OP<sub>3</sub>和该曲线包围的面积等于<sup>π</sup>/<sub>4</sub>（四分之一圆的面积）。

该曲线的长度和四分之一圆弧的长度相差百分之多少？

也就是说，如果该曲线的长度为L，试计算100 × $\frac{L − π/2}{π/2}$。

将你的答案保留小数点后10位数字。

---

## 输入格式

参数模式：输入 steps。
- 字符 `PE`：输出原题官方答案。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
