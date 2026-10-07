# Problem 613（PE 613）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=613](https://projecteuler.net/problem=613)。

## **Pythagorean Ant**

Dave is doing his homework on the balcony and, preparing a presentation about Pythagorean triangles, has just cut out a triangle with side lengths 30cm, 40cm and 50cm from some cardboard, when a gust of wind blows the triangle down into the garden.
Another gust blows a small ant straight onto this triangle. The poor ant is completely disoriented and starts to crawl straight ahead in random direction in order to get back into the grass.

Assuming that all possible positions of the ant within the triangle and all possible directions of moving on are equiprobable, what is the probability that the ant leaves the triangle along its longest side?
Give your answer rounded to 10 digits after the decimal point.

## **毕达哥拉斯蚂蚁**

戴夫正在阳台上做家庭作业；为了准备一个关于毕达哥拉斯三角形的展示，他刚刚从硬纸板上剪下了一个边长分别为30厘米、40厘米和50厘米的三角形，这时一阵风吹来把三角形吹到了花园中。
另一阵风把一只小蚂蚁径直吹到了三角形上。这只可怜的蚂蚁完全迷失了方向，只能随机选了个方向一直向前爬，想要回到草丛中。

假设蚂蚁等可能地落在三角形内的任意位置并选择了任意方向，那么它最终从最长边离开三角形的概率是多少？
将你的答案四舍五入到小数点后10位小数。

---

## 输入格式

第一行一个 token：

- 若为 `PE`，输出原题官方答案；
- 否则为整数 $n$（$100 \le n \le 8000$），表示数值积分的分辨率。

## 输出格式

一行一个实数：从斜边离开的概率（保留 10 位小数，随 $n$ 增大收敛到官方值）。

## 样例

### 输入

```
8000
```

### 输出

```
0.3916721499
```

（收敛值即官方答案 $0.3916721504$。）

---

## 数据范围

- 若输入为 `PE`，输出 $0.3916721504$；
- 否则 $100 \le n \le 8000$。

## 提示

对三角形内每点，方向命中斜边的概率等于斜边线段在该点的张角除以 $2\pi$；对 $(x,y)$ 在三角形上做二重复合 Simpson 积分即可（换元到 $u,v\in[0,1], u+v\le1$）。原题 $30	ext{-}40	ext{-}50$ 直角三角形面积为 $600$。
