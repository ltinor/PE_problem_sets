#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 947: Fibonacci Residues / 斐波那契余数（简单版本）
//
// 原题：S(10^6) mod 999999893。
// 改编：读入 M (1 <= M <= 200)，输出 S(M) mod 999999893。
//
// (a,b,m)-序列：g(0)=a, g(1)=b, g(n) = (g(n-1)+g(n-2)) mod m。
// p(a,b,m) 为其周期。s(m) = Σ_{a,b} p(a,b,m)^2，S(M) = Σ_{m=1}^{M} s(m)。
//
// 暴力：对每个 m、每个 (a,b) 直接迭代求周期（周期 <= Pisano 周期 π(m) <= 6m）。
//
// 验证点：s(3)=513, S(3)=542, s(10)=225820, S(10)=310897。

const ll MOD = 999999893LL;

ll period(ll a, ll b, ll m) {
    ll x = a, y = b;
    ll bound = 6 * m + 10; // 安全上界
    for (ll n = 1; n <= bound; n++) {
        ll z = (x + y) % m;
        x = y;
        y = z;
        if (x == a && y == b) return n;
    }
    return bound; // 不应发生
}

ll s_of_m(ll m) {
    ll sum = 0;
    for (ll a = 0; a < m; a++) {
        for (ll b = 0; b < m; b++) {
            ll p = period(a, b, m);
            sum = (sum + (i128)p * p) % MOD;
        }
    }
    return sum;
}

ll solve(ll M) {
    ll ans = 0;
    for (ll m = 1; m <= M; m++) {
        ans = (ans + s_of_m(m)) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll M;
    if (!(cin >> M)) return 0;
    if (M < 1 || M > 200) return 0;
    cout << solve(M) << "\n";
    return 0;
}
