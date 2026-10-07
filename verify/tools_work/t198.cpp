// PE198: 两可数计数
// x = p/q (既约) 两可 ⟺ p 奇, q 偶, 且 q = d*b, d | (p-1)/2, b | (p+1)/2
// (x 为某相邻 Farey 对的中点; 推导见批注)
// 计数: 0 < x < 1/100, q <= 10^8 => 奇数 p <= 10^6, q > 100p
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll Q = 100000000LL;
const ll PMAX = 1000000LL;

vector<ll> divs(ll n) { // n = 0 => 空表(特殊处理), n>=1
    vector<ll> ds;
    for (ll i = 1; i * i <= n; i++)
        if (n % i == 0) { ds.push_back(i); if (i != n / i) ds.push_back(n / i); }
    return ds;
}

int main() {
    // SPF 筛到 5e5 供快速分解
    const ll SM = 500000;
    vector<ll> spf(SM + 1, 0);
    for (ll i = 2; i <= SM; i++)
        if (!spf[i]) for (ll j = i; j <= SM; j += i) if (!spf[j]) spf[j] = i;

    ll total = 0;
    // p = 1 特例: A = 0 (d 任意), B = 1 (b = 1) => q = d: 偶数 d, 100 < d <= Q
    total += (Q / 2) - 50; // 偶数 d ∈ (100, 1e8]: 49999450
    for (ll p = 3; p <= PMAX; p += 2) {
        ll A = (p - 1) / 2, B = (p + 1) / 2;
        // 分解 A 与 B (A, B <= 5e5)
        auto fact = [&](ll x) {
            vector<pair<ll,int>> f;
            while (x > 1) {
                ll sp = spf[x]; int c = 0;
                while (x % sp == 0) { x /= sp; c++; }
                f.push_back({sp, c});
            }
            return f;
        };
        vector<ll> dA = {1}, dB = {1};
        for (auto& [pp, e] : fact(A)) {
            size_t sz = dA.size(); ll pw = 1;
            for (int i = 0; i < e; i++) { pw *= pp; for (size_t t = 0; t < sz; t++) dA.push_back(dA[t] * pw); }
        }
        for (auto& [pp, e] : fact(B)) {
            size_t sz = dB.size(); ll pw = 1;
            for (int i = 0; i < e; i++) { pw *= pp; for (size_t t = 0; t < sz; t++) dB.push_back(dB[t] * pw); }
        }
        ll lo = 100 * p; // q > 100p (严格)
        // 判据(两方向): q = d*b, (d|A 且 b|B) 或 (d|B 且 b|A)
        // 去重: q | A (或 q | B) 时两个方向都会计到它, 需减去重复
        // 两方向枚举所有 (d, b) 组合, 按 q 去重 (同一 x 可能有多组 (b,d) 拆分)
        vector<ll> qs;
        for (ll dd : dA) {
            if (dd > Q) continue;
            for (ll bb : dB) {
                ll q = dd * bb;
                if (q > Q || q <= lo) continue;
                if ((q & 1) == 0) qs.push_back(q);
            }
        }
        for (ll dd : dB) {
            if (dd > Q) continue;
            for (ll bb : dA) {
                ll q = dd * bb;
                if (q > Q || q <= lo) continue;
                if ((q & 1) == 0) qs.push_back(q);
            }
        }
        sort(qs.begin(), qs.end());
        total += unique(qs.begin(), qs.end()) - qs.begin();
    }
    cout << total << endl;
    return 0;
}
