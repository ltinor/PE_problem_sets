# 交错的椭圆（PE 404）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=404](https://projecteuler.net/problem=404)。

E<sub>a</sub>是一个椭圆，其方程为x<sup>2</sup> + 4y<sup>2</sup> = 4a<sup>2</sup>。
E<sub>a</sub>'是将E<sub>a</sub>绕原点O(0, 0)逆时针旋转角θ得到的图形，其中0° &lt; θ &lt; 90°。

<center><img src="/resources/images/0404_c_ellipse.gif"></center>

b是两个椭圆离原点较近的两个交点到原点的距离，而c是另外两个较远的交点到远点的距离。
如果有序三元组(a, b, c)中a、b和c均为正整数，我们称之为规范椭圆三元组。
例如，(209, 247, 286)就是一个规范椭圆三元组。

记C(N)为所有满足a ≤ N的规范椭圆三元组(a, b, c)的数目。
可以验证C(10<sup>3</sup>) = 7，C(10<sup>4</sup>) = 106，以及C(10<sup>6</sup>) = 11845。

求C(10<sup>17</sup>)。

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
