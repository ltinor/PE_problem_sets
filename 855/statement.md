# Problem 855（PE 855）

> ⚠️ 本题面为自动生成的骨架：题目描述取自 PE 原题（中文译文）。
> 【输入格式 / 输出格式 / 数据范围】与原题的参数化改编有关，**待人工校对补充**；
> 若目录下已有 data/ 数据，可对照实际输入输出理解约定。

## 原题描述

原题及更多讨论见 [https://projecteuler.net/problem=855](https://projecteuler.net/problem=855)。

## **Delphi Paper**

Given two positive integers $a,b$, Alex and Bianca play a game in $ab$ rounds. They begin with a square piece of paper of side length $1$.

In each round Alex divides the current rectangular piece of paper into $a \times b$ pieces using $a-1$ horizontal cuts and $b-1$ vertical ones. The cuts do not need to be evenly spaced. Moreover, a piece can have zero width/height when a cut coincides with another cut or the edge of the paper. The pieces are then numbered $1, 2, \ldots, ab$ starting from the left top corner, moving from left to right and starting from the left of the next row when a row is finished.

Then Bianca chooses one of the pieces for the game to continue on. However, Bianca must not choose a piece with a number she has already chosen during the game.

Bianca wants to minimize the area of the final piece of paper while Alex wants to maximize it. Let $S(a,b)$ be the area of the final piece assuming optimal play.

For example, $S(2,2) = 1/36$ and $S(2, 3) = 1/1800 \approx 5.5555555556\mathrm{e}{-4}$.

Find $S(5,8)$. Give your answer in scientific notation rounded to ten significant digits after the decimal point. Use a lowercase e to separate the mantissa and the exponent.

## **德尔菲分纸法**

亚历克斯和比安卡在玩游戏，这个游戏需要进行$ab$轮，其中$a$和$b$均为正整数。游戏开始时，需要一张边长为$1$的正方形纸。

在每一轮中，亚历克斯在纸上横切$a-1$刀，竖切$b-1$刀，将其分成$a\times b$块长方形纸片。刀与刀间的距离无需相同，而且可以相互重合，此时对应的长方形长度或宽度为零。随后，从纸的左上角开始，从上至下、从左至右依次将长方形纸片编号为$1, 2, \ldots, ab$。

随后，比安卡选择其中一张长方形纸片并下一轮游戏，但比安卡所选纸片的编号不能与之前轮数中的选择相同。

比安卡的目标是使游戏结束时纸片的面积尽可能小，而亚历克斯的目标则是使之尽可能大。记$S(a,b)$为双方都采取最优策略时最终的纸片面积。

例如，$S(2,2) = 1/36$，$S(2, 3) = 1/1800 \approx 5.5555555556\mathrm{e}{-4}$。

求$S(5,8)$，并将你的答案用科学计数法表示（用小写字母e分隔尾数和指数），保留十位小数。

---

## 输入格式

（待人工补充：请对照 code/std.cpp 的读取约定描述。）

## 输出格式

（待人工补充。）

## 样例

（无 data 数据，待人工补充。）

---

## 数据范围

（待人工补充；原题参数范围见上方原题描述。）

