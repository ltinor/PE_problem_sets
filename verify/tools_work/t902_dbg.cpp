// 902 调试: 直接枚举 pi^k (k=1..ord) 算 rank 与 S_i, 对比闭式
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char** argv) {
    ll m = atoi(argv[1]);
    ll n = m * (m + 1) / 2;
    // sigma/tau/pi (同 std)
    vector<ll> sig(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll k = (ll)((sqrtl(8.0L * i + 1) - 1) / 2);
        if (k * (k + 1) / 2 == i) sig[i] = k * (k - 1) / 2 + 1;
        else sig[i] = i + 1;
    }
    vector<ll> tau(n + 1), tinv(n + 1);
    for (ll i = 1; i <= n; i++) { tau[i] = (1000000007LL % n) * (i % n) % n + 1; tinv[tau[i]] = i; }
    vector<ll> pi(n + 1);
    for (ll i = 1; i <= n; i++) pi[i] = tinv[sig[tau[i]]];

    // ord: 循环长度 lcm
    vector<int> cid(n + 1, -1), off(n + 1, -1);
    vector<vector<int>> cyc;
    for (ll s = 1; s <= n; s++) {
        if (cid[s] != -1) continue;
        int id = cyc.size(); vector<int> c; ll x = s;
        while (cid[x] == -1) { cid[x] = id; off[x] = c.size(); c.push_back(x); x = pi[x]; }
        cyc.push_back(c);
    }
    ll ord = 1;
    for (auto& c : cyc) ord = ord / __gcd(ord, (ll)c.size()) * (ll)c.size();
    printf("m=%lld n=%lld ord=%lld cycles:", m, n, ord);
    for (auto& c : cyc) printf(" %zu", c.size());
    printf("\n");

    // 直接枚举 pi^k, k = 1..ord
    vector<ll> cur(n + 1); for (ll i = 1; i <= n; i++) cur[i] = i; // id
    vector<ll> S(n + 1, 0);
    ll RP = 0; // sum_{k=1}^{ord} rank
    for (ll k = 1; k <= ord; k++) {
        for (ll i = 1; i <= n; i++) cur[i] = pi[cur[i]]; // cur = pi^k
        ll rank = 1;
        ll f = 1; // (n-i)! 从 i=n 开始
        for (ll i = n; i >= 1; i--) {
            ll c = 0;
            for (ll j = i + 1; j <= n; j++) if (cur[j] < cur[i]) c++;
            rank += c * f;
            S[i] += c;
            f *= (n - i + 1);
        }
        RP += rank;
    }
    printf("sum_{k=1..ord} rank = %lld\n", RP);
    for (ll i = 1; i <= n; i++) printf("S[%lld] = %lld (cycle %d, off %d)\n", i, S[i], cid[i], off[i]);
    // P(m) = (m!/ord) * RP
    ll mf = 1; for (ll i = 2; i <= m; i++) mf *= i;
    printf("P(%lld) exact = %lld\n", m, (mf / ord) * RP);
    return 0;
}
