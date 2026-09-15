# PE842 — Irrational Jumps（无理跳跃）

来源：改编自 Project Euler Problem 842

## 原题意

一个过程或粒子按无理步长在直线或圆上进行跳跃。每次跳跃的长度或角度为无理数（如 $\sqrt{2}$、$\pi$、$e$、黄金比例 $\varphi$）。

常见解释包括：
1. **Beatty 序列**：$\lfloor n\alpha\rfloor$（$\alpha > 1$ 为无理数）。Rayleigh 定理：若 $1/\alpha+1/\beta=1$，则两序列分划自然数。
2. **无理旋转**：$x_{n+1}=\{x_n+\alpha\}\bmod 1$，对无理 $\alpha$ 序列等分布。
3. **三间隙定理（Steinhaus）**：$k\alpha\bmod 1$ 点间最多 3 种间距。

PE 答案：299724841336576。

## 算法

1. **Beatty 序列求和**：$\sum_{k=1}^N\lfloor k\alpha\rfloor$ 可使用 O(log N) 的 floor-sum 算法。
2. **floor_sum 算法**：递归计算 $\sum_{i=0}^{n-1}\lfloor(ai+b)/m\rfloor$，来源于 Concrete Mathematics。
3. **Wythoff 博弈**：$\varphi$ 的 Beatty 序列对 $(\lfloor n\varphi\rfloor, \lfloor n\varphi^2\rfloor)$。
4. **无理旋转**：使用模 1 加法模拟圆周上的无理跳跃。

## 改编方向

1. 推广到高维无理跳跃（如二维环面上的无理旋转）
2. 研究跳跃序列的统计性质（自相关、间隙分布）
3. 考虑跳跃大小随时间变化的非平稳过程
4. 探索无理跳跃与丢番图逼近的联系
