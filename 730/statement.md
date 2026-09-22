# Problem 730（PE 730）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=730](https://projecteuler.net/problem=730)。

## **Shifted Pythagorean Triples**

For a non-negative integer $k$, the triple $(p,q,r)$ of positive integers is called a <i>$k$-shifted Pythagorean triple</i> if $$p^2 + q^2 + k = r^2$$

$(p, q, r)$ is said to be primitive if $\gcd(p, q, r)=1$.

Let $P_k(n)$ be the number of primitive k-shifted Pythagorean triples such that $1 \le p \le q \le r$ and $p + q + r \le n$. 
For example, $P_0(10^4) = 703$ and $P_{20}(10^4) = 1979$. 

Define 
$$\displaystyle S(m,n)=\sum_{k=0}^{m}P_k(n)$$
You are given that $S(10,10^4) = 10956$. 

Find $S(10^2,10^8)$.

## **移位勾股数**

对于非负整数$k$，若正整数三元组$(p,q,r)$满足
$$p^2 + q^2 + k = r^2$$
则称之为<i class=zh>$k$-移位勾股数</i>。若进一步地$(p, q, r)$满足$\gcd(p, q, r)=1$，则称为$k$-移位本原勾股数。

记$P_k(n)$为满足$1 \le p \le q \le r$和$p + q + r \le n$的$k$-移位本原勾股数的数目。
例如，$P_0(10^4) = 703$，$P_{20}(10^4) = 1979$。

记 
$$\displaystyle S(m,n)=\sum_{k=0}^{m}P_k(n)$$
已知$S(10,10^4) = 10956$。

求$S(10^2,10^8)$。

---

## 输入格式

一行：

- 字符 `PE`：输出原题（m = 100, n = 10^8）的官方答案；
- 或两个整数 m, n（0 ≤ m ≤ 100，1 ≤ n ≤ 10^5）：输出 S(m,n)。

## 输出格式

一个整数。

## 样例

### 输入

```
10 10000
```

### 输出

```
10956
```

---

## 数据范围

- 0 ≤ m ≤ 100，1 ≤ n ≤ 10^5
- 检查值: S(10,10^4) = 10956、P_0(10^4) = S(0,10^4) = 703、P_20(10^4) = 1979（原题给定）
- PE 答案: S(100,10^8) = 1315965924（原题规模超出改编范围, PE 分支输出官方值;
  改编范围内算法为 (a,e,w) 参数化 + Möbius 反演, 原题三锚点全部落在范围内并精确命中）

