# Problem 934（PE 934）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=934](https://projecteuler.net/problem=934)。

## **Unlucky Primes**

We define the *unlucky prime* of a number $n$, denoted $u(n)$, as the smallest prime number $p$ such that the remainder of $n$ divided by $p$ (i.e. $n \bmod p$) is not a multiple of seven.<br/>
For example, $u(14) = 3$, $u(147) = 2$ and $u(1470) = 13$.

Let $U(N)$ be the sum $\sum_{n = 1}^N u(n)$.<br/>
You are given $U(1470) = 4293$.

Find $U(10^{17})$.

## **不幸素数**

定义数$n$对应的<i class=zh>不幸素数</i>$u(n)$为最小的、使得$n$除以$p$的余数（即$n \bmod p$）不是$7$的倍数的素数$p$。<br/>
例如，$u(14) = 3$，$u(147) = 2$，$u(1470) = 13$。

记$U(N)$为求和$\sum_{n = 1}^N u(n)$。<br/>
已知$U(1470) = 4293$。

求$U(10^{17})$。

---

## 输入格式

一行：

- 字符 `PE`：输出原题（N = 10^17）的官方答案；
- 或一个整数 N（1 ≤ N ≤ 10^7）：输出 U(N)。

## 输出格式

一个整数。

## 样例

### 输入

```
1470
```

### 输出

```
4293
```

---

## 数据范围

- 1 ≤ N ≤ 10^7（参数化分支为直接模拟）
- 检查值: N = 1470 → 4293（原题给定）
- PE 答案: N = 10^17 → 292137809490441370（全规模计数算法未实现, PE 分支直接输出）

