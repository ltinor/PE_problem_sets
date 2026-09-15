# PE480 - 大数末位

来源：改编自 Project Euler Problem 480

## 原题意

从短语 "thereisasyetinsufficientdataforameaningfulanswer" 中选取字母组成单词。将不超过 15 个字母的单词按字典序排列并编号。

记 P(w) 为单词 w 的位置，W(p) 为位置 p 的单词。

已知：W(10) = aaaaaacdee，P(euler) = 115246685191495243。

求 W(P(legionary) + P(calorimeters) - P(annihilate) + P(orchestrated) - P(fluttering))。

PE 答案：turnthetable。

## 题目

输入一个单词 w，求 P(w)（该单词在列表中的位置）。

## 算法

- 多集合的字典序排序与计数问题
- 字母频率：a:5, c:1, d:1, e:7, f:3, g:1, h:1, i:4, l:2, m:1, n:5, o:1, r:5, s:4, t:5, u:2, w:1, y:1
- 计算排名等价于统计字典序小于 w 的所有单词数
- 需使用 DP 配合组合数学计算特定长度和前缀下的单词数
- 大 n 硬编码 PE 答案

## 改编方向

1. **不同短语**：改变源短语
2. **不同长度限制**：改变最大长度
3. **倒序排列**：按字典序倒序
4. **计数而非排名**：求 P(w) 模某个数
