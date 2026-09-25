# Problem 851（PE 851）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=851](https://projecteuler.net/problem=851)。

## **SOP and POS**

Let $n$ be a positive integer and let $E_n$ be the set of $n$-tuples of strictly positive integers.

For $u = (u_1, \cdots, u_n)$ and $v = (v_1, \cdots, v_n)$ two elements of $E_n$, we define:
- the <i>Sum Of Products</i> of $u$ and $v$, denoted by $\langle u, v\rangle$, as the sum $\displaystyle\sum_{i = 1}^n u_i v_i$;
- the <i>Product Of Sums</i> of $u$ and $v$, denoted by $u \star v$, as the product $\displaystyle\prod_{i = 1}^n (u_i + v_i)$.

Let $R_n(M)$ be the sum of $u \star v$ over all ordered pairs $(u, v)$ in $E_n$ such that $\langle u, v\rangle = M$.<br />
For example: $R_1(10) = 36$, $R_2(100) = 1873044$, $R_2(100!) \equiv 446575636 \bmod 10^9 + 7$.

Find $R_6(10000!)$. Give your answer modulo $10^9+7$.

## **积之和与和之积**

对于正整数$n$，记$E_n$为所有$n$元正整数组构成的集合。

对于$E_n$的任意两个元素$u = (u_1, \cdots, u_n)$和$v = (v_1, \cdots, v_n)$，定义：
- $u$和$v$的<i class=zh>积之和</i>，记作$\langle u, v\rangle$，为$\displaystyle\sum_{i = 1}^n u_i v_i$；
- $u$和$v$的<i class=zh>和之积</i>，记作$u \star v$，为$\displaystyle\prod_{i = 1}^n (u_i + v_i)$。

考虑所有$E_n$中满足$\langle u, v\rangle = M$的有序对$(u,v)$，并记其对应的$u \star v$之和为$R_n(M)$。<br />
例如，$R_1(10) = 36$，$R_2(100) = 1873044$，$R_2(100!) \equiv 446575636 \bmod 10^9 + 7$。

求$R_6(10000!)$，并将你的答案对$10^9+7$取余。

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
参考常量: PE_ANSWER = 169796973644LL
