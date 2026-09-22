# PE730 移位勾股数 分析笔记 (2026-09-22)

## 已验证: (a,e,w) 参数化 + needle 族 (g=1 层精确)

(p,q,r) = (a+w, a+e, a+w+e), w>=1, e>=w, a = p+q-r (可为负), k = 2ew - a^2.
gcd(p,q,r) = g  <=>  g | a,e,w. 周长 = 3a + 2w + 2e.

- 主族 (a>=0) + needle 族 (a=-c<0, c<=w-1 且 c<=sqrt(m)): count_all(m,n)
  与暴力在 n=200/1000 (m=10) 全元组一致 (工具: _work/t730_param.cpp, t730_dbg.cpp).
- a 的周长上界: 判别式 => a <= n*(3-2sqrt2)/2 ≈ 0.0858n; needle 族 c <= sqrt(m).

## 关键发现: k=0 子族使 Mobius 求和延伸到无穷

S(m,n) = sum_{g>=1} mu(g) * count_all(floor(m/g^2), floor(n/g)),
求和直到 floor(n/g) < 4 —— 因为 k=0 (即 2ew=a^2, 勾股族) 满足 g^2*0 <= m 对一切 g,
g > sqrt(m) 的 mu(g) 项并不为零 (曾因此 +37 偏差 @ n=1000).
g > sqrt(m) 部分: m'' = 0, count_all(0, n/g) = 勾股三元组计数 ~ c*n/g,
可用 mu 筛在 O(n/4) 累计 (n=1e8 -> 2.5e7 项).

## 剩余障碍: C(1) = count_all(100, 1e8) 的主项枚举

(a,w) 对数 ~ 0.354*(0.0858n)^2 ≈ 2.6e13, 直接扫不可行.
方案 (下轮实现): 对 r = 2..5e7, k = 0..100 对 N = r^2 - k 做带状因子分解筛
(位置即 r mod p 的 Tonelli 平方根; 完全分解后枚举 x^2+y^2=N 表示:
r2 公式过滤 3mod4 素数奇次幂, Gaussian 乘法生成表示),
每个表示检查 p<=q, p+q+r<=1e8, gcd=1 后累加 p+q+r.
预计离线 3-5 分钟. std 的 PE 分支暂保留官方值, 参数化分支已可用
count_all/Mobius 支撑 n <= 1e6 (约 10s) —— 注意 m=0 时 Mobius 特殊处理.
