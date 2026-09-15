# 超幂运算

## 题目描述

超幂运算（tetration）$a \uparrow\uparrow b$ 定义如下：
- $a \uparrow\uparrow 1 = a$
- $a \uparrow\uparrow (k+1) = a^{(a \uparrow\uparrow k)}$

即 $a \uparrow\uparrow b$ 是一个有 $b$ 层 $a$ 的幂塔：$a^{a^{a^{\cdots^a}}}$。

给定 $A$ 和 $B$，求 $A \uparrow\uparrow B \bmod 10^8$ 的值。输出 $8$ 位数字（不足 $8$ 位在前面补 $0$）。

---

## 输入格式

一行，两个整数 $A$ 和 $B$，用一个空格分隔。

---

## 输出格式

一行，一个 $8$ 位数字（含前导零），表示 $A \uparrow\uparrow B \bmod 10^8$。

---

## 样例

### 输入
```
1777 1855
```

### 输出
```
95962097
```

---

## 数据范围

- $2 \le A \le 2000$
- $2 \le B \le 2000$
