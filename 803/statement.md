# Problem 803（PE 803）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=803](https://projecteuler.net/problem=803)。

## **Pseudorandom sequence**

<b>Rand48</b> is a pseudorandom number generator used by some programming languages. It generates a sequence from any given integer $0 \le a_0 < 2^{48}$ using the rule $a_n = (25214903917 \cdot a_{n - 1} + 11) \bmod 2^{48}$.

Let $b_n = \lfloor a_n / 2^{16} \rfloor \bmod 52$. The sequence $b_0, b_1, \dots$ is translated to an infinite string $c = c_0c_1\dots$ via the rule:<br />
$0 \rightarrow$ a, $1\rightarrow$ b, $\dots$, $25 \rightarrow$ z, $26 \rightarrow$ A, $27 \rightarrow$ B, $\dots$, $51 \rightarrow$ Z.

For example, if we choose $a_0 = 123456$, then the string $c$ starts with: "bQYicNGCY$\dots$".<br />
Moreover, starting from index $100$, we encounter the substring "RxqLBfWzv" for the first time.

Alternatively, if $c$ starts with "EULERcats$\dots$", then $a_0$ must be $78580612777175$.

Now suppose that the string $c$ starts with "PuzzleOne$\dots$".<br />
Find the starting index of the first occurrence of the substring "LuckyText" in $c$.

## **伪随机序列**

许多编程语言都使用<b>Rand48</b>这种伪随机数生成器。对于任意给定整数$0 \le a_0 < 2^{48}$，它会按照规则$a_n = (25214903917 \cdot a_{n - 1} + 11) \bmod 2^{48}$生成一组伪随机序列。

记$b_n = \lfloor a_n / 2^{16} \rfloor \bmod 52$。序列$b_0, b_1, \dots$会进一步按照以下规则翻译为无限长字符串$c = c_0c_1\dots$：<br />
$0 \rightarrow$ a，$1\rightarrow$ b，$\dots$，$25 \rightarrow$ z，$26 \rightarrow$ A，$27 \rightarrow$ B，$\dots$，$51 \rightarrow$ Z。

例如，如果我们选择$a_0 = 123456$，那么字符串$c$的开头部分为："bQYicNGCY$\dots$"。<br />
进一步地，在字符串下标为$100$的位置，我们第一次得到子串"RxqLBfWzv"。

另一方面，如果我们希望字符串$c$的开头部分为"EULERcats$\dots$"，那么$a_0$必须选定为$78580612777175$。

现在假设字符串$c$的开头部分为"PuzzleOne$\dots$"。<br />
求我们第一次在字符串$c$中得到子串"LuckyText"的起始位置下标。

---

## 输入格式

（待人工补充：请对照 code/std.cpp 的读取约定描述。）

## 输出格式

（待人工补充。）

## 样例

（无 data 数据，待人工补充。）

---

## 数据范围

（待人工补充；原题参数范围见上方原题描述。）

