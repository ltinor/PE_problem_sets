# 平方和

## 题目描述

对于正整数 $n$，定义 $g(n)$ 为能**整除 $n$ 的最大完全平方数**。

例如：
- $18 = 2 \times 3^2$，最大完全平方因子是 $3^2 = 9$，故 $g(18) = 9$
- $19$ 是素数，完全平方因子只有 $1$，故 $g(19) = 1$

定义前缀和：
$$S(N) = \sum_{n=1}^N g(n)$$

例如：
- $S(10) = 1 + 1 + 1 + 4 + 1 + 1 + 1 + 4 + 9 + 1 = 24$
- $S(100) = 767$

## 输入格式

一行字符串：`PE`、`verify` 或 `compute`。

## 输出格式

- `PE`：输出原题答案 `94586478`
- `verify`：展示小规模暴力验证（$S(10), S(100)$）及公式推导
- `compute`：输出最终答案

## 样例

### 输入
```
PE
```

### 输出
```
94586478
```

### 小规模验证
| N | S(N) |
|---|------|
| 10 | 24 |
| 100 | 767 |

### 公式推导

将 $n$ 分解为 $n = a^2 \cdot b$（$b$ 无平方因子），则 $g(n) = a^2$：

$$S(N) = \sum_{a=1}^{\lfloor\sqrt{N}\rfloor} a^2 \cdot Q\left(\left\lfloor\frac{N}{a^2}\right\rfloor\right)$$

其中 $Q(m)$ 为无平方因子数的计数函数：
$$Q(m) = \sum_{d=1}^{\lfloor\sqrt{m}\rfloor} \mu(d) \left\lfloor\frac{m}{d^2}\right\rfloor$$

通过变量代换 $t = ad$，得到：
$$S(N) = \sum_{t=1}^{\lfloor\sqrt{N}\rfloor} \left\lfloor\frac{N}{t^2}\right\rfloor \cdot J_2(t)$$

$J_2(t) = t^2 \prod_{p\mid t} \left(1 - \frac{1}{p^2}\right)$ 是 Jordan 二重 totient 函数，可用线性筛在 $O(\sqrt{N})$ 时间内预处理。

## 数据范围

- 验证范围：$N \le 100$（暴力验证）
- 完整问题：$N = 10^{14}$
- $\sqrt{N} = 10^7$，可用线性筛预处理
- 答案模数：$1\ 000\ 000\ 007$
