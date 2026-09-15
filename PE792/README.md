# PE792 — Too Many Twos（太多2）

来源：改编自 Project Euler Problem 792

## 原题意

问题涉及因数分解中 2 的幂次。$v_2(n)$ 表示 $n$ 中因子 2 的个数（2-adic valuation）。问题可能要求统计 $v_2(n) \ge k$ 的数个数、求和 $\sum v_2(n)$、或讨论阶乘的 2-adic valuation $v_2(n!) = n - s_2(n)$，其中 $s_2(n)$ 为 $n$ 的二进制表示中 1 的个数。

PE 答案：475019340（约 $4.75 \times 10^8$）。

## 算法

1. **$v_2(n)$ 计算**：反复除以 2 直到 $n$ 为奇数。
2. **Legendre 公式**：$v_2(n!) = \sum_{k=1}^\infty \lfloor n/2^k \rfloor = n - s_2(n)$。
3. **二进制位和**：$s_2(n) = \text{popcount}(n)$，与组合数 $C(2n,n)$ 的 $v_2$ 直接关联：$v_2(C(2n,n)) = s_2(n)$。
4. **区间统计**：$[1,N]$ 中 $v_2(n) \ge k$ 的个数为 $\lfloor N/2^k \rfloor$。

## 改编方向

1. 推广到多个素数（如同时考虑 $v_2$ 和 $v_3$）
2. 求 $\sum n \cdot v_2(n)$ 或更复杂的加权和
3. 限制在满足 $v_2(n) = v_3(n)$ 的数上
4. 求 $\prod_{v_2(n)=k} n$ 或类似乘积问题
5. 与二项式系数的奇偶性（Lucas 定理）关联
