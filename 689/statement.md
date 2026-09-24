# Problem 689（PE 689）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=689](https://projecteuler.net/problem=689)。

## **Binary Series**

For $0 \le x \lt 1$, define $d_i(x)$ to be the $i$th digit after the binary point of the binary representation of $x$.
For example $d_2(0.25) = 1$, $d_i(0.25) = 0$ for $i \ne 2$.

Let $f(x) = \displaystyle{\sum_{i=1}^{\infty}\frac{d_i(x)}{i^2}}$.

Let $p(a)$ be probability that $f(x) \gt a$, given that $x$ is uniformly distributed between $0$ and $1$.

Find $p(0.5)$. Give your answer rounded to $8$ digits after the decimal point.

## **二进制级数**

对于任意$0 \le x \lt 1$，记$d_i(x)$为$x$的二进制表示中小数点后第$i$位数字。
例如，$d_2(0.25) = 1$，而对所有$i \ne 2$则有$d_i(0.25)=0$。

记$f(x) = \displaystyle{\sum_{i=1}^{\infty}\frac{d_i(x)}{i^2}}$。

若$x$在$0$和$1$之间均匀分布，记$p(a)$为$f(x) \gt a$的概率。

求$p(0.5)$，并将你的答案保留小数点后$8$位数字。

---

## 输入格式

一行：

- 字符 `PE`：输出原题（D→∞ 极限）的官方答案；
- 或两个整数 D, a 的十进制（2 ≤ D ≤ 42，0 ≤ a ≤ 2）：输出截断级数精确概率。

## 输出格式

一个 12 位小数（精确值四舍五入）。

## 样例

### 输入

```
42 0.5
```

### 输出

```
0.553555999451
```

---

## 数据范围

- 2 ≤ D ≤ 42，0 ≤ a ≤ 2
- 检查值: p_42(0.5) = 0.553555999451
- PE 答案（原题 D→∞ 极限）: 0.56565454（p_D(0.5) 随 D 增大收敛于它）

---

## 数据范围

（待人工补充；原题参数范围见上方原题描述。）

