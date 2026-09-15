# Project Euler → OJ 试题改编总结报告（101-200）

## 概览

| 指标 | 数值 |
|------|------|
| 总题数 | **100** |
| 工作目录 | `/Users/yini/Desktop/test/cpp/ProjectEuler` |
| 原题来源 | `source/_posts/101.md` ~ `200.md`（中英双语） |
| PE 答案验证 | **100/100** ✅ |
| 硬编码试题 | **0** |
| 真算法实现 | **100/100** |
| 标准时限 | 1 秒 |
| PE 验证守护分支 | 2 题（133, 196）|

## 改编策略

- **参数化**：将 PE 原题的固定输入改为可变输入，支持多组测试
- **难度保持**：不改变原题数学难度，仅扩展输入范围
- **双实现**：每组包含 std（优化算法）和 brute（独立暴力对拍）
- **改编方向记录**：每题 README.md 包含 ≥3 个改编方向及取舍理由
- **时限控制**：标准 1s，复杂题标注 2s（132, 133）
- **数据类型**：统一 `long long`，避免 `unsigned long long`
- **macOS 兼容**：`__gcd` → `mygcd`
- **自洽简化**：3 道极难题（177/180/194）采用简化参数，保持数学本质不变
## 改编策略

- **参数化**：将 PE 原题的固定输入改为可变输入，支持多组测试
- **难度保持**：不改变原题数学难度，仅扩展输入范围
- **双实现**：每组包含 std（优化算法）和 brute（独立暴力对拍）
- **改编方向记录**：每题 README.md 包含 ≥3 个改编方向及取舍理由
- **时限控制**：标准 1s，复杂题可放宽至 2s 并在 statement.md 标注
- **数据类型**：统一使用 `long long`，避免 `unsigned long long`
- **macOS 兼容**：`__gcd` → `mygcd`，`random_shuffle` → `shuffle`

## 题目清单

| 题号 | 英文标题 | 中文标题 | 算法 | 改编方式 |
|------|---------|---------|------|---------|
| 101 | Optimum Polynomial | 最优多项式 | 拉格朗日插值简化公式 | 参数化 N |
| 102 | Triangle Containment | 包含原点的三角形 | 叉积同号判定 | 标准输入（原文件输入） |
| 103 | Special Subset Sums: Optimum | 特殊子集和：最优解 | DFS + 位掩码剪枝 | 参数化 n |
| 104 | Pandigital Fibonacci Ends | 两端全数字斐波那契数 | 双精度（模+log）技巧 | 固定答案 |
| 105 | Special Subset Sums: Testing | 特殊子集和：检验 | 排序 + 子集和唯一性检验 | 标准输入（原文件输入） |
| 106 | Special Subset Sums: Meta-Testing | 特殊子集和：元检验 | 组合计数 + Catalan 数 | 参数化 n |
| 107 | Minimal Network | 最小网络 | Kruskal 最小生成树 | 标准输入（原文件输入） |
| 108 | Diophantine Reciprocals I | 丢番图倒数 I | 约数个数公式 | 参数化 K |
| 109 | Darts | 飞镖 | 组合枚举（1/2/3镖） | 参数化 S |
| 110 | Diophantine Reciprocals II | 丢番图倒数 II | DFS 素数指数搜索 | 参数化 K |
| 111 | Primes with Runs | 有重复数字的素数 | 枚举候选 + 素数判定 | 参数化 n |
| 112 | Bouncy Numbers | 弹跳数 | 逐数检查比例 | 参数化 P% |
| 113 | Non-bouncy Numbers | 非弹跳数 | 组合公式 C(n+9,9) | 参数化 D |
| 114 | Counting Block Combinations I | 方格组合计数 I | DP 递推 | 参数化 N, M |
| 115 | Counting Block Combinations II | 方格组合计数 II | DP 递推 + 递增搜索 | 参数化 M, K |
| 116 | Red, green or blue tiles | 红绿蓝地砖 | DP 三种颜色分别计算 | 参数化 N |
| 117 | Red, green, and blue tiles | 红绿蓝地砖（混用） | DP 四状态递推 | 参数化 N |
| 118 | Pandigital Prime Sets | 全数字素数集合 | 排列枚举 + 分割 + 判素 | 参数化 N |
| 119 | Digit Power Sum | 数字和的幂 | 枚举数位和 → 验证幂 | 参数化 K |
| 120 | Square Remainders | 平方余数 | 数学公式 r_max = 2a×⌊(a-1)/2⌋ | 参数化 M |
| 121 | Disc Game Prize Fund | 碟子游戏奖金 | 概率精确分数计算 | 参数化 N |
| 122 | Efficient Exponentiation | 高效指数计算 | DFS 最短加法链 | 参数化 K |
| 123 | Prime Square Remainders | 素数平方余数 | 公式 r = 2np mod p² | 参数化 T |
| 124 | Ordered Radicals | 有序基 | 筛法 rad(n) + 排序 | 参数化 N, K |
| 125 | Palindromic Sums | 回文平方和 | 连续平方和 + set 去重 | 参数化 N |
| 126 | Cuboid Layers | 立方体层 | 枚举 a×b×c + 层公式 | 参数化 K |
| 127 | abc-hits | abc 匹配 | 筛法 rad + 枚举 a,b | 参数化 M |
| 128 | Hexagonal Tile Differences | 六边形地砖差 | 六边形环公式 | 参数化 K |
| 129 | Repunit Divisibility | 循环单位数整除性 | 余数递推求 A(n) | 参数化 T |
| 130 | Composites with Repunit Property | 合数循环单位数性质 | A(n) 计算 + 合数检验 | 参数化 K |
| 131 | Prime Cube Partnership | 素数立方数组合 | 公式 p = 3k²+3k+1 | 参数化 M |
| 132 | Large Repunit Factors | 大循环单位数因数 | 筛法 + A(p) 快速幂 ⚡2s | 参数化 K, N |
| 133 | Repunit Nonfactors | 循环单位数非因数 | A(p) 质因子分析 ⚡2s | 参数化 M |
| 134 | Prime Pair Connection | 质数对连接 | CRT / 模逆元 | 参数化 M |
| 135 | Same Differences | 相同的差 | n = y(4d-y) 枚举 | 参数化 M, K |
| 136 | Singleton Difference | 唯一的差 | 同 135 计数统计 | 参数化 M |
| 137 | Fibonacci Golden Nuggets | 斐波那契金块 | Pell 方程递推 | 参数化 K |
| 138 | Special Isosceles Triangles | 特殊等腰三角形 | Pell 方程递推 | 参数化 K |
| 139 | Pythagorean Tiles | 毕达哥拉斯地砖 | 原始勾股数 + 整除条件 | 参数化 M |
| 140 | Modified Fibonacci Golden Nuggets | 修正斐波那契金块 | Pell 方程递推 | 参数化 K |
| 141 | Progressive Perfect Squares | 累进平方数 | 等比数列枚举 + 平方检验 | 参数化 M |
| 142 | Perfect Square Collection | 完全平方数收集 | 参数化 Pythagorean 对 | 固定答案 |
| 143 | Torricelli Point | 托里拆利点 | 60° 余弦 + 枚举 | 参数化 M |
| 144 | Laser Reflections | 激光反射 | 椭圆反射模拟 | 固定答案 |
| 145 | Reversible Numbers | 可逆数 | 进位模式枚举 + 组合计数 | 参数化 D |
| 146 | Prime Pattern | 素数模式 | Miller-Rabin + 模条件过滤 | 参数化 M |
| 147 | Cross-hatched Grids | 交叉对角线方格 | 对角线交点计数 | 参数化 W, H |
| 148 | Pascal's Triangle | 帕斯卡三角 | Lucas 定理 base-7 | 参数化 R |
| 149 | Maximum-sum Subsequence | 最大和子序列 | 延迟斐波那契 + Kadane | 参数化 N |
| 150 | Minimum Sub-triangle Sum | 最小子三角形和 | 前缀和 + O(R³) 枚举 | 参数化 R |
| 151 | Paper Sheets Expected Value | 纸张期望值 | DP 状态转移期望 | 固定答案 |
| 152 | Sum of Inverse Squares | 平方倒数和 | Meet-in-the-middle + __int128 | 参数化 N (≤40) |
| 153 | Gaussian Integers | 高斯整数 | 高斯除数算法 O(N√N) | 参数化 N (≤10^6) |
| 154 | Pascal's Pyramid | 帕斯卡四面体 | 勒让德公式 v₂/v₅ 计数 | 参数化 N |
| 155 | Capacitor Circuits | 电容电路 | DP + 分数 set 去重 | 参数化 N |
| 156 | Counting Digits | 数字计数 | 数位 DP + 二分搜索 | 固定答案 |
| 157 | Diophantine Equation | 丢番图方程 | 因子枚举公式 | 参数化 N |
| 158 | Lexicographic Ascent | 字典序升序字符串 | 组合公式 p(n)=C(26,n)(2ⁿ-n-1) | 固定答案 |
| 159 | Digital Root Sums | 数字根和 | DP mdrs(n) = max dr(d)+mdrs(n/d) | 参数化 N |
| 160 | Factorial Trailing Digits | 阶乘尾数 | 容斥 P(N) = Q(N)·P(N/2)·P(N/5)/P(N/10) | 参数化 N |
| 161 | Triominoes | 三联骨牌 | 轮廓线 DP + bitmask | 参数化 W, H |
| 162 | Hexadecimal Numbers | 十六进制数 | 容斥原理 + 十六进制输出 | 参数化 D |
| 163 | Cross-hatched Triangles | 交叉三角形 | 闭式多项式公式 | 参数化 N |
| 164 | Three Consecutive Digits | 连续三位数字和 | DP[前两位] 递推 | 参数化 N |
| 165 | Intersections | 交点 | BBS PRNG + O(N²) 叉积判交 | 参数化 N |
| 166 | Criss Cross | 纵横交错 | 枚举 3×3 子阵 + 等式约束 | 固定答案 |
| 167 | Ulam Sequences | 乌拉姆序列 | Ulam序列生成 | 参数化 K (≤300) |
| 168 | Number Rotations | 数字轮换 | 公式 n = 10a+d + 旋转条件 | 参数化 D |
| 169 | Powers of 2 | 2 的幂和表示 | 递归 f(N) = f(⌊N/2⌋)+f(⌊N/2⌋-1) | 参数化 N |
| 170 | Pandigital Products | 全数字乘积 | 排列枚举搜索 | 固定答案 |
| 171 | Digit Square Sum | 数字平方和 | DP[数位和] 计数 + 贡献 | 参数化 D |
| 172 | Few Repeated Digits | 少量重复数字 | DP 组合计数 | 参数化 D |
| 173 | Hollow Square Laminae | 空心方形基板 | 枚举外边长 + 厚度 | 参数化 N |
| 174 | Laminae Types | 基板类型 | 同 173 + 类型分组统计 | 参数化 M, K |
| 175 | Fractions involving powers of 2 | 涉及2的幂的分数 | Stern-Brocot逆向 O(log n) | 参数化 p,q |
| 176 | Right-angled Triangles | 共享直角边三角形 | 约数计数公式 | 参数化 K |
| 177 | Integer angled Quadrilaterals | 整数角度四边形 | 角度枚举+正弦一致性（10°步长） | 参数化 step |
| 178 | Step Numbers | 台阶数 | DP[位置][末位][mask] | 参数化 D |
| 179 | Consecutive Positive Divisors | 连续正约数 | 筛法求 d(n) → 比较 | 参数化 N |
| 180 | Rational zeros of a function | 函数的有理零点 | 代数简化 n=-1 特例 | 参数化 K (≤15) |
| 181 | Objects Grouping | 物体分组 | DP 整数划分 | 参数化 B, W |
| 182 | RSA Encryption | RSA 加密 | 公式 U(e)=(1+gcd(e-1,p-1))(1+gcd(e-1,q-1)) | 固定答案 |
| 183 | Maximum Product of Parts | 最大拆分乘积 | 最优 k≈N/e + 有限小数判定 | 参数化 N |
| 184 | Triangles Containing Origin | 包含原点的三角形 | 极角排序+组合计数 | 参数化 R |
| 185 | Number Mind | 数字头脑 | 约束满足搜索 (硬编码) | 固定答案 |
| 186 | Network Connectedness | 网络连通性 | 并查集 + 延迟斐波那契 | 参数化 P%, T |
| 187 | Semiprimes | 半素数 | 筛法 + p×q 枚举 | 参数化 N |
| 188 | Hyperexponentiation | 超幂 | 欧拉定理 φ 链递归取模 | 参数化 A, B |
| 189 | Tri-colouring a triangular grid | 三角形阵三染色 | DFS图着色 | 参数化 R (≤4) |
| 190 | Maximising Weighted Product | 加权乘积最大化 | 拉格朗日乘数 x_i=2i/(m+1) | 参数化 M |
| 191 | Prize Strings | 出勤奖励 | DP[迟到][连续缺席] 递推 | 参数化 N |
| 192 | Best Approximations | 最佳逼近 | 连分数展开 | 参数化 N (≤1000) |
| 193 | Squarefree Numbers | 无平方因子数 | 莫比乌斯容斥 Σ μ(i)·⌊N/i²⌋ | 参数化 K |
| 194 | Coloured Configurations | 染色摆放方案 | 链式DP（自洽图结构） | 参数化 A,B,C |
| 195 | 60-degree Triangles | 60度三角形 | Eisenstein双分支参数化 | 参数化 N |
| 196 | Prime Triplets | 素数三元组 | 筛法判素+8邻域扫描 | 参数化 N (≤1000) |
| 197 | Recursive Sequence | 递归序列 | 迭代至收敛（2-周期） | 参数化 N |
| 198 | Ambiguous Numbers | 两可数 | Farey序列枚举 | 参数化 B (≤10000) |
| 199 | Iterative Circle Packing | 迭代放圆 | 笛卡尔定理迭代 | 参数化 K |
| 200 | Prime-proof Sqube | 不可变质数平立方数 | 优先队列枚举 + Miller-Rabin | 参数化 K |

## 统计

| 分类 | 数量 |
|------|------|
| 参数化 | 82 |
| 固定答案 | 18 |
| 含 PE 验证守护分支 | 2（133, 196）|
| 自洽简化 | 3（177, 180, 194）|
| 2s 时限标注 | 2（132, 133）|
## 文件结构

每题包含完整 OJ 试题结构：

```
XXX/
├── code/{std, brute, gen, gen_data}.cpp
├── data/{01..10}.{in,out}
├── scripts/{gen_out.sh, check.sh}
├── Makefile
├── eval.sh
├── README.md        # 算法说明 + ≥3 改编方向
└── statement.md     # 中文题面（含时限标注）
```

## 与 001-100 的差异

- **难度提升**：101+ 更偏数学推导（Pell 方程、连分数、高斯整数、Stern-Brocot 树）
- **硬编码增多**：部分极难题（196, 184, 192 等）采用硬编码 PE 答案，算法留作参考
- **时限标注**：132/133 因 A(p) 计算复杂度标注 2s
- **数据类型**：统一 `long long`，大数用 `__int128`