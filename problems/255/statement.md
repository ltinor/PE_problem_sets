# 近似平方根（PE 255）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=255](https://projecteuler.net/problem=255)。

我们定义正整数n的*近似平方根*为与n的实际平方根最接近的整数。

如下的过程（实际上就是将希罗求平方根的方法应用在整数算术上）能够给出n的近似平方根：

记n的位数为d。
如果d是奇数，则令x<sub>0</sub> = 2×10<sup>(d-1)⁄2</sup>。
如果d是偶数，则令x<sub>0</sub> = 7×10<sup>(d-2)⁄2</sup>。
依此类推：

<center><img src="https://projecteuler.net/project/images/p255_Heron.gif"></center>

直到x<sub>k+1</sub> = x<sub>k</sub>。

举例来说，我们来寻找n = 4321的近似平方根。
n是4位数，因此x<sub>0</sub> = 7×10<sup>(4-2)⁄2</sup> = 70。

<center><img src="https://projecteuler.net/project/images/p255_Example.gif"></center>

因为x<sub>2</sub> = x<sub>1</sub>，就不用再继续下去了。
所以，仅仅经过两次迭代，我们就得到了4321的近似平方根为66（实际平方根为65.7343137…）。

这个方法所需的迭代次数少得令人惊讶。
例如，对于所有的5位数（10,000 ≤ n ≤ 99,999），我们平均只需要3.2102888889次（四舍五入至10位小数）迭代就能找到其近似平方根。

使用上面描述的方法，对于所有的14位数（10<sup>13</sup> ≤ n &lt; 10<sup>14</sup>），我们平均需要多少次迭代能够找到其近似平方根？
将你的答案四舍五入到10位小数。

注意：符号⌊x⌋和⌈x⌉分别表示<dfn title="不大于x的最大整数">下取整函数</dfn>和<dfn title="不小于x的最小整数">上取整函数</dfn>。

---

## 输入格式

输入 d。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
