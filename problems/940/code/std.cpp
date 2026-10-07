#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 940（简单版本）：二维递归 Two-Dimensional Recurrence
//
// 原题：求 S(50) mod 1123581313（f_50 ≈ 1.25e10，需要 O(log) 闭式解）。
// 简单版本：缩数据到 k <= 20（f_20 = 6765），用 O(f_k^2) 的 DP 递推即可在
//           几秒内算出，且算法直接来自定义，容易验证。
//
// A(0,0)=0, A(0,1)=1
// A(m+1,n)   = A(m,n+1) + A(m,n)
// A(m+1,n+1) = 2*A(m+1,n) + A(m,n)
// S(k) = sum_{i=2..k} sum_{j=2..k} A(f_i, f_j)
//
// 验证点：S(3)=30，S(5)=10396。
//
// 由两条原始递推可消元得到单向递推：
//   A(m+2,n) = 3*A(m+1,n) + A(m,n)      (固定 n，沿 m 方向)
//   A(m,n+2) = A(m,n+1) + 3*A(m,n)      (固定 m，沿 n 方向)
// 从而先用后者算出 A(0,*) 与 A(1,*)（初值 A(0,0)=0,A(0,1)=1；
// A(1,0)=1,A(1,1)=2），再对每一列 n=f_j 用前者把 m 方向填满。

const ll MOD = 1123581313LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll k;
    if (!(cin >> k)) return 0;

    // 斐波那契
    vector<ll> f(k + 1);
    f[0] = 0; f[1] = 1;
    for (int i = 2; i <= k; i++) f[i] = f[i - 1] + f[i - 2];
    ll M = f[k];

    // A(0,*) 与 A(1,*)：沿 n 方向递推（需要到 M）
    vector<ll> a0(M + 1), a1(M + 1);
    a0[0] = 0; a0[1] = 1;
    for (int n = 0; n + 2 <= M; n++) a0[n + 2] = (a0[n + 1] + 3 * a0[n]) % MOD;
    a1[0] = 1; a1[1] = 2;
    for (int n = 0; n + 2 <= M; n++) a1[n + 2] = (a1[n + 1] + 3 * a1[n]) % MOD;

    // A(f_i, f_j)：只对需要的列 n = f_j 沿 m 方向填满
    ll S = 0;
    vector<ll> col(M + 1);
    for (int j = 2; j <= k; j++) {
        int n = (int)f[j];
        col[0] = a0[n];
        col[1] = a1[n];
        for (int m = 0; m + 2 <= M; m++) col[m + 2] = (3 * col[m + 1] + col[m]) % MOD;
        for (int i = 2; i <= k; i++) S = (S + col[f[i]]) % MOD;
    }

    cout << S << "\n";
    return 0;
}
