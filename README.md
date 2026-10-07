# Project Euler Problem Set

968 道 Project Euler 竞赛编程题，改编为支持参数化输入的 OJ 格式。

## 结构

```
├── problems/              968 个问题目录 (001/ … 968/)
│   ├── 001/
│   │   ├── statement.md     题面
│   │   ├── std.cpp          标准解法
│   │   ├── data/            测试数据
│   │   └── README.md        算法说明
│   └── …
├── verify/                  对拍验证文件（brute.cpp, gen.cpp 等）
├── tools/                   审计与批量操作脚本
├── docs/reports/            审计报告与算法分析笔记
└── source/                  PE 原题资源
```

## 使用

```bash
# 编译
g++ -std=c++17 -O2 problems/001/code/std.cpp -o std

# 运行（输入格式见题面）
./std < problems/001/data/01.in

# 验证
diff <(./std < problems/001/data/01.in) problems/001/data/01.out
```

## 统计

| 指标 | 数值 |
|---|---|
| 总题数 | 968 |
| 编译通过 | 100% |
| data 覆盖 | 100%（3095 对） |
