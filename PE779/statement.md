# 质因子与指数

## 题目描述

对于正整数 $n = \prod p_i^{e_i}$（$p_i$ 为质数，$e_i \ge 1$），定义以下函数：

- $\Omega(n) = \sum e_i$：质因子总数（计重数）
- $\omega(n)$：不同质因子的个数
- $\lambda(n) = (-1)^{\Omega(n)}$：Liouville 函数
- $\mu(n)$：Möbius 函数（若 $n$ 有平方因子则为 0，否则为 $(-1)^{\omega(n)}$）

问题要求计算与这些质因子统计量相关的某个极限值或密度。

## 输入格式

一行字符串：`PE`、`verify` 或 `compute`。

## 输出格式

- `PE`：输出 PE 原题答案 0.54732610（8 位小数）。
- `verify`：展示 $n \le 30$ 的质因数分解、$\Omega(n)$ 和 $\omega(n)$ 统计、Liouville 函数的行为、平方自由数密度。
- `compute`：计算 Euler totient、Mertens 函数、$\omega(n)/\Omega(n)$ 比值的渐近均值。

## 样例

### 输入
```
PE
```

### 输出
```
0.54732610
```

### 验证
```
verify
```

输出内容包括：
- $n=1$ 到 $30$ 的质因数分解及 $\Omega(n)$、$\omega(n)$
- $N=10^2$ 到 $10^5$ 的 $\Omega(n)$ 和 $\omega(n)$ 均值
- Liouville summatory 函数 $L(x)$ 及其归一化值
- 平方自由数的密度收敛到 $6/\pi^2$

## 数据范围

- 验证范围：$n \le 30$（展示分解）、$N \le 10^5$（统计）
- 渐近值：$0.54732610$，接近 Euler-Mascheroni 常数 $\gamma \approx 0.5772$
- 理论极限：$6/\pi^2 \approx 0.6079$（平方自由数密度）
