# Problem 906（PE 906）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=906](https://projecteuler.net/problem=906)。

## **A Collective Decision**

Three friends attempt to collectively choose one of $n$ options, labeled $1,\dots,n$, based upon their individual preferences. They choose option $i$ if for every alternative option $j$ at least two of the three friends prefer $i$ over $j$. If no such option $i$ exists they fail to reach an agreement.

Define $P(n)$ to be the probability the three friends successfully reach an agreement and choose one option, where each of the friends' individual order of preference is given by a (possibly different) random permutation of $1,\dots,n$.

You are given $P(3)=17/18$ and $P(10)\approx0.6760292265$.

Find $P(20\ 000)$. Give your answer rounded to ten places after the decimal point.

## **集体决定**

三位朋友试图根据他们各自的偏好集体从$n$个选项中选择其中之一，这些选项分别用$1,\dots,n$表示。如果存在选项$i$使得，对于任意其他选项$j$，至少有两位朋友更喜欢选项$i$胜过选项$j$，那么他们就会选择选项$i$。如果不存在这样的选项$i$，他们就无法达成一致。

定义$P(n)$为三位朋友成功达成一致的概率，其中每位朋友的个人偏好可以由$1,\dots,n$的一个（可能不同的）随机排列表示。

已知$P(3)=17/18$，$P(10)\approx0.6760292265$。

求$P(20\ 000)$，并四舍五入保留十位小数作为你的答案。

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
