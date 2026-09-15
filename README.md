# PE_problem_sets · Project Euler → OJ 题目改编集

将 [Project Euler](https://projecteuler.net) 第 **1 ～ 968** 题改编为 ACM/OI 风格的 OJ 试题：把原题的固定常数输入参数化、支持多组测试数据，并为每题配齐中文题面、改编说明、标准解、暴力解、数据生成器与对拍脚本。改编总体原则是**不改变原题难度的前提下参数化输入**。

## 每题的文件结构

每题一个目录（`001/` ~ `968/`），结构以 `_template/` 为规范：

| 文件 / 目录 | 说明 |
| --- | --- |
| `statement.md` | OJ 题面：题目描述、输入输出格式、样例 |
| `README.md` | 改编说明：原题意 → 参数化后的新题 → 数据范围 → 算法 |
| `NNN.md` | Project Euler 原题双语对照（绝大多数题目附带） |
| `code/std.cpp` | 标准解，用于生成 `*.out` |
| `code/brute.cpp` | 暴力解，用于与标准解对拍 |
| `code/gen.cpp` | 小数据生成器（仅对拍使用） |
| `code/gen_data.cpp` | 正式数据生成器 |
| `data/` | `NN.in` / `NN.out` 测试数据（部分题目已内置，其余可本地生成） |
| `scripts/check.sh` | std / brute / gen 暴力对拍脚本（小数据对拍） |
| `scripts/gen_out.sh` | 调用 `std.cpp` 读取 `*.in` 生成 `*.out` |
| `Makefile` | 编译、数据生成、对拍、清理 |
| `eval.sh` | 标准解运行计时 |

## 快速上手

```bash
cd 001
make           # 编译 std / brute / gen / gen_data
make data      # 生成正式测试数据（*.in / *.out）
make check     # 暴力对拍
./eval.sh      # 标准解计时
make clean     # 清理编译产物
```

依赖：`g++`（C++17）与 `bash`。

## 仓库布局

```
PE_problem_sets/
├── 001/ ~ 968/      题目目录，共 968 题
├── _template/       题目文件结构模板，新题从复制此目录开始
├── _tools/          构建、抓取、分析脚本；各批次验证脚本在 _tools/verify/
├── docs/
│   ├── Skill.md          批量改编工作流定义（读取原题库 → 提炼改编方向 → 按模板落地成题）
│   └── reports/          各批次进度报告与阶段总结（SUMMARY*、RUN_REPORT* 等）
├── source/          网站源文件：_posts/ 为 PE 原题双语库（1.md ~ 968.md），
│                    另有 problems/（题目索引页）、about/、resources/
└── _archive/        历史遗留存档（未做穷举核对，暂保留待查）
    ├── PE_alias/         616 个 PE 前缀目录：多为对应数字目录的旧版/残缺副本，
    │                     但含少量独有文件（如 PE0315 的 data/、PE0687 的探索代码）
    ├── shortname_dup/    41/42/43 无前导零目录：与 041~043 为不同版本
    └── misc/             临时脚本、运行日志、tar 归档、根目录 data 等杂项
```

## 现状备注

- 全部 968 题具备统一的 `statement.md` / `README.md` / `code/` / `scripts/` / `Makefile` 结构；`data/` 仅部分题目随仓库提交，其余题目在本地执行 `make data` 即可生成。
- 早期题目（约前 100 题）为改编规范探索阶段：部分缺少 `NNN.md` 原题对照，个别目录留有 `std.txt` / `input.txt` 等运行产物；个别题目使用 SPJ 判题（如 009）。
- 最初 1 ～ 10 题示例阶段的 README（含改编策略与规范讨论）已归档至 `docs/reports/README_v1_001-010示例.md`。
- 各批次改编进度与验证记录见 `docs/reports/`。

## 相关链接

- 原题来源：[Project Euler](https://projecteuler.net)
- 改编工作流：见 `docs/Skill.md`
