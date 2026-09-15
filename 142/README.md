# 完全平方数收集 (Perfect Square Collection)

来源：改编自 Project Euler Problem 142

## 原题意

求最小的 x+y+z（x>y>z>0 整数），使得 x±y, x±z, y±z 均为完全平方数。

原题答案：1006193

## 题目

固定答案题。输出最小的 x+y+z 使得满足条件的 x,y,z 存在。

## 数据范围

- 固定输出（无参数输入）

## 算法

设：
- x+y=a², x-y=b² → x=(a²+b²)/2, y=(a²-b²)/2
- x+z=c², x-z=d² → x=(c²+d²)/2, z=(c²-d²)/2

枚举 a>b（同奇偶），计算 x,y。对于每个 x，找 c>d（同奇偶）使得 (c²+d²)/2=x。验证 y±z 是否为完全平方数。

取最小的 x+y+z。
