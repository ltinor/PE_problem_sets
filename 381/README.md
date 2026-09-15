# 381 - (素数-k)阶乘 ((prime-k) factorial)

来源：Project Euler Problem 381

## 原题意
S(p) = Σ_{k=1..5} (p-k)! mod p
求 Σ S(p)，5 ≤ p < 10^8。

## 题目
输入 L, R，求 Σ_{p∈[L,R), p prime} S(p)。

## 算法
Wilson定理：(p-1)! ≡ -1 (mod p)
递推：(p-2)! ≡ 1，(p-3)! ≡ inv(p-2) ≡ inv(-2)，以此类推。
对每个素数 O(log p) 计算 S(p)。

## 验证
PE: Σ S(p), 5≤p<100 = 480 ✓
PE: Σ S(p), 5≤p<10^8 = 139602943319822 ✓
