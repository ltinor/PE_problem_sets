# PE843 — Periodic Circles（周期圆）

来源：改编自 Project Euler Problem 843

## 原题意

圆以周期模式排列——可能在二维格子、Ford 圆模式或其他周期结构中。问题要求计算与这些圆相关的量，如总面积、周长、交点数或半径和。

可能的解释：
1. **Ford 圆**：对每个既约分数 $p/q$，半径为 $1/(2q^2)$ 的圆，圆心在 $(p/q, 1/(2q^2))$。这些圆两两相切或不相交。
2. **周期格子中的圆填充**：圆排列在二维格点上，计算覆盖面积或重叠。
3. **Apollonian 垫片**：自相似周期结构的圆填充（Descartes 圆定理）。
4. **整数半径圆**：格点上的整数半径圆，计数或求和。

PE 答案：1591033983566。

## 算法

1. **Ford 圆面积和**：$\text{Area}(N)=(\pi/4)\sum_{q=1}^N \varphi(q)/q^4$。
2. **Ford 圆周长和**：$\text{Perim}(N)=\pi\sum_{q=1}^N \varphi(q)/q^2$。
3. **欧拉函数 $\varphi(q)$**：计算与 $q$ 互素的整数个数。
4. **Gauss 圆问题**：计算圆内格点数 $N(R)=1+4\lfloor R\rfloor+4\sum_{i=1}^{\lfloor R\rfloor}\lfloor\sqrt{R^2-i^2}\rfloor$。

## 改编方向

1. 推广到三维 Ford 球
2. 研究不同周期格子的圆填充效率
3. 探索 Ford 圆的 Farey 序列联系
4. 计算 Apollonian 垫片中的整数曲率圆
