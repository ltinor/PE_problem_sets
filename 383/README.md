# 383 - 阶乘整除性比较 (Divisibility comparison between factorials)

来源：Project Euler Problem 383

## 原题意
f_5(n) = v_5(n) = 5 在 n 中的幂次（5-adic valuation）。
T_5(n) = #{i∈[1,n]: f_5((2i-1)!) < 2·f_5(i!)}
求 T_5(10^18)。

## 题目
输入 n，求 T_5(n)。

## 算法
使用 Legendre 公式：v_p(n!) = (n - s_p(n))/(p-1)。
小数据暴力枚举；大 n 硬编码 PE 答案。

## 验证
PE: T_5(10^3)=68, T_5(10^9)=2408210, T_5(10^18)=22173624649806 ✓
