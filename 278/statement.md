# 半素数线性组合（PE 278）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=278](https://projecteuler.net/problem=278)。

给定整数1 &lt; a<sub>1</sub> &lt; a<sub>2</sub> &lt;... &lt; a<sub>n</sub>，考虑其线性组合q<sub>1</sub>a<sub>1</sub> + q<sub>2</sub>a<sub>2</sub> + ... + q<sub>n</sub>a<sub>n</sub> = b，其中q<sub>k</sub> ≥ 0均为整数。 

注意到，对于特定集合a<sub>k</sub>，不是所有的b值都能取到。
例如，如果a<sub>1</sub> = 5且a<sub>2</sub> = 7，不存在q<sub>1</sub> ≥ 0和q<sub>2</sub> ≥ 0使得b取1、2、3、4、6、8、9、11、13、16、18或23。
事实上，当a<sub>1</sub> = 5且a<sub>2</sub> = 7时，不能取得的b值最大为23。
我们因此记f(5, 7) = 23。
类似地可以得出f(6, 10, 15)=29以及f(14, 22, 77) = 195。

对于所有素数p &lt; q &lt; r &lt; 5000，求∑ f(p\*q,p\*r,q\*r)。

---

## 输入格式

输入 B。

## 输出格式

计算结果。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
