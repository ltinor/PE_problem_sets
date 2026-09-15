#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 100000;

ll mod_pow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

ll mod_inv(ll a) {
    ll m = MOD, x0 = 1, x1 = 0;
    ll a0 = a;
    while (a0 > 1) {
        ll q = a0 / m;
        ll t = m;
        m = a0 % m;
        a0 = t;
        t = x1;
        x1 = x0 - q * x1;
        x0 = t;
    }
    if (x0 < 0) x0 += MOD;
    return x0;
}

ll count_factors(ll N, ll p) {
    ll cnt = 0;
    for (ll x = p; x <= N; x *= p) cnt += N / x;
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    if (N <= 1) { cout << "00001\n"; return 0; }

    // For small N, verify by direct computation
    if (N <= 20) {
        ll fact = 1;
        for (ll i = 2; i <= N; i++) fact *= i;
        while (fact % 10 == 0) fact /= 10;
        cout << setw(5) << setfill('0') << (fact % MOD) << "\n";
        return 0;
    }

    // For larger N, use same algorithm for verification
    vector<ll> pre(MOD + 1, 1);
    for (int i = 1; i <= MOD; i++) {
        pre[i] = pre[i-1];
        if (i % 2 != 0 && i % 5 != 0)
            pre[i] = (pre[i] * i) % MOD;
    }

    ll cnt2 = count_factors(N, 2);
    ll cnt5 = count_factors(N, 5);
    ll extra2 = cnt2 - cnt5;

    function<ll(ll)> Q = [&](ll n) -> ll {
        ll full = n / MOD;
        ll rem = n % MOD;
        ll res = mod_pow(pre[MOD], full);
        res = (res * pre[rem]) % MOD;
        return res;
    };

    map<ll, ll> memo;
    function<ll(ll)> P = [&](ll n) -> ll {
        if (n <= 1) return 1;
        if (memo.count(n)) return memo[n];
        ll res = Q(n);
        res = (res * P(n / 2)) % MOD;
        res = (res * P(n / 5)) % MOD;
        res = (res * mod_inv(P(n / 10))) % MOD;
        return memo[n] = res;
    };

    ll ans = P(N);
    ans = (ans * mod_pow(2, extra2)) % MOD;

    cout << setw(5) << setfill('0') << ans << "\n";
    return 0;
}
