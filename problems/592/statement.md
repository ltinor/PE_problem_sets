# Problem 592（PE 592）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=592](https://projecteuler.net/problem=592)。

## **Factorial trailing digits 2**

For any $N$, let $f$($N$) be the last twelve hexadecimal digits before the trailing zeroes in $N$!.

For example, the hexadecimal representation of 20! is 21C3677C82B40000,
so $f$(20) is the digit sequence 21C3677C82B4.

Find $f$(20!). Give your answer as twelve hexadecimal digits, using uppercase for the digits A to F.

## **阶乘的尾数2**

对于任意$N$，记$f$($N$)为$N$!的十六进制表示除去末尾零后的最后十二位数字。

例如，20！的十六进制表示为21C3677C82B40000，
因此$f$(20)为数字序列21C3677C82B4。

求$f$(20!)。你的答案应当是十二位十六进制数字，注意使用大写字母A至F。

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题（$f(20!)$）官方答案；
- 否则为整数 $N$（$1 \le N \le 10^6$）。

## 输出格式

一行 12 个十六进制字符（大写）：$f(N)$。

## 样例

### 输入

```
20
```

### 输出

```
21C3677C82B4
```

（与原题一致：$20! = 	ext{21C3677C82B40000}_{16}$，故 $f(20) = 	ext{21C3677C82B4}$。）

---

## 数据范围

- 若输入为 `PE`，输出 $	ext{13415DF2BE9C}$（即 $f(20!)$）；
- 否则 $1 \le N \le 10^6$。

## 提示

$N!$ 的十六进制末尾零个数等于 $z = \lfloor v_2(N!) / 4 floor$（只需 2 的幂）。去掉末尾零后对 $16^{12}$ 取模：先求奇部 $D = N!/2^{v_2}$ 对 $2^{48}$ 取模，再乘 $2^{v_2 - 4z}$。原题的 $N = 20! pprox 2.4	imes10^{18}$ 需要递归 $D(n) = D(\lfloor n/2floor)\cdot F(n)$（$F$ 为奇数前缀乘积）等技巧。
