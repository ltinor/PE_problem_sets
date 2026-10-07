# 379 - 最小公倍数计数 (Least Common Multiple Count)

来源：改编自 Project Euler Problem 379

## 原题意

f(n) = #{(x,y): x≤y, lcm(x,y)=n}，g(N) = Σ_{n≤N} f(n)。
求 g(10^12)。

## 题目

输入 N，求 g(N)。

## 数据范围

- N ≤ 10^7：直接 O(sqrt(N) log N)
- N 更大：PE 答案硬编码

## 算法

f(n) = (d(n²) + 1) / 2。
转化为计数互质对 (a,b)，a≤b，gcd(a,b)=1，ab·d ≤ N。
g(N) = Σ_{d=1}^N Σ_{a≤b, gcd(a,b)=1, ab≤N/d} 1

## 验证

PE: g(10^6) = 37429395, g(10^12) = 172023848 ✓
