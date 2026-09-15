# 945 异或方程（三）（简单版本）

来源：改编自 Project Euler Problem 945 (XOR-Equation C)

## 原题意

用 $x\otimes y$ 表示 $x$ 与 $y$ 的**异或积**：二进制长乘法，但中间结果相加改为按位异或。
它等价于 $\mathrm{GF}(2)[x]$ 上的多项式乘法（无进位乘法）。例如 $7\otimes 3 = 111_2\otimes 11_2 = 1001_2 = 9$。

求满足方程
$$(a\otimes a)\oplus(2\otimes a\otimes b)\oplus(b\otimes b)=c\otimes c$$
且 $0\le a\le b\le N$ 的解 $(a,b,c)$ 的数量 $F(N)$。已知 $F(10)=21$。原题求 $F(10^7)$。

## 题目（简单版本）

输入一个整数 $N$，输出 $F(N)$。

## 数据范围

- 简单版本：$0 \le N \le 5000$。

## 算法

在 $\mathrm{GF}(2)[x]$ 中，$a\otimes a=a(x)^2=a(x^2)$、$b\otimes b=b(x^2)$、$c\otimes c=c(x^2)$ 均只含偶次项；而 $2\otimes a\otimes b = x\cdot a(x)\cdot b(x)$（$2$ 只有第 $1$ 位为 $1$，故 $2\otimes a = a\ll 1$）。

等式化为
$$a(x^2)\oplus x\cdot a(x)\cdot b(x)\oplus b(x^2)=c(x^2).$$
奇次项上右端为 $0$，故要求 $x\cdot a\cdot b$ 的奇次项系数为 $0$，即 $a\otimes b$ 的**偶数位置比特全为 $0$**；此时 $c$ 由偶次项唯一确定。因此

$$F(N)=\#\{(a,b): 0\le a\le b\le N,\ (a\otimes b)\ \&\ 0\text{x}5555555555555555=0\}.$$

直接 $O(N^2)$ 枚举 $(a,b)$，用无进位乘法判定即可（$N\le 5000$ 时约 $1.25\times 10^7$ 对，秒出）。

验证：$F(10)=21$。
