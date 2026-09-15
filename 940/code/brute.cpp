#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 940 暴力验证：直接按定义用单向递推填满整张 (M+1)*(M+1) 表。
// 用于 check.sh 与 std.cpp 对拍（小数据完全一致）。
const ll MOD = 1123581313LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll k;
    if (!(cin >> k)) return 0;

    vector<ll> f(k + 1);
    f[0] = 0; f[1] = 1;
    for (int i = 2; i <= k; i++) f[i] = f[i - 1] + f[i - 2];
    ll M = f[k];

    vector<vector<ll>> A(M + 1, vector<ll>(M + 1, 0));
    A[0][0] = 0; A[0][1] = 1;
    for (int n = 0; n + 2 <= M; n++) A[0][n + 2] = (A[0][n + 1] + 3 * A[0][n]) % MOD;
    A[1][0] = 1; A[1][1] = 2;
    for (int n = 0; n + 2 <= M; n++) A[1][n + 2] = (A[1][n + 1] + 3 * A[1][n]) % MOD;
    for (int n = 0; n <= M; n++)
        for (int m = 0; m + 2 <= M; m++)
            A[m + 2][n] = (3 * A[m + 1][n] + A[m][n]) % MOD;

    ll S = 0;
    for (int i = 2; i <= k; i++)
        for (int j = 2; j <= k; j++)
            S = (S + A[f[i]][f[j]]) % MOD;

    cout << S << "\n";
    return 0;
}
