# Problem 789（PE 789）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=789](https://projecteuler.net/problem=789)。

## **Minimal pairing modulo $p$**

Given an odd prime $p$, put the numbers $1, \ldots, p-1$ into $\frac{p-1}{2}$ pairs such that each number appears exactly once. Each pair $(a,b)$ has a cost of $ab \bmod p$. For example, if $p=5$ the pair $(3,4)$ has a cost of $12 \bmod 5 = 2$.

The <i>total cost</i> of a pairing is the sum of the costs of its pairs. We say that such pairing is optimal if its total cost is minimal for that $p$.

For example, if $p = 5$, then there is a unique optimal pairing: $(1, 2), (3, 4)$, with total cost of $2 + 2 = 4$.

The <i>cost product</i> of a pairing is the product of the costs of its pairs. For example, the cost product of the optimal pairing for $p = 5$ is $2 \cdot 2 = 4$.

It turns out that all optimal pairings for $p = 2\ 000\ 000\ 011$ have the same cost product.

Find the value of this product.

## **模$p$余数的最优配对**

对于给定的奇质数$p$，将整数$1, \ldots, p-1$分成$\frac{p-1}{2}$对并保证每个整数只出现一次。每一对$(a,b)$的成本为$ab \bmod p$。例如，若$p=5$，那么整数对$(3,4)$的成本为$12 \bmod 5 = 2$。

一组配对的<i class=zh>总成本</i>是其中每一整数对的成本之和。对于$p$，我们称总成本最小的配对为最优配对。

例如，若$p = 5$，存在唯一的最优配对$(1, 2), (3, 4)$，其总成本为$2 + 2 = 4$。

一组配对的<i class=zh>成本积</i>是其中每一整数对的成本的乘积。例如，上述$p=5$的最优配对的成本积是$2 \cdot 2 = 4$。

已知$p = 2\ 000\ 000\ 011$的所有最优配对都有相同的成本积。

求该成本积的值。

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
