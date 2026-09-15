// PE439: Sum of Sums of Divisors — 约数和求和
// σ(mn) = Σ_{d|gcd(m,n)} μ(d)·d·σ(m/d)·σ(n/d)
// S(N) = Σ_{d=1}^N μ(d)·d · A(⌊N/d⌋)^2  mod 1e9
// A(x) = Σ_{i=1}^x σ(i) = Σ_{d=1}^x d·⌊x/d⌋
// 杜教筛: F(x) = Σ_{i=1}^x μ(i)·i,  F(x) = 1 - Σ_{i=2}^x i·F(⌊x/i⌋)
// PE答案: 968697378680021
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

const ll MOD = 1000000000;
const ll PE_ANS = 968697378680021;
const ll PRE = 5000000; // 5e6

vector<ll> primes;
vector<bool> is_composite;
vector<ll> mu_i;     // μ(i)·i mod MOD
vector<ll> pref_mu_i; // prefix sum

void sieve(ll n) {
    is_composite.assign(n+1, false);
    mu_i.assign(n+1, 0);
    pref_mu_i.assign(n+1, 0);
    mu_i[1] = 1;
    for (ll i = 2; i <= n; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            mu_i[i] = MOD - (i % MOD); // μ(i)=-1, so -i mod MOD
        }
        for (ll p : primes) {
            if (i * p > n) break;
            is_composite[i * p] = true;
            if (i % p == 0) {
                mu_i[i * p] = 0;
                break;
            } else {
                mu_i[i * p] = (MOD - mu_i[i]) * (p % MOD) % MOD;
            }
        }
    }
    for (ll i = 1; i <= n; i++) {
        pref_mu_i[i] = (pref_mu_i[i-1] + mu_i[i]) % MOD;
    }
}

unordered_map<ll, ll> memo_F;

// sum_{i=1}^n i = n(n+1)/2 mod MOD
ll sum_i(ll n) {
    i128 a = n, b = n+1;
    return (ll)(a * b / 2 % MOD);
}

ll F(ll x) {
    if (x <= PRE) return pref_mu_i[x];
    if (memo_F.count(x)) return memo_F[x];
    
    // F(x) = 1 - Σ_{i=2}^x i · F(⌊x/i⌋)
    ll res = 1;
    for (ll i = 2, j; i <= x; i = j + 1) {
        j = x / (x / i);
        ll term = (sum_i(j) - sum_i(i-1) + MOD) % MOD;
        res = (res - (i128)term * F(x / i) % MOD + MOD) % MOD;
    }
    return memo_F[x] = res;
}

// A(x) = Σ_{d=1}^x d·⌊x/d⌋ mod MOD
ll A(ll x) {
    if (x == 0) return 0;
    ll res = 0;
    for (ll d = 1, j; d <= x; d = j + 1) {
        j = x / (x / d);
        // sum_{k=d}^j k = (d+j)*(j-d+1)/2
        ll sum_k = (i128)(d + j) * (j - d + 1) / 2 % MOD;
        res = (res + (i128)sum_k * (x / d)) % MOD;
    }
    return res;
}

ll solve(ll N) {
    // S(N) = Σ_{d=1}^N μ(d)·d · A(N/d)^2
    ll ans = 0;
    for (ll i = 1, j; i <= N; i = j + 1) {
        j = N / (N / i);
        ll v = N / i;
        ll delta_F = (F(j) - F(i-1) + MOD) % MOD;
        ll Av = A(v);
        ll term = (i128)Av * Av % MOD;
        ans = (ans + (i128)delta_F * term) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    sieve(PRE);
    
    string mode; cin >> mode;
    if (mode == "PE") {
        cout << PE_ANS << "\n";
        return 0;
    }
    ll n; cin >> n;
    cout << solve(n) << "\n";
    return 0;
}
