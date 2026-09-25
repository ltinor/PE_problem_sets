# Problem 770（PE 770）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=770](https://projecteuler.net/problem=770)。

## **Delphi Flip**

A and B play a game. A has originally $1$ gram of gold and B has an unlimited amount. Each round goes as follows:
- A chooses and displays, $x$, a nonnegative real number no larger than the amount of gold that A has.
- Either B chooses to TAKE. Then A gives B $x$ grams of gold.
- Or B chooses to GIVE. Then B gives A $x$ grams of gold.

B TAKEs $n$ times and GIVEs $n$ times after which the game finishes.

Define $g(X)$ to be the smallest value of $n$ so that A can guarantee to have at least $X$ grams of gold at the end of the game. You are given $g(1.7) = 10$.

Find $g(1.9999)$.

## **狡诈的先知**

A和B正在玩一个游戏。游戏开始时，A持有$1$克黄金，而B则持有无穷的黄金。在每一轮游戏中：
- A选择并展示一个非负数实数$x$，且$x$不超过A持有的黄金数量。
- B可以选择<i class=zh>拿走</i>，此时A必须将$x$克黄金交给B。
- B也可以选择<i class=zh>赠予</i>，此时B必须将$x$克黄金交给A。

当B选择了恰好各$n$次<i class=zh>拿走</i>和<i class=zh>赠予</i>后，游戏结束。

记$g(X)$为最小的$n$，使得A能保证游戏结束时至少持有$X$克黄金。已知$g(1.7) = 10$。

求$g(1.9999)$。

<i class=zh>译注：本题源自《科学美国人》2001年8月刊同名谜题，大意是赌徒向先知请教接下来数次硬币抛掷的结果，先知虽然能够准确预测未来，但偶尔也会撒谎，赌徒需要决定如何下注以最大化收益。</i>

---

## 输入格式

字符 `PE`：输出原题官方答案。

## 输出格式

原题官方答案。

## 样例

（无 data 数据，参见原题样例。）

---

## 数据范围

见原题参数范围。
参考常量: PE_ANSWER = 1273112231728726740LL
