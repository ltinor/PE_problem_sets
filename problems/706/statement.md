# Problem 706（PE 706）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=706](https://projecteuler.net/problem=706)。

## **$3$-Like Numbers**

For a positive integer $n$, define $f(n)$ to be the number of non-empty substrings of $n$ that are divisible by $3$. For example, the string "$2573$" has $10$ non-empty substrings, three of which represent numbers that are divisible by $3$, namely $57$, $573$ and $3$. So $f(2573) = 3$.

If $f(n)$ is divisible by $3$ then we say that $n$ is <i>$3$-like</i>.

Define $F(d)$ to be how many $d$ digit numbers are $3$-like. For example, $F(2) = 30$ and $F(6) = 290898$.

Find $F(10^5)$. Give your answer modulo $1\ 000\ 000\ 007$.

## **$3$似数**

将正整数$n$视为数字串，记$f(n)$为能被$3$整除的$n$的非空子串数目。例如，数字串"$2573$"有$10$个非空子串，其中有三个能被$3$整除，分别是$57$、$573$和$3$，因此$f(2573) = 3$。

如果$f(n)$能被$3$整除，则称$n$为<i class=zh>$3$似数</i>。

记$F(d)$为$d$位数中$3$似数的个数。例如，$F(2) = 30$，$F(6) = 290898$。

求$F(10^5)$并将你的答案对$1\ 000\ 000\ 007$取余。

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题（$d = 10^5$）官方答案；
- 否则为整数 $d$（$1 \le d \le 10^5$），表示位数。

## 输出格式

一行一个整数：$F(d)$ 对 $1\,000\,000\,007$ 取余。

## 样例

### 输入

```
6
```

### 输出

```
290898
```

---

## 数据范围

- 若输入为 `PE`，输出 $884837055$（即 $F(10^5)$）；
- 否则 $1 \le d \le 10^5$。

## 提示

数位 DP：状态记录（当前前缀数位和模 3，以及三类前缀（数位和模 3 为 0/1/2）的个数模 3）。$f(n) mod 3$ 只依赖这三个计数值模 3 的情况。
