# PE774 — Conjunctive sequences（合取序列）

来源：改编自 Project Euler Problem 774

## 原题意

"合取序列"（conjunctive sequences）是将前几项的数字拼接（concatenate）在一起形成新项的序列。最常见的定义是：
$$a_n = \text{concat}(a_{n-2},\; a_{n-1}) \quad (n \ge 2)$$
即第 $n$ 项由第 $n-2$ 项和第 $n-1$ 项的数字串拼接而成。

例如以 $(1, 2)$ 为种子：
$$1, 2, 12, 212, 12212, 21212212, \dots$$
这类似于斐波那契词（Fibonacci word）的数字版本。

问题可能要求计算第 $N$ 项在某个模数下的值，或序列中数字的出现次数。

PE 答案：1064883765（约 $1.06 \times 10^9$）。

## 算法

1. **模运算拼接**：$\text{concat}(a,b) \bmod M = (a \cdot 10^{\text{len}(b)} + b) \bmod M$，其中 len(b) 为 b 的数字位数。
2. **长度递推**：$\text{len}(a_n) = \text{len}(a_{n-2}) + \text{len}(a_{n-1})$，满足斐波那契递推。
3. **快速幂**：使用快速幂计算 $10^{\text{len}(b)} \bmod M$。
4. **位运算版本**：也探索 bitwise AND 合取序列（$a_n = a_{n-1} \mathbin{\&} a_{n-2}$）。
5. **大数处理**：数字长度很快超越可用内存，必须仅保留模值。

## 改编方向

1. 不同种子对的拼接序列比较
2. $a_n = \text{concat}(a_{n-1}, a_{n-2})$ 的反向拼接
3. 推广到 $k$ 项拼接（$k$-nacci 词）
4. 多进制拼接（二进制、十六进制）
5. 统计特定数字模式在序列中的出现频率
