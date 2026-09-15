# 双斜整数四边形 (Biclinic Integral Quadrilaterals)

来源：改编自 Project Euler Problem 311

## 原题意

凸四边形 ABCD，边长为整数满足 1 ≤ AB < BC < CD < AD。BD 为整数，O 为 BD 中点，AO 为整数。若 AO = CO ≤ BO = DO，称 ABCD 为双斜整数四边形。记 B(N) 为满足 AB²+BC²+CD²+AD² ≤ N 的四边形数。PE 答案：B(10^10) = 2466018557。

## 题目

输入 N，求 B(N)。

## 数据范围

$1 \\le N \\le 10^6$。

## 算法

### 方向一：两平方和分解

核心条件 AB²+AD² = BC²+CD² = S。对每个 S ≤ N/2，找出所有表示为两平方和的数对。

### 方向二：对角线验证

对于每组候选四边形 (a,b,c,d)，验证存在整数 BD 和 AO 满足几何条件。

### 时间复杂度

枚举两平方和 O(N)，内部检查常数级。N=10⁶ 约 0.5s。
