#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 160: Factorial Trailing Digits - Last 5 non-zero digits of N!
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

// Extended Euclidean for modular inverse (MOD is not prime: 2^5 * 5^5)
// But P(N/10) is coprime to 10, hence coprime to MOD
ll mod_inv(ll a) {
    // a and MOD are coprime since a is not divisible by 2 or 5
    ll m = MOD;
    ll x0 = 1, x1 = 0;
    while (a > 1) {
        ll q = a / m;
        ll t = m;
        m = a % m;
        a = t;
        t = x1;
        x1 = x0 - q * x1;
        x0 = t;
    }
    if (x0 < 0) x0 += MOD;
    return x0;
}

// Count factors of p in N!
ll count_factors(ll N, ll p) {
    ll cnt = 0;
    for (ll x = p; x <= N; x *= p) cnt += N / x;
    return cnt;
}

// Q(N) = product of numbers 1..N with gcd(i,10)=1 (odd and not div by 5), mod MOD
ll Q(ll N, const vector<ll>& pre) {
    ll period_prod = pre[MOD];
    ll full = N / MOD;
    ll rem = N % MOD;
    ll res = mod_pow(period_prod, full);
    res = (res * pre[rem]) % MOD;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    if (N <= 1) { cout << "00001\n"; return 0; }

    // Precompute prefix products of numbers coprime to 10 up to MOD
    vector<ll> pre(MOD + 1, 1);
    for (int i = 1; i <= MOD; i++) {
        pre[i] = pre[i-1];
        if (i % 2 != 0 && i % 5 != 0) {
            pre[i] = (pre[i] * i) % MOD;
        }
    }

    // Count factors of 2 and 5
    ll cnt2 = count_factors(N, 2);
    ll cnt5 = count_factors(N, 5);
    ll extra2 = cnt2 - cnt5;

    // Compute P(N) = product of all numbers 1..N after removing 2s and 5s
    // P(N) = Q(N) * P(N/2) * P(N/5) / P(N/10)
    // We'll compute bottom-up with memoization or top-down recursion
    // Use a map for memoization since N can be up to 10^12 but recursion depth is log(N)
    
    map<ll, ll> memo;
    function<ll(ll)> P = [&](ll n) -> ll {
        if (n <= 1) return 1;
        if (memo.count(n)) return memo[n];
        
        ll res = Q(n, pre);
        res = (res * P(n / 2)) % MOD;
        res = (res * P(n / 5)) % MOD;
        // Divide by P(n/10) using modular inverse
        ll p10 = P(n / 10);
        // p10 is coprime to 10, hence coprime to MOD
        res = (res * mod_inv(p10)) % MOD;
        
        return memo[n] = res;
    };

    ll ans = P(N);
    ans = (ans * mod_pow(2, extra2)) % MOD;

    cout << setw(5) << setfill('0') << ans << "\n";
    return 0;
}
