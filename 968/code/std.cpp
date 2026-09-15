#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 968 简化版：五维求和
//
// 定义 P(X_ab, X_ac, X_ad, X_ae, X_bc, X_bd, X_be, X_cd, X_ce, X_de)
// = Σ 2^a·3^b·5^c·7^d·11^e，求和范围是所有满足下面约束的非负五元组 (a,b,c,d,e)：
//   a+b ≤ X_ab, a+c ≤ X_ac, a+d ≤ X_ad, a+e ≤ X_ae,
//   b+c ≤ X_bc, b+d ≤ X_bd, b+e ≤ X_be,
//   c+d ≤ X_cd, c+e ≤ X_ce,
//   d+e ≤ X_de。
//
// 原题（PE 968）需对 100 组极大的 X 值求和，本简化版将 X 缩小到 [0, 15]，
// 单次求 P 可用 O(B^4) 枚举 + 最后一个变量等比数列闭合式。
//
// 验证点：
//   P(2,2,2,2,2,2,2,2,2,2) = 7120
//   P(1,2,3,4,5,6,7,8,9,10) ≡ 799809376 (mod 1e9+7)

const ll MOD = 1000000007LL;

ll mod_pow(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp) {
        if (exp & 1) res = (i128)res * base % MOD;
        base = (i128)base * base % MOD;
        exp >>= 1;
    }
    return res;
}

ll mod_inv(ll x) { return mod_pow(x, MOD - 2); }

// 变量下标：0=a, 1=b, 2=c, 3=d, 4=e
// X[i][j] = 第 i 与第 j 个变量的和的上界（i<j）
ll X[5][5];

ll solve() {
    static const ll p[5] = {2, 3, 5, 7, 11};
    // 枚举前 4 个变量 a,b,c,d，用闭合式求和 e
    ll inv10 = mod_inv(10); // 11-1 = 10
    ll ans = 0;
    ll ba = 1e18, bb = 1e18, bc = 1e18, bd = 1e18;
    for (int j = 0; j < 5; j++) if (j != 0) ba = min(ba, X[0][j]);
    for (int j = 0; j < 5; j++) if (j != 1) bb = min(bb, X[1][j]);
    for (int j = 0; j < 5; j++) if (j != 2) bc = min(bc, X[2][j]);
    for (int j = 0; j < 5; j++) if (j != 3) bd = min(bd, X[3][j]);

    for (ll a = 0; a <= ba; a++) {
        ll pa = mod_pow(2, a);
        for (ll b = 0; b <= bb; b++) {
            if (a + b > X[0][1]) break;
            ll pab = (i128)pa * mod_pow(3, b) % MOD;
            for (ll c = 0; c <= bc; c++) {
                if (a + c > X[0][2]) break;
                if (b + c > X[1][2]) break;
                ll pabc = (i128)pab * mod_pow(5, c) % MOD;
                for (ll d = 0; d <= bd; d++) {
                    if (a + d > X[0][3]) break;
                    if (b + d > X[1][3]) break;
                    if (c + d > X[2][3]) break;
                    ll E = min({X[0][4] - a, X[1][4] - b, X[2][4] - c, X[3][4] - d});
                    if (E < 0) continue;
                    // Σ_{e=0}^{E} 11^e = (11^{E+1} - 1) / 10
                    ll geo = (mod_pow(11, E + 1) - 1 + MOD) % MOD;
                    geo = (i128)geo * inv10 % MOD;
                    ll term = (i128)pabc * mod_pow(7, d) % MOD * geo % MOD;
                    ans = (ans + term) % MOD;
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // 读入 10 个整数，顺序：
    // X_ab X_ac X_ad X_ae X_bc X_bd X_be X_cd X_ce X_de
    // 即 (0,1)(0,2)(0,3)(0,4)(1,2)(1,3)(1,4)(2,3)(2,4)(3,4)
    int order[10][2] = {
        {0,1},{0,2},{0,3},{0,4},{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}
    };
    for (int k = 0; k < 10; k++) {
        ll v;
        cin >> v;
        X[order[k][0]][order[k][1]] = v;
        X[order[k][1]][order[k][0]] = v;
    }
    cout << solve() << "\n";
    return 0;
}
