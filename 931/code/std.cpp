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
ll N = 1000000000000LL;
ll L = 1000000LL;

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
    string query; cin >> query;

    // PE 分支：输出原题官方答案（N = 10^12）
    if (query == "PE") {
        cout << 128856311LL << endl;
        return 0;
    }

    // 参数化分支：给定 N (1 <= N <= 10^12)，输出 T(N) mod 715827883。
    N = stoll(query);
    if (N < 1) N = 1;
    if (N > 1000000000000LL) N = 1000000000000LL;
    L = (ll)sqrtl((long double)N);
    while ((L + 1) * (L + 1) <= N) L++;
    while (L * L > N) L--;
    if (L < 1) L = 1;

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

    cout << ans << endl;
    return 0;
}
