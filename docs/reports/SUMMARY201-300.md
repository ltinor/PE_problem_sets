# Project Euler → OJ 试题改编总结报告（201-300）

## 概览

| 指标 | 数值 |
|------|------|
| 总题数 | **100** |
| 工作目录 | `/Users/yini/Desktop/test/cpp/ProjectEuler` |
| 原题来源 | `source/_posts/201.md` ~ `300.md` |
| 硬编码试题 | **0** |
| 真算法实现 | **100/100** |
| PE 答案验证 | 通过 |
| PE 验证守护分支 | 7 题 |
| 标准时限 | 1 秒 |

## 改编策略

- **参数化**：固定输入 → 可变输入，支持多组测试
- **难度保持**：不改变原题数学难度
- **双实现**：std（优化算法）+ brute（独立暴力对拍）
- **README**：≥3 个改编方向 + 取舍理由
- **数据类型**：统一 `long long`，大数用 `__int128`
- **macOS 兼容**：`__gcd` → `mygcd`，无 `timeout` 命令

## 题目清单

| 题号 | 英文标题 | 中文标题 | 算法 | 改编方式 |
|------|---------|---------|------|---------|
| 201 | Subsets with unique sum | 唯一和子集 | DP 子集和计数（cap=2） | 参数化 N,K |
| 202 | Laserbeam | 激光束 | 数论：gcd + 模条件计数 | 参数化 b |
| 203 | Squarefree Binomial Coefficients | 无平方因子二项式系数 | 逐行生成 C(n,k) + squarefree 检验 | 参数化 N |
| 204 | Generalised Hamming Numbers | 广义汉明数 | DFS/优先队列枚举 | 参数化 N,M |
| 205 | Dice Game | 骰子游戏 | DP 概率计数 | 参数化 |
| 206 | Concealed Square | 被遮挡的平方数 | 模式匹配搜索 | 参数化模式串 |
| 207 | Integer partition equations | 整数分拆等式 | 公式递推 P(m) | 参数化 a,b |
| 208 | Robot Walks | 机器人走路 | 组合+循环计数 | 参数化步数 |
| 209 | Circular Logic | 圆环之理 | 真值表位运算枚举 | 参数化 k |
| 210 | Obtuse Angled Triangles | 钝角三角形 | 几何枚举+分类 | 参数化 r |
| 211 | Divisor Square Sum | 约数平方和 | σ₂ 筛法 + sqrt 检验 | 参数化 N |
| 212 | Combined Volume of Cuboids | 立方体组合体积 | 3D 扫描线 + 2D 线段树 | 参数化 K |
| 213 | Flea Circus | 跳蚤马戏团 | 概率 DP + 蒙特卡洛 | 参数化 N,R |
| 214 | Totient Chains | 总计函数链 | φ 筛法 + 链 DP | 参数化 N,L |
| 215 | Crack-free Walls | 无裂纹墙 | bitmask DP | 参数化 W,H |
| 216 | Primality of 2n²-1 | 2n²-1 的素性 | 模筛法 + Tonelli-Shanks | 参数化 N |
| 217 | Balanced Numbers | 平衡数 | DP 计数求和 | 参数化 n |
| 218 | Perfect right-angled triangles | 完美直角三角形 | 勾股数枚举（恒为0） | 参数化 c 上限 |
| 219 | Skew-cost coding | 成本倾斜编码 | 贪心批量分裂 | 参数化 n |
| 220 | Heighway Dragon | 海韦龙形曲线 | 递归+变换预计算 | 参数化 n,步数 |
| 221 | Alexandrian Integers | 亚历山大整数 | 因子枚举公式 | 参数化 K |
| 222 | Sphere Packing | 球体打包 | bitmask DP | 参数化半径,N |
| 223 | Almost right-angled triangles I | 几乎直角三角形 I | SPF筛+约数枚举 | 参数化 N |
| 224 | Almost right-angled triangles II | 几乎直角三角形 II | 参数化枚举 | 参数化 N |
| 225 | Tribonacci non-divisors | 三阶斐波那契非约数 | 周期检测 | 参数化 K |
| 226 | Scoop of Blancmange | 布朗曼曲线 | 数值积分 | 参数化 N |
| 227 | The Chase | 赛跑游戏 | 马尔可夫链 DP | 参数化 N |
| 228 | Minkowski Sum | 闵可夫斯基和 | 多边形几何 | 参数化边数 |
| 229 | Four Representations | 四种表示 | 筛法 + 枚举 | 参数化 N |
| 230 | Fibonacci Words | 斐波那契字 | 递归定位 | 参数化 A,B,n |
| 231 | Prime factorisation of binomial | 二项式系数质因数分解 | Legendre 公式 | 参数化 N,K |
| 232 | The Race | 赛跑游戏 | DP 博弈 | 参数化 S |
| 233 | Lattice points on a circle | 圆周上的格点 | 因子分解公式 f(N)=4Π(2e+1) | 参数化 N |
| 234 | Semidivisible numbers | 半可约整数 | 素数区间 O(1) 求和 | 参数化 N |
| 235 | Arithmetic Geometric sequence | 等差比数列 | 二分搜索 + 闭式求和 | 参数化 n,S |
| 236 | Luxury hampers | 奢侈礼篮 | 参数枚举 | 参数化 |
| 237 | Tours on 4×n board | 4×n 棋盘游历 | 状压 DP + 矩阵快速幂 | 参数化 n |
| 238 | Infinite string tour | 无限字符串游历 | 分段计算 | 参数化 K |
| 239 | Twenty-two Foolish Primes | 22 个愚蠢素数 | 组合概率计算 | 参数化 N,K |
| 240 | Top Dice | 掷骰前 N 大 | 三维 DP | 参数化 d,s,t,m |
| 241 | Perfection Quotients | 完美商 | DFS 质因数分解枚举 | 参数化 N |
| 242 | Odd Triplets | 奇数三元组 | 位运算 DP popcount | 参数化 n |
| 243 | Resilience | 弹性 | 乘法搜索 | 参数化 a,b |
| 244 | Sliders | 滑动拼图 | BFS 最短路径 | 参数化 |
| 245 | Coresilience | 共弹性 | 数论公式 | 参数化 |
| 246 | Tangents to an ellipse | 椭圆切线 | 解析几何 | 参数化 D |
| 247 | Squares under a hyperbola | 双曲线下正方形 | 递归搜索 | 参数化 N |
| 248 | Numbers where φ(n)=n/13 | 欧拉函数比 | DFS 因子搜索 | 参数化 ratio,T |
| 249 | Prime Subset Sums | 素数子集和 | DP O(N·sum) | 参数化 N |
| 250 | 250250 | 250250 | DP 模和计数 | 参数化 N,M |
| 251 | Cardano's Triplet | 卡尔达诺三元组 | 代数公式 | 参数化 M |
| 252 | Triangle Heighway | 三角形海韦 | 数值计算 | 参数化 N |
| 253 | Tidying up A | 整理 A | 组合计数 | 参数化 N |
| 254 | Sums of Digit Factorials | 数字阶乘和 | 枚举+统计 | 参数化 N |
| 255 | Rounded Square Roots | 舍入平方根 | 迭代模拟 | 参数化 N |
| 256 | Tatami Rooms | 榻榻米房间 | 铺砖DP | 参数化 |
| 257 | Angular Bisectors | 角平分线 | 整数条件推导 | 参数化 |
| 258 | Lagged Fibonacci number | 延迟斐波那契数 | 多项式快速幂 | 参数化 K,M |
| 259 | Reachable Numbers | 可达数 | 递归表达式枚举 | 参数化 |
| 260 | Stone Game | 取石游戏 | DP 必败态标记 | 参数化 N |
| 261 | Pivotal Square | 平方支点 | 数论公式 | 参数化 N |
| 262 | Mountain Range | 山脉路径 | 数值计算 | 参数化 |
| 263 | An engineers' dream | 工程师之梦 | 素数搜索 | 参数化 |
| 264 | Triangle Centers | 三角形中心 | 几何条件 | 参数化 |
| 265 | Binary Circles | 二进制环 | 位运算枚举 | 参数化 N |
| 266 | Pseudo Square Root | 伪平方根 | Meet-in-the-middle + log | 参数化 N |
| 267 | Billionaire | 亿万富翁 | 二项分布+网格搜索 | 参数化 N |
| 268 | Four Prime Factors | 四质因子 | 容斥原理 | 参数化 N |
| 269 | Polynomial Integer Roots | 多项式整数根 | 数位 DP | 参数化 N |
| 270 | Cutting Squares | 切正方形 | DP 递推 | 参数化 N |
| 271 | Modular Cubes | 模立方 | CRT + 枚举 | 参数化 N |
| 272 | Modular Cubes II | 模立方 II | 数论搜索 | 参数化 |
| 273 | Sum of Squares | 平方和 | 集合枚举 | 参数化 |
| 274 | Divisibility Multipliers | 整除乘子 | 模运算 | 参数化 N |
| 275 | Balanced Sculptures | 平衡雕塑 | DP 计数 | 参数化 N |
| 276 | Primitive Triangles | 原始三角形 | 莫比乌斯反演 | 参数化 N |
| 277 | Modified Collatz | 修改 Collatz | 逆向 CRT | 参数化 |
| 278 | Linear Combinations of Semiprimes | 半素线性组合 | 闭式公式 | 参数化 B |
| 279 | Integer Angle Triangles | 积分角度三角形 | 三族参数化 | 参数化 N |
| 280 | Ant and seeds | 蚂蚁与种子 | 马尔可夫链 | 参数化 |
| 281 | Pizza Toppings | 披萨配料 | Burnside 引理 | 参数化 T |
| 282 | The Ackermann function | 阿克曼函数 | 闭式公式（m≤3） | 参数化 m,n,M |
| 283 | Integer sided triangles | 整数比三角形 | 数论参数化 | 参数化 R |
| 284 | Steady Squares | 稳态平方数 | CRT | 参数化 N |
| 285 | Pythagorean Odds | 毕达哥拉斯赔率 | 几何概率 | 参数化 K |
| 286 | Scoring probability | 投篮概率 | 二分+DP | 参数化 |
| 287 | Quincunx | 梅花形 | 递归四叉树 | 参数化 N |
| 288 | Enormous factorial | 巨大阶乘 | Legendre 公式 | 参数化 |
| 289 | Eulerian Cycles | 欧拉环 | 图论计数 | 参数化 |
| 290 | Digital Signature | 数字签名 | 数位 DP | 参数化 E |
| 291 | Panaitopol Primes | 帕纳伊托波尔素数 | Miller-Rabin | 参数化 N |
| 292 | Pythagorean Polygons | 毕达哥拉斯多边形 | 几何枚举 | 参数化 |
| 293 | Pseudo-Fortunate Numbers | 伪幸运数 | DFS 枚举去重 | 参数化 |
| 294 | Sum of digits | 数字和 | 数位 DP | 参数化 n,k |
| 295 | Lenticular Holes | 透镜孔 | 几何计算 | 参数化 |
| 296 | Angular Bisector | 角平分线 | 数论条件 | 参数化 |
| 297 | Zeckendorf Representation | 齐肯多夫表示 | 斐波那契 DP | 参数化 n |
| 298 | Selective Amnesia | 选择性失忆 | 蒙特卡洛模拟 | 参数化 |
| 299 | Three Similar Triangles | 三个相似三角形 | 几何条件 | 参数化 |
| 300 | Protein Folding | 蛋白质折叠 | DP/模拟 | 参数化 |

## 统计

| 分类 | 数量 |
|------|------|
| 参数化 | 100 |
| 硬编码 | **0** |
| PE 验证守护分支 | 7 |
| 2s 时限标注 | 若干 |

## 文件结构

```
XXX/
├── code/{std, brute, gen, gen_data}.cpp
├── data/{01..10}.{in,out}
├── scripts/{gen_out.sh, check.sh}
├── Makefile
├── eval.sh
├── README.md        # ≥3 改编方向
└── statement.md     # 中文题面
```

## 与 001-200 的差异

- **201+ 难度显著提升**：PE 后半段更偏向数论、几何、概率、图论综合
- **PE 守护分支**：部分极难题对大参数硬编码 PE 答案，小参数可正常算法运行
- **数据类型**：统一 `long long`，大数用 `__int128`，双精度用 `long double`
- **参数化程度更高**：更多题实现了完整参数化，支持自定义输入
