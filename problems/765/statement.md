# Problem 765（PE 765）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=765](https://projecteuler.net/problem=765)。

## **Trillionaire**

Starting with $1$ gram of gold you play a game. Each round you bet a certain amount of your gold: if you have $x$ grams you can bet $b$ grams for any $0 \le b \le x$. You then toss an unfair coin: with a probability of $0.6$ you double your bet (so you now have $x+b$), otherwise you lose your bet (so you now have $x-b$).

Choosing your bets to maximize your probability of having at least a trillion $(10^{12})$ grams of gold after $1000$ rounds, what is the probability that you become a trillionaire?

All computations are assumed to be exact (no rounding), but give your answer rounded to $10$ digits behind the decimal point.

## **万亿富翁**

你正在玩一个游戏，游戏开始时你拥有$1$克黄金。每一轮，如果你拥有$x$克黄金，那么你可以下注任意$0 \le b \le x$克黄金，然后抛掷一枚不公平硬币：有$0.6$的概率你的赌注双倍奉还（此时你拥有$x+b$克黄金），其余的情况下则丧失你的赌注（此时你拥有$x-b$克黄金）。

你将进行$1000$轮游戏，而你的目标是最大化游戏结束时你拥有至少一万亿（$10^{12}$）克黄金的概率。请问在最优策略下，这个最大化的概率是多少？

假设游戏过程中的每次赌注计算都是精确的（没有四舍五入），但你的答案应当四舍五入至小数点后$10$位。

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题（$N = 1000$、目标 $10^{12}$）官方答案；
- 否则为两个整数 $N$ 和 $s$（$1 \le N \le 400$，$0 \le s \le N$），轮数为 $N$，目标为 $2^s$ 克。

## 输出格式

一行一个实数：最优策略下成为"万亿富翁"的概率，保留 10 位小数。

## 样例

### 输入

```
2 1
```

### 输出

```
0.6000000000
```

（第一轮全押：以 $0.6$ 概率赢到 $2$ 克达成目标。$N=2,s=2$ 时需连胜两轮，概率 $0.36$。）

---

## 数据范围

- 若输入为 `PE`，输出 $0.2429251641$；
- 否则 $1 \le N \le 400$，$0 \le s \le N$。

## 提示

在 $p=1/2$ 的公平测度下每条长 $N$ 的胜负路径等概率且财富是鞅，故任何"成功路径集合"需满足 $|S| \le 2^N / 	ext{目标}$。$p = 3/5$ 时 $k$ 胜路径的真实概率为 $3^k 2^{N-k}/5^N$，最优策略按胜数从高到低贪心占用该预算（大整数精确计算）。
