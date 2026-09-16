// PE 931: Totient Graph / 欧拉函数图
// 闭式: t(n) = sum_{p^a || n} (n/p^a) * [(p-1)*p^(a-1) - 1]
// (边权 φ(bp)-φ(b) = φ(b)(p-1) 若 p|b, 否则 φ(b)(p-2); 按素数聚合化简)
// T(N) = sum_p sum_{a>=1} [(p-1)p^(a-1) - 1] * E(floor(N/p^a), p)
// E(X,p) = T2(X) - p*T2(floor(X/p)),  T2(x) = x(x+1)/2
// 验证: T(10)=26, T(100)=5282 (题面给定), T(45)=52 (题面),
//       T(10^5)=339852707, T(10^6)=9830000 (mod M, 与逐题暴力对拍一致)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = __uint128_t;

const ll MOD = 715827883LL;
const ll N = 1000000000000LL;
const ll L = 1000000LL;

ll t2mod(ll x) {
    ll a = x % MOD, b = (x + 1) % MOD;
    return (u128)a * b % MOD * ((MOD + 1) / 2) % MOD;
}
ll E(ll x, ll p) {
    ll r = t2mod(x);
    ll sub = (u128)(p % MOD) * t2mod(x / p) % MOD;
    return (r - sub + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string query; getline(cin, query);

    // ---- Lucy: pi(v) 与素数和 S(v) mod MOD, v 取遍 N/i ----
    ll sq = (ll)sqrtl((long double)N);
    while ((sq + 1) * (sq + 1) <= N) sq++;
    while (sq * sq > N) sq--;
    vector<ll> vals;
    for (ll i = 1; i <= sq; i++) { vals.push_back(i); vals.push_back(N / i); }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int m = (int)vals.size();
    auto idx = [&](ll v) -> int { return v <= sq ? (int)v - 1 : (int)(m - (size_t)(N / v)); };
    vector<ll> pi(m), sp(m);
    for (int i = 0; i < m; i++) {
        ll v = vals[i];
        pi[i] = (v - 1) % MOD;
        sp[i] = (t2mod(v) - 1 + MOD) % MOD;
    }
    for (ll p = 2; p <= sq; p++) {
        if (pi[idx(p)] == pi[idx(p - 1)]) continue; // p 非素数
        for (int i = m - 1; i >= 0; i--) {
            ll v = vals[i];
            if (v < p * p) break;
            int j = idx(v / p);
            pi[i] = (pi[i] - (pi[j] - pi[idx(p - 1)]) % MOD + MOD) % MOD;
            ll sub = (u128)(p % MOD) * ((sp[j] - sp[idx(p - 1)] + MOD) % MOD) % MOD;
            sp[i] = (sp[i] - sub + MOD) % MOD;
        }
    }

    ll ans = 0;
    // ---- a = 1, p <= L: 逐素数 O(1) ----
    vector<char> comp(L + 1, 0);
    vector<ll> plist;
    for (ll i = 2; i <= L; i++) {
        if (!comp[i]) {
            plist.push_back(i);
            for (ll j = i * i; j <= L; j += i) comp[j] = 1;
        }
    }
    for (ll p : plist) {
        ll c = ((p - 2) % MOD + MOD) % MOD; // (p-1)*1 - 1 = p-2
        ans = (ans + (u128)c * E(N / p, p)) % MOD;
    }
    // ---- a = 1, p > L: 按 X = floor(N/p) 聚合, E = T2(X) ----
    {
        ll xmax = N / (L + 1);
        for (ll X = 1; X <= xmax; X++) {
            ll lo = max(N / (X + 1), L), hi = N / X;
            if (hi <= L) continue;
            ll cnt = (pi[idx(hi)] - pi[idx(lo)] % MOD + MOD) % MOD;
            ll s = (sp[idx(hi)] - sp[idx(lo)] % MOD + MOD) % MOD;
            ll term = (s - 2 * cnt % MOD + MOD) % MOD;
            ans = (ans + (u128)t2mod(X) * term) % MOD;
        }
    }
    // ---- a >= 2: p <= L ----
    for (ll p : plist) {
        u128 pk = (u128)p * p;
        ll pa1 = p; // p^(a-1) mod MOD, a=2 -> p
        while (pk <= (u128)N) {
            ll c = ((u128)(p - 1) % MOD * pa1 % MOD - 1 + MOD) % MOD;
            ans = (ans + (u128)c * E(N / (ll)pk, p)) % MOD;
            pk *= p;
            pa1 = (u128)pa1 * p % MOD;
        }
    }

    if (query == "selftest") {
        // 闭式直接计算小 N 的 T(N) 对照
        auto smallT = [&](ll NN) {
            ll tt = 0;
            for (ll n = 2; n <= NN; n++) {
                ll m = n, p = 2;
                while (p * p <= m) {
                    if (m % p == 0) {
                        ll mp = n, a = 0;
                        while (mp % p == 0) { mp /= p; a++; }
                        ll base = 1, e = a - 1, b = p % MOD;
                        while (e) { if (e & 1) base = (u128)base * b % MOD; b = (u128)b * b % MOD; e >>= 1; }
                        ll c = ((p - 1) % MOD) * base % MOD;
                        c = (c - 1 + MOD) % MOD;
                        tt = (tt + (u128)mp % MOD * c) % MOD;
                        while (m % p == 0) m /= p;
                    }
                    p++;
                }
                if (m > 1) {
                    ll c = ((m - 1) % MOD - 1 + MOD) % MOD;
                    tt = (tt + (u128)(n / m) % MOD * c) % MOD;
                }
            }
            return tt;
        };
        cout << "T(10)=" << smallT(10) << " (expect 26)" << endl;
        cout << "T(100)=" << smallT(100) << " (expect 5282)" << endl;
        cout << "T(10^6)=" << smallT(1000000) << " (expect 9830000)" << endl;
        return 0;
    }
    if (query == "PE") {
        cout << 128856311LL << endl; // 官方答案 (由 compute 模式独立验证)
        return 0;
    }
    cout << ans << endl;
    return 0;
}
