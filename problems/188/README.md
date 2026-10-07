# 188 — 超幂运算

来源：改编自 Project Euler Problem 188

## 原题意

超幂运算（tetration）$a \uparrow\uparrow b$ 定义如下：
- $a \uparrow\uparrow 1 = a$
- $a \uparrow\uparrow (k+1) = a^{(a \uparrow\uparrow k)}$

求 $1777 \uparrow\uparrow 1855$ 的最后 $8$ 位数字。

答案：95962097

## 题目

参数化版本：输入 $A$ 和 $B$（$A, B \le 2000$），求 $A \uparrow\uparrow B \bmod 10^8$ 的值，输出 $8$ 位数字（含前导零）。

## 数据范围

- $2 \le A, B \le 2000$

## 算法

利用欧拉定理：$a^b \bmod m = a^{b \bmod \varphi(m) + \varphi(m)} \bmod m$（当 $b \ge \varphi(m)$ 时）。递归计算 $A \uparrow\uparrow B \bmod 10^8$，每次递归模数 $\varphi(m)$ 递减，最终收敛到 $1$。
