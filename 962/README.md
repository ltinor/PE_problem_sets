# PE962 - 角平分线与切线（二）

来源：改编自 Project Euler Problem 962（Angular Bisector and Tangent 2）

## 原题意

给定整数边长三角形 $ABC$，$BC \le AC \le AB$。$k$ 是 $\angle ACB$ 的角平分线，$m$ 是外接圆在 $C$ 点的切线，$n$ 是过 $B$ 平行于 $m$ 的直线，$E = n \cap k$。

求周长不超过 $1\,000\,000$ 且 $CE$ 为整数的三角形个数。

（本题是 Project Euler 296 的更难版本。）

## 题目

给定整数 $N$，求周长不超过 $N$ 且 $CE$ 为整数的三角形 $ABC$ 的个数。

## 数据范围

$1 \le N \le 1000$（原题 $N = 10^6$，此处为缩数据版）。

## 算法

- 枚举所有满足 $a \le b \le c$、$a+b>c$、$a+b+c \le N$ 的三角形（$O(N^3)$）。
- 几何推导（以 $C$ 为原点、角平分线为 $x$ 轴，令 $\angle ACB=\gamma$）：
  - $A=(b\cos\frac\gamma2,-b\sin\frac\gamma2)$，$B=(a\cos\frac\gamma2,a\sin\frac\gamma2)$；
  - 外接圆 $x^2+y^2+ux+vy=0$，解得 $u=-\frac{a+b}{2\cos\frac\gamma2}$，$v=-\frac{a-b}{2\sin\frac\gamma2}$；
  - 切线 $ux+vy=0$，过 $B$ 的平行线与角平分线交于 $E$，得 $CE=\frac{2a^2\cos(\gamma/2)}{a+b}$。
  - 由 $\cos^2\frac\gamma2=\frac{(a+b)^2-c^2}{4ab}$ 得
    $$CE^2=\frac{a^3(a+b-c)(a+b+c)}{b(a+b)^2}.$$
- $CE$ 为整数 $\iff$ 上式约分后分母为 $1$ 且分子为完全平方数。

## 验证

- `std`（64 位精确实现）与 `brute`（`__int128` 独立实现）在 $N\le1000$ 全量一致；
- 公式已用直接坐标几何（长 double）在 $N\le200$ 全量比对，$0$ 处不一致。

## 小规模验证点

| $N$ | 答案 |
|----|----|
| 3  | 0 |
| 10 | 0 |
| 20 | 2 |
| 50 | 8 |
| 100 | 26 |
| 200 | 71 |
| 500 | 282 |
| 1000 | 763 |

## 改编方向

原题 $N=10^6$ 需要数论参数化（把 $CE^2$ 为完全平方数转化为丢番图条件并筛法计数），无法用 $O(N^3)$ 枚举；本缩数据版用 $O(N^3)$ 枚举 + 精确判定，面向小规模 OJ。
