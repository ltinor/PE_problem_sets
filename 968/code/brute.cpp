#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// 独立暴力校验：直接枚举 a,b,c,d,e 全部五个变量
const ll MOD = 1000000007LL;

ll X[5][5];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int order[10][2] = {
        {0,1},{0,2},{0,3},{0,4},{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}
    };
    for (int k = 0; k < 10; k++) {
        ll v;
        cin >> v;
        X[order[k][0]][order[k][1]] = v;
        X[order[k][1]][order[k][0]] = v;
    }

    ll b[5] = {(ll)1e18, (ll)1e18, (ll)1e18, (ll)1e18, (ll)1e18};
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (j != i) b[i] = min(b[i], X[i][j]);

    static const ll p[5] = {2, 3, 5, 7, 11};
    ll ans = 0;
    for (ll a = 0; a <= b[0]; a++)
    for (ll bb = 0; bb <= b[1]; bb++)
    for (ll c = 0; c <= b[2]; c++)
    for (ll d = 0; d <= b[3]; d++)
    for (ll e = 0; e <= b[4]; e++) {
        ll x[5] = {a, bb, c, d, e};
        bool ok = true;
        for (int i = 0; i < 5 && ok; i++)
            for (int j = i + 1; j < 5; j++)
                if (x[i] + x[j] > X[i][j]) { ok = false; break; }
        if (!ok) continue;
        ll w = 1;
        for (int i = 0; i < 5; i++)
            for (ll t = 0; t < x[i]; t++)
                w = (i128)w * p[i] % MOD;
        ans = (ans + w) % MOD;
    }
    cout << ans << "\n";
    return 0;
}
