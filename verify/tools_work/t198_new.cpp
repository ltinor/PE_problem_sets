// PE198 closed-form counter (candidate final std)
// 判定: x = p/q (既约) 两可 <=> p 奇, q 偶, (q/2) | ((p-1)/2)((p+1)/2)
//   即存在 d | (p-1)/2, b | (p+1)/2 使 q = 2*d*b
// 范围: 0 < x < 1/100, q <= Q  =>  p < Q/100, q = 2*d*b > 100p
// 计数: p=1 特支 + 对每个奇 p 统计 (d,b) 对数 (A,B 互素 => 乘积两两不同, 无需去重)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char** argv) {
    ll Q = (argc > 1) ? atoll(argv[1]) : 100000000LL;

    const ll SM = 500000;
    vector<int> spf(SM + 1, 0);
    for (ll i = 2; i <= SM; i++)
        if (!spf[i]) for (ll j = i; j <= SM; j += i) if (!spf[j]) spf[j] = (int)i;

    ll total = 0;
    // p = 1: A = 0 => 任意 t = q/2 可; q 偶, 100 < q <= Q
    if (Q >= 102) total += Q / 2 - 50;

    ll PMAX = Q / 100; // q > 100p 且 q <= Q
    for (ll p = 3; p <= PMAX; p += 2) {
        ll A = (p - 1) / 2, B = (p + 1) / 2;
        auto divisors = [&](ll x) {
            vector<ll> ds = {1};
            while (x > 1) {
                ll sp = spf[x]; int c = 0;
                while (x % sp == 0) { x /= sp; c++; }
                size_t sz = ds.size(); ll pw = 1;
                for (int i = 0; i < c; i++) {
                    pw *= sp;
                    for (size_t t = 0; t < sz; t++) ds.push_back(ds[t] * pw);
                }
            }
            sort(ds.begin(), ds.end());
            return ds;
        };
        vector<ll> dB = divisors(B);
        vector<ll> dA = divisors(A);
        // 统计 d*b ∈ (50p, Q/2]
        ll LO = 50 * p + 1, HI = Q / 2;
        ll cnt = 0;
        for (ll d : dA) {
            if (d > HI) break;
            ll lob = (LO + d - 1) / d;
            ll hib = HI / d;
            if (lob > hib) continue;
            cnt += upper_bound(dB.begin(), dB.end(), hib) - lower_bound(dB.begin(), dB.end(), lob);
        }
        total += cnt;
    }
    cout << total << endl;
    return 0;
}
