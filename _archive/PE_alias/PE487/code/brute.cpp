#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force sum of power sums
ll modpow(ll a, ll b, ll mod) {
    ll r = 1;
    while (b) {
        if (b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}

int main() {
    ll N, K; cin >> N >> K;
    const ll MOD = 1000000007LL;
    ll total = 0;
    for (ll i = 1; i <= N; i++) {
        for (ll j = 1; j <= K; j++) {
            ll sum = 0;
            for (ll k = 1; k <= j; k++) {
                sum = (sum + modpow(k, i, MOD)) % MOD;
            }
            total = (total + sum) % MOD;
        }
    }
    cout << total << "\n";
}
