#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 938 (简单版本): Exhausting a Colour / 耗尽同色牌
//
// 原题: 求 P(24690,12345)，牌数太多，朴素 O(R*B) DP 内存/时间都不可行。
// 简单版本: 缩小数据范围 (R,B 较小)，用 O(R*B) 概率 DP 精确计算，
//           并用验证点 P(2,2)=0.4666666667、P(10,9)=0.4118903397、
//           P(34,25)=0.3665688069 验证。
//
// 状态 (r,b): r 张红牌, b 张黑牌。f(r,b)=最终剩余牌为黑色的概率。
// 一次抽两张:
//   两张红: 丢弃两张 -> (r-2,b)   概率 r(r-1)/T
//   两张黑: 放回      -> 自环      概率 b(b-1)/T
//   异色:   放回红,丢黑 -> (r,b-1) 概率 2rb/T
// 消除自环: f(r,b) = [r(r-1) f(r-2,b) + 2rb f(r,b-1)] / [T - b(b-1)]
// 边界: f(0,b)=1 (全黑), f(r,0)=0 (全红)。

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int R, B;
    cin >> R >> B;

    if (R == 0) { cout << fixed << setprecision(10) << 1.0 << "\n"; return 0; }
    if (B == 0) { cout << fixed << setprecision(10) << 0.0 << "\n"; return 0; }

    // 滚动数组: f0 = f(r-2, ·), f1 = f(r-1, ·)
    vector<double> f0(B + 1, 1.0); // f(0,b)=1
    vector<double> f1(B + 1, 0.0); // f(1,b)=0

    double ans = 0.0;
    if (R == 1) {
        ans = 0.0;
    } else {
        for (int r = 2; r <= R; r++) {
            vector<double> cur(B + 1, 0.0);
            for (int b = 1; b <= B; b++) {
                long double T   = (long double)(r + b) * (r + b - 1);
                long double prr = (long double)r * (r - 1);
                long double pbb = (long double)b * (b - 1);
                long double prb = (long double)2.0L * r * b;
                long double denom = T - pbb;
                long double num = prr * f0[b] + prb * cur[b - 1];
                cur[b] = (double)(num / denom);
            }
            f0 = f1;
            f1 = cur;
        }
        ans = f1[B];
    }
    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}
