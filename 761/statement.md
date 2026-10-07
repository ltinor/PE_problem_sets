# Problem 761（PE 761）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=761](https://projecteuler.net/problem=761)。

## **Runner and Swimmer**

Two friends, a runner and a swimmer, are playing a sporting game: The swimmer is swimming within a circular pool while the runner moves along the pool edge. While the runner tries to catch the swimmer at the very moment that the swimmer leaves the pool, the swimmer tries to reach the edge before the runner arrives there. They start the game with the swimmer located in the middle of the pool, while the runner is located anywhere at the edge of the pool.

We assume that the swimmer can move with any velocity up to $1$ in any direction and the runner can move with any velocity up to $v$ in either direction around the edge of the pool. Moreover we assume that both players can react immediately to any change of movement of their opponent.

Assuming optimal strategy of both players, it can be shown that the swimmer can always win by escaping the pool at some point at the edge before the runner gets there, if $v$ is less than the critical speed $V\_{Circle} \approx 4.60333885$ and can never win if $v>V\_{Circle}$.

Now the two players play the game in a perfectly square pool. Again the swimmer starts in the middle of the pool, while the runner starts at the midpoint of one of the edges of the pool. It can be shown that the critical maximal speed of the runner below which the swimmer can always escape and above which the runner can always catch the swimmer when trying to leave the pool is $V\_{Square} \approx 5.78859314$.

At last, both players decide to play the game in a pool in the form of regular hexagon. Giving the same conditions as above, with the swimmer starting in the middle of the pool and the runner at the midpoint of one of the edges of the pool, find the critical maximal speed $V\_{Hexagon}$ of the runner, below which the swimmer can always escape and above which the runner can always catch the swimmer. Give your answer rounded to $8$ digits after the decimal point.

## **跑者与泳者**

跑者与泳者这对好朋友正在进行一场运动比赛：泳者在一个圆形泳池中游泳，而跑者则沿着泳池边缘跑步；跑者试图在泳者离开泳池的瞬间抓住泳者，而泳者则努力在跑者到达之前抵达泳池边缘。比赛开始时，泳者位于泳池的正中心，而跑者则位于泳池边缘的任意位置。

我们假设泳者向任意方向游泳时的最高速率为$1$，而跑者沿着泳池边缘跑步的最高速率为$v$。我们进一步假设双方都能即时地根据对方的行动作出反应。

假设双方都采取最优策略，可以证明，如果$v$小于某个阈值$V\_{Circle} \approx 4.60333885$，则泳者总是能够在跑者到达前抵达泳池边缘并离开，反之若$v>V\_{Circle}$，则泳者永远不可能获胜。

接着，双方在一个正方形泳池中再次进行比赛。同样地，比赛开始时，泳者位于泳池的正中心，但这次跑者位于泳池任意一条边的中点。可以计算出，此时决定跑者能否获胜的最高速率阈值为$V\_{Square} \approx 5.78859314$。

最后，双方决定再到一个正六边形泳池中进行比赛。和之前的条件一样，比赛开始时，泳者位于泳池的正中心，跑者位于泳池任意一条边的重点，求此时跑者的最高速率的阈值$V\_{Hexagon}$，并将你的答案保留小数点后$8$位。

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题（正六边形池）官方答案；
- 否则为整数 $n$，表示泳池形状：$0$ 为圆形，$4$ 为正方形，$6$ 为正六边形。

## 输出格式

一行一个实数：对应形状下跑者的临界速度，保留 8 位小数。

## 样例

### 输入

```
4
```

### 输出

```
5.78859314
```

---

## 数据范围

- 若输入为 `PE`，输出 $5.05505046$（$V_{	ext{Hexagon}}$）；
- 否则 $n \in \{0, 4, 6\}$，分别对应 $V_{	ext{Circle}} = 4.60333885$、$V_{	ext{Square}} = 5.78859314$、$V_{	ext{Hexagon}} = 5.05505046$。

## 提示

临界速度的求解需要构造泳者的最优逃跑策略与跑者的最优追逐策略（迭代几何构造），原题只要求六边形情形。
