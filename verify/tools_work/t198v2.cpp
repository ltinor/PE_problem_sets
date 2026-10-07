// PE198 v2: x = p/q 两可 ⟺ 2x = M/N (M 奇, 既约) 是相邻 Farey 对 (a/b, c/d) 的中点
//   ⟺ bc - ad = ±1 且 x = M/N = (ad+bc)/(2bd), d | (M∓1)/2, b | (M±1)/2
// 计数: 对每个奇 M, 枚举 (M±1)/2 的因子对 (d, b), x = M/(2bd) < 1/100,
//   既约分母 = 2bd/gcd(M,2bd) <= 1e8, 去重乘积 bd 后计数.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll QDEN = 100000000LL;
const ll XNUM = 100LL;         // x < 1/XNUM

vector<ll> divs_of(ll n) {     // n >= 1
    vector<ll> ds;
    for (ll i = 1; i * i <= n; i++)
        if (n % i == 0) { ds.push_back(i); if (i != n/i) ds.push_back(n/i); }
    sort(ds.begin(), ds.end());
    return ds;
}

int main(int argc, char** argv) {
    ll Mmax = (argc > 1) ? atoll(argv[1]) : 2000000LL; // M = 2p <= 2e6
    ll total = 0;
    for (ll M = 1; M <= Mmax; M += 2) {
        // x = M/(2v) < 1/100  =>  v > 50*M
        ll vmin = 50 * M + 1;
        // 既约分母 = 2v/gcd(M, 2v) <= QDEN
        //   => 2v/g <= QDEN, g = gcd(M, 2v); 枚举 v 的上界: 2v <= QDEN*g
        //    g | M (奇), g = gcd(M, 2v): g 的 2-part = 1 (M 奇) => 2v 含全部 2 因子
        // 简化: 枚举 v, 直接验证
        ll A1 = (M - 1) / 2, A2 = (M + 1) / 2;   // d | A1 与 b | A2 (或互换)
        vector<ll> d1 = divs_of(A1), d2 = divs_of(A2);
        // 收集全部乘积 v = d*b (两方向, 去重)
        vector<ll> prods;
        for (ll dd : d1) for (ll bb : d2) if (dd * bb > vmin) prods.push_back(dd * bb);
        for (ll dd : d2) for (ll bb : d1) if (dd * bb > vmin) prods.push_back(dd * bb);
        sort(prods.begin(), prods.end());
        prods.erase(unique(prods.begin(), prods.end()), prods.end());
        // 过滤: 既约分母 <= QDEN
        ll cnt = 0;
        for (ll v : prods) {
            ll g = __gcd(M, 2*v);
            if (2*v/g <= QDEN) cnt++;
        }
        total += cnt;
    }
    cout << total << endl;
    return 0;
}
