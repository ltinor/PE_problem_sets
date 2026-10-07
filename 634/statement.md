# Problem 634（PE 634）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=634](https://projecteuler.net/problem=634)。

## **Numbers of the form $a^2b^3$**

Define $F(n)$ to be the number of integers $x\le n$ that can be written in the form $x=a^2b^3$, where $a$ and $b$ are integers not necessarily different and both greater than $1$.

For example, $32=2^2\times 2^3$ and $72=3^2\times 2^3$ are the only two integers less than $100$ that can be written in this form. Hence, $F(100)=2$.

Further you are given $F(2\times 10^4)=130$ and $F(3\times 10^6)=2014$.

Find $F(9\times 10^{18})$.

## **可写成$a^2b^3$的数**

考虑整数$x\le n$，若$x$可写成$x=a^2b^3$，其中$a$和$b$是大于$1$且可重复的整数，记所有此类整数的数目为$F(n)$。

例如，在小于$100$的整数中，只有$32=2^2\times 2^3$和$72=3^2\times 2^3$可以写成这种形式，因此$F(100)=2$。

此外，还已知$F(2\times 10^4)=130$以及$F(3\times 10^6)=2014$。

求$F(9\times 10^{18})$。

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题（$N = 9	imes10^{18}$）官方答案；
- 否则为整数 $N$（$8 \le N \le 9	imes10^{18}$）。

## 输出格式

一行一个整数：能表示为 $a^2 b^3$（$a, b \ge 2$）的不同整数 $x \le N$ 的个数。

## 样例

### 输入

```
1000
```

### 输出

```
19
```

---

## 数据范围

- 若输入为 `PE`，输出 $4019680944$；
- 否则 $8 \le N \le 9	imes10^{18}$。

## 提示

每个“强数”都有唯一的表示 $x = c^2 d^3$（$d$ 为无平方因子数）。先对无平方因子的 $b \ge 2$ 统计 $a \ge 2$ 的贡献，再补上可表示的完全平方数（用默比乌斯函数统计非无立方因子数）。
