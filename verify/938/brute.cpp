#include<bits/stdc++.h>
using namespace std;

// PE 938 暴力版：递归记忆化 DP（与 std 相同的转移方程，独立实现用于对拍）。
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int R, B;
    cin >> R >> B;
    vector<vector<double>> dp(R + 1, vector<double>(B + 1, -1.0));
    function<double(int,int)> f = [&](int r, int b) -> double {
        if (r == 0) return 1.0;
        if (b == 0) return 0.0;
        if (dp[r][b] >= 0) return dp[r][b];
        long double T   = (long double)(r + b) * (r + b - 1);
        long double prr = (long double)r * (r - 1);
        long double pbb = (long double)b * (b - 1);
        long double prb = (long double)2.0L * r * b;
        long double denom = T - pbb;
        long double num = 0.0L;
        if (r >= 2) num += prr * f(r - 2, b);
        num += prb * f(r, b - 1);
        return dp[r][b] = (double)(num / denom);
    };
    cout << fixed << setprecision(10) << f(R, B) << "\n";
    return 0;
}
