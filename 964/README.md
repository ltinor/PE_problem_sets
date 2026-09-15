# 964 变种音乐椅游戏

来源：改编自 Project Euler Problem 964（Musical Chairs Revisited）

## 原题意

一群 $k(k-1)/2+1$ 个孩子玩 $k$ 轮游戏。第 $i$ 轮随机选出 $i$ 个孩子（组合等概率），
他们站起跳舞后随机坐回空出的 $i$ 把椅子（排列等概率）。记 $P(k)$ 为最终每个孩子恰好
坐到初始位置顺时针下一把椅子的概率。已知 $P(3) \approx 1.3888888889\times10^{-2}$，
求 $P(7)$（科学计数法，10 位有效数字）。

## 题目

给定整数 $k$（$1\le k\le 7$），输出 $P(k)$ 的科学计数法表示（10 位有效数字，小写 `e`）。
将原题的单一 $k=7$ 扩展为参数化输入，构成 OJ 缩数据版本。

## 数据范围

$1 \le k \le 7$，对应 $T = k(k-1)/2+1 \le 22$。

## 算法

问题可建模为对称群 $S_T$ 上的随机游走：每轮施加一个"随机 $i$-子集置换"，分布
$f_i$ 是 $S_T$ 上的类函数（中心元素）。最终置换为各轮置换的乘积，故

$$P(k) = (f_1 * f_2 * \cdots * f_k)(s),\qquad s = \text{全体 } T\text{-循环}.$$

利用类函数 Fourier 反演（特征标公式）：

$$P(k) = \frac{1}{T!}\sum_{\lambda\vdash T} d_\lambda\,\chi_\lambda(s)\prod_{i=1}^{k}\omega_i(\lambda),$$

其中 $\omega_i(\lambda)=\frac{1}{d_\lambda}\sum_g f_i(g)\chi_\lambda(g)$ 是 $f_i$ 在不可约表示
$\lambda$ 上的特征值。

由 Murnaghan–Nakayama 法则，$\chi_\lambda(s)$ 仅在 $\lambda$ 为钩子 $\lambda=(a,1^{T-a})$
时非零，此时 $\chi=(-1)^{T-a}$、$d=C(T-1,a-1)$。对钩子，$\omega_i=m_i/d$，其中 $m_i$
为钩子不可约表示限制到 $S_i$ 后平凡表示的重数，等于"从 $\lambda$ 删去一条含 $i$ 格的
水平条得到的 $\mu$ 的维数 $f^\mu$ 之和"。钩子情形有闭式：

- 若 $b=T-a\ge 1$：$m_i=f^{(a-i,1^b)}+f^{(a-i+1,1^{b-1})}$（对合法下标求和），$m_a=1$；
- 若 $b=0$（$\lambda=(a)$ 平凡表示）：$m_i=1$（$0\le i\le a$）；

其中 $f^{(c,1^r)}=C(c+r-1,r)$。最终

$$P(k)=\frac{\sum_a (-1)^b \prod_{i=1}^k m_i(a) \cdot r_a^{k-1}}{B^{k-1}\,T!},\quad
r_a=\frac{B}{C(T-1,a-1)},\; B=\frac{\mathrm{lcm}(1..T)}{T}.$$

$B$ 恰为帕斯卡三角第 $T-1$ 行二项式系数的 lcm（故 $r_a$ 为整数）。求和用大整数精确
累加以避免消位误差，最后做一次除法格式化输出。

参考实现见 `code/std.cpp`（大整数 + 钩子特征标），`code/brute.cpp` 直接枚举 $S_T$ 上的
随机游走用于小数据对拍（$k\le4$）。
