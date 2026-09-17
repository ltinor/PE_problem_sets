# 混合物（PE 478）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=478](https://projecteuler.net/problem=478)。

考虑由三种成份**A**，**B**和**C**组成的**混合物**。每种混合物可以用所含**A**，**B**，**C**三种成份的比例来表示，也就是说(a&nbsp;:&nbsp;b&nbsp;:&nbsp;c)。例如，一种比例是(2&nbsp;:&nbsp;3&nbsp;:&nbsp;5)的混合物包含有20% **A**，30% **B**和50% **C**。

我们不能从混合物中分理处不同的成分，但是我们可以组合不同数量的不同混合物来组成有新的比例的混合物。

例如，我们现在有三种比例分别是(3&nbsp;:&nbsp;0&nbsp;:&nbsp;2)，(3&nbsp;:&nbsp;6&nbsp;:&nbsp;11)和(3&nbsp;:&nbsp;3&nbsp;:&nbsp;4)的混合物。将10单位的第一种混合物，20单位的第二种混合物和30单位第三种混合物，我们得到一种新的混合物，比例是(6&nbsp;:&nbsp;5&nbsp;:&nbsp;9)，因为：

(10·<sup>3</sup>/<sub>5</sub>&nbsp;+&nbsp;20·<sup>3</sup>/<sub>20</sub>&nbsp;+&nbsp;30·<sup>3</sup>/<sub>10</sub>&nbsp;:&nbsp;10·<sup>0</sup>/<sub>5</sub>&nbsp;+&nbsp;20·<sup>6</sup>/<sub>20</sub>&nbsp;+&nbsp;30·<sup>3</sup>/<sub>10</sub>&nbsp;:&nbsp;10·<sup>2</sup>/<sub>5</sub>&nbsp;+&nbsp;20·<sup>11</sup>/<sub>20</sub>&nbsp;+&nbsp;30·<sup>4</sup>/<sub>10</sub>) = (18&nbsp;:&nbsp;15&nbsp;:&nbsp;27) = (6&nbsp;:&nbsp;5&nbsp;:&nbsp;9)

然而，用同样的三种混合物，永远无法配置出比例为(3&nbsp;:&nbsp;2&nbsp;:&nbsp;1)的混合物，因为成分**B**的量永远比成分**C**要少。

记n是一个正整数。假设对于任意整数a，b，c满足0 ≤ a, b, c ≤ n且gcd(a, b, c) = 1，我们都有一种比例是(a, b, c)的混合物。记M(n)是所有这些混合物的集合。

例如，M(2)包含有下列19种不同比例的混合物：

{(0&nbsp;:&nbsp;0&nbsp;:&nbsp;1), (0&nbsp;:&nbsp;1&nbsp;:&nbsp;0), (0&nbsp;:&nbsp;1&nbsp;:&nbsp;1), (0&nbsp;:&nbsp;1&nbsp;:&nbsp;2), (0&nbsp;:&nbsp;2&nbsp;:&nbsp;1), 
(1&nbsp;:&nbsp;0&nbsp;:&nbsp;0), (1&nbsp;:&nbsp;0&nbsp;:&nbsp;1), (1&nbsp;:&nbsp;0&nbsp;:&nbsp;2), (1&nbsp;:&nbsp;1&nbsp;:&nbsp;0), (1&nbsp;:&nbsp;1&nbsp;:&nbsp;1), 
(1&nbsp;:&nbsp;1&nbsp;:&nbsp;2), (1&nbsp;:&nbsp;2&nbsp;:&nbsp;0), (1&nbsp;:&nbsp;2&nbsp;:&nbsp;1), (1&nbsp;:&nbsp;2&nbsp;:&nbsp;2), (2&nbsp;:&nbsp;0&nbsp;:&nbsp;1), 
(2&nbsp;:&nbsp;1&nbsp;:&nbsp;0), (2&nbsp;:&nbsp;1&nbsp;:&nbsp;1), (2&nbsp;:&nbsp;1&nbsp;:&nbsp;2), (2&nbsp;:&nbsp;2&nbsp;:&nbsp;1)}.

记E(n)是能够构成混合物比例(1 : 1 : 1)的M(n)的子集数目。 
可以验证E(1) = 103，E(2) = 520447，E(10)&nbsp;mod&nbsp;11<sup>8</sup> = 82608406，E(500)&nbsp;mod&nbsp;11<sup>8</sup> = 13801403。
求E(10&nbsp;000&nbsp;000)&nbsp;mod&nbsp;11<sup>8</sup>。

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

