# Problem 655（PE 655）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=655](https://projecteuler.net/problem=655)。

## **Divisible Palindromes**

The numbers $545$, $5\ 995$ and $15\ 151$ are the three smallest **palindromes** divisible by $109$. There are nine palindromes less than $100\ 000$ which are divisible by $109$.

How many palindromes less than $10^{32}$ are divisible by $10\ 000\ 019$?

## **可除尽的回文数**

$545$，$5\ 995$和$15\ 151$是最小的三个能被$109$除尽的**回文数**。在所有小于$100\ 000$的回文数中，有九个能够被$109$除尽。

在所有小于$10^{32}$的回文数中，有多少个能够被$10\ 000\ 019$整除？

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题（$M = 10\,000\,019$，$L = 32$）官方答案；
- 否则为两个整数 $M$ 和 $L$（$1 \le M \le 10^7$，$1 \le L \le 13$）。

## 输出格式

一行一个整数：小于 $10^L$ 且能被 $M$ 整除的回文数个数。

## 样例

### 输入

```
109 5
```

### 输出

```
9
```

（与原题一致：小于 $100\,000$ 且能被 $109$ 整除的回文数有 9 个，最小三个为 $545, 5995, 15151$。）

---

## 数据范围

- 若输入为 `PE`，输出 $2000008332$；
- 否则 $1 \le M \le 10^7$，$1 \le L \le 13$。

## 提示

按长度 $l$ 枚举回文数的前半部分（$\lceil l/2 ceil$ 位）并检查整除即可；原题 $L = 32$ 规模下需按各位系数 $c_i = 10^{L-i} + 10^{i-1} \pmod M$ 做 meet-in-the-middle。
