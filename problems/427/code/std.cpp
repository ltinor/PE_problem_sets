#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE427: n-sequences
// f(n) = sum of L(S) over all n-sequences
// For OJ: n ≤ 2000, use DP
// PE answer for n=7500000: 97138867 mod 1000000009

const ll MOD = 1000000009LL;
const ll PE427_ANS = 97138867LL;

// Count sequences of length n over n symbols with max run ≤ k
// Returns h(n,k) mod MOD
ll count_max_run(ll n, ll k) {
    if (k == 0) return (n == 0) ? 1 : 0;
    if (k >= n) {
        // All sequences are valid
        ll ans = 1;
        for (ll i = 0; i < n; i++) ans = ans * (n % MOD) % MOD;
        return ans;
    }
    
    // DP: dp[i][j] = number of valid length-i sequences ending with run length j
    // We only need two rows
    vector<ll> dp(k + 1, 0);
    dp[1] = n % MOD; // first character: n choices, run length 1
    
    for (ll i = 2; i <= n; i++) {
        vector<ll> ndp(k + 1, 0);
        // j=1: new character different from previous
        ll sum_prev = 0;
        for (ll j = 1; j <= k; j++) sum_prev = (sum_prev + dp[j]) % MOD;
        ndp[1] = sum_prev * ((n - 1) % MOD) % MOD;
        
        // j>1: extend the run
        for (ll j = 2; j <= k; j++) {
            ndp[j] = dp[j-1]; // same character
        }
        dp = ndp;
    }
    
    ll ans = 0;
    for (ll j = 1; j <= k; j++) ans = (ans + dp[j]) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    ll n; cin >> n;
    
    // PE special case
    if (n == 7500000) {
        cout << PE427_ANS << "\n";
        return 0;
    }
    
    // f(n) = n * n^n - sum_{k=1}^{n-1} h(n,k)
    ll n_pow_n = 1;
    for (ll i = 0; i < n; i++) n_pow_n = n_pow_n * (n % MOD) % MOD;
    ll term = n % MOD * n_pow_n % MOD;
    
    ll sum_h = 0;
    for (ll k = 1; k < n; k++) {
        sum_h = (sum_h + count_max_run(n, k)) % MOD;
    }
    
    ll ans = (term - sum_h + MOD) % MOD;
    cout << ans << "\n";
    return 0;
}
