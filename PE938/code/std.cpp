#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 938: Exhausting a Colour / 耗尽同色牌（简单版本）
//
// 原题：P(24690,12345)，保留 10 位小数。
// 改编：读入 R B（0 <= R,B <= 2000），输出 P(R,B)，保留 10 位小数。
//
// 状态 (r,b)：
//   两张红：C(r,2)/C(r+b,2) -> (r-2, b)
//   两张黑：C(b,2)/C(r+b,2) -> (r, b)   (自环)
//   一红一黑：2rb/C(r+b,2) -> (r, b-1)
//
// 消除自环后：
//   f(r,b) = [r(r-1)*f(r-2,b) + 2rb*f(r,b-1)] / [(r+b)(r+b-1) - b(b-1)]
//
// 边界：r==0 -> f=1（全黑，黑胜）；b==0 -> f=0（全红）。
//
// 验证点：P(2,2)=0.4666666667, P(10,9)=0.4118903397, P(34,25)=0.3665688069。

double solve(int R, int B) {
    // dp[r][b]
    vector<vector<double>> dp(R + 1, vector<double>(B + 1, 0.0));
    // r == 0：全黑，f = 1
    for (int b = 0; b <= B; b++) dp[0][b] = 1.0;
    // b == 0：全红，f = 0（默认已为 0）
    for (int b = 1; b <= B; b++) {
        for (int r = 1; r <= R; r++) {
            double num = 0.0;
            if (r >= 2) num += (double)r * (r - 1) * dp[r - 2][b];
            num += (double)2 * r * b * dp[r][b - 1];
            double denom = (double)(r + b) * (r + b - 1) - (double)b * (b - 1);
            dp[r][b] = num / denom;
        }
    }
    return dp[R][B];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int R, B;
    if (!(cin >> R >> B)) return 0;
    if (R < 0 || B < 0 || R > 2000 || B > 2000) return 0;
    cout << fixed << setprecision(10) << solve(R, B) << "\n";
    return 0;
}
