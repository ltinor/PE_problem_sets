# Problem 633（PE 633）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=633](https://projecteuler.net/problem=633)。

## **Square prime factors II**

For an integer $n$, we define the <i>square prime factors</i> of $n$ to be the primes whose square divides $n$. For example, the square prime factors of $1500 = 2^2 \times 3 \times 5^3$ are $2$ and $5$.

Let $C_k(N)$ be the number of integers between $1$ and $N$ inclusive with exactly $k$ square prime factors.  It can be shown that with growing $N$ the ratio $\frac{C_k(N)}{N}$ gets arbitrarily close to a constant $c_k^\infty$, as suggested by the table below.

| |$k=0$|$k=1$|$k=2$|$k=3$|$k=4$|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$C_k(10)$|$7$|$3$|$0$| $0$ | $0$ |
|$C_k(10^2)$|$61$|$36$|$3$| $0$ | $0$ |
|$C_k(10^3)$|$608$|$343$|$48$| $1$ | $0$ |
|$C_k(10^4)$|$6083$|$3363$|$533$| $21$ | $0$ |
|$C_k(10^5)$|$60794$|$33562$|$5345$| $297$ | $2$ |
|$C_k(10^6)$|$607926$|$335438$|$53358$| $3218$ | $60$ |
|$C_k(10^7)$|$6079291$|$3353956$|$533140$| $32777$ | $834$ |
|$C_k(10^8)$|$60792694$|$33539196$|$5329747$| $329028$ | $9257$ |
|$C_k(10^9)$|$607927124$|$335389706$|$53294365$| $3291791$ | $95821$ |
|$c_k^\infty$| $\frac{6}{\pi^2}$| $3.3539\times 10^{-1}$| $5.3293\times 10^{-2}$ | $3.2921\times 10^{-3}$| $9.7046\times 10^{-5}|

Find $c_7^\infty$. Give the result in scientific notation rounded to $5$ significant digits, using a $e$ to seperate mantissa and exponent. E.g., if the answer were $0.000123456789$, then the answer format would be $1.2346e-4$.

## **平方质因数II**

对于整数$n$，称平方后能整除$n$的质数为$n$的<i class=zh>平方质因数</i>。例如，$1500 = 2^2 \times 3 \times 5^3$的平方质因数包括$2$和$5$。

记$C_k(N)$为$1$与$N$之间（含$1$和$N$）恰好有$k$个平方质因数的整数之和。可以发现，随着$N$不断增大，比值$\frac{C_k(N)}{N}$逐渐趋向于一个常数$c_k^\infty$，如下表所示：

| |$k=0$|$k=1$|$k=2$|$k=3$|$k=4$|$k=5$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$N=10$|$7$|$3$|$0$| $0$ | $0$ |$0$|
|$N=10^2$|$61$|$36$|$3$| $0$ | $0$ |$0$|
|$N=10^3$|$608$|$343$|$48$| $1$ | $0$ |$0$|
|$N=10^4$|$6083$|$3363$|$533$| $21$ | $0$ |$0$|
|$N=10^5$|$60794$|$33562$|$5345$| $297$ | $2$ |$0$|
|$N=10^6$|$607926$|$335438$|$53358$| $3218$ | $60$ |$0$|
|$N=10^7$|$6079291$|$3353956$|$533140$| $32777$ | $834$ |$2$|
|$N=10^8$|$60792694$|$33539196$|$5329747$| $329028$ | $9257$ |$78$|

求$c_7^\infty$，并将结果用科学计数法表示，保留5位有效数字，尾数和指数间用$e$分隔。例如，如果结果是$0.000123456789$，则应当回答$1.2346e-4$。

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题（$k=7$）官方答案；
- 否则为整数 $k$（$0 \le k \le 7$）。

## 输出格式

一行一个字符串：$c_k^\infty$，科学计数法保留 5 位有效数字，用 `e` 分隔尾数与指数（如 `1.2346e-4`）。

## 样例

### 输入

```
4
```

### 输出

```
9.7046e-5
```

（与原题表格一致：$c_1^\infty = 3.3539	imes10^{-1}$，$c_4^\infty = 9.7046	imes10^{-5}$。）

---

## 数据范围

- 若输入为 `PE`，输出 `1.0012e-10`；
- 否则 $0 \le k \le 7$。

## 提示

由欧拉乘积 $\prod_p \left(1 + rac{x-1}{p^2}ight) = \sum_k c_k^\infty x^k$，可得

$$c_k^\infty = rac{6}{\pi^2}\, e_k\left(\left\{rac{1}{p^2-1}ight\}_{p 	ext{ prime}}ight)$$

其中 $e_k$ 为初等对称多项式。由于 $1/(p^2-1)$ 衰减极快，对 $p \le 10^7$ 做 DP 即可精确到 5 位有效数字。
