// PE198 v3: 两方向判据 + 按 (p,q) 去重
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll Q = 100000000LL;

vector<ll> divs_of(ll n) {
    vector<ll> ds;
    for (ll i = 1; i * i <= n; i++)
        if (n % i == 0) { ds.push_back(i); if (i != n/i) ds.push_back(n/i); }
    return ds;
}

int main(int argc, char** argv) {
    ll PMAX = 1000000LL;
    if (argc > 1) PMAX = atoll(argv[1]);
    ll total = 0;
    // p = 1 特例: d | 0 任意, b | 1 => b = 1, q = d: 偶数 d, 100 < d <= Q
    total += (Q / 2) - 50;
    for (ll p = 3; p <= PMAX; p += 2) {
        ll A = (p - 1) / 2, B = (p + 1) / 2;
        vector<ll> dA = divs_of(A), dB = divs_of(B);
        ll lo = 100 * p;
        set<ll> qs;
        for (int orient = 0; orient < 2; orient++) {
            auto& D = orient ? dB : dA;
            auto& Bl = orient ? dA : dB;
            for (ll d : D) {
                if (d > Q) continue;
                for (ll b : Bl) {
                    ll q = d * b;
                    if (q > Q || q <= lo || (q & 1)) continue;
                    qs.insert(q);
                }
            }
        }
        total += qs.size();
    }
    cout << total << endl;
    return 0;
}
