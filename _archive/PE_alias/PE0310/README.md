# Nim Square（平方取石子）

来源：改编自 Project Euler Problem 310

## 原题意

三堆 Nim 游戏，每次只能取平方数个石子。求 0 ≤ a ≤ b ≤ c ≤ 100,000 时必败态个数。PE 答案：2586528661783。

## 题目

输入 N，求 0 ≤ a ≤ b ≤ c ≤ N 时必败态（三堆 Grundy 值异或为 0）的个数。

## 数据范围

$1 \\le N \\le 10^5$。

## 算法

### 方向一：Grundy 数计算

对每堆大小 i，Grundy 值 g[i] = mex{g[i - k²] | k² ≤ i}。递推 O(N√N)。

### 方向二：计数

统计每个 Grundy 值的频数。枚举 (a, b)，通过前缀和 O(1) 查询满足 g[a]^g[b]^g[c]=0 且 c ≥ b 的 c 的个数。

### 时间复杂度

Grundy 计算 O(N√N)，计数 O(N²)。N=10⁵ 时约 2s，N≤3×10⁴ 时 <1s。
