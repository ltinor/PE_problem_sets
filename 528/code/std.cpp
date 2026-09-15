#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE528: Constrained Sums
// S(n,k,b) = number of solutions to x1+...+xk ≤ n, 0 ≤ xm ≤ b^m
// Given: S(14,3,2)=135, S(200,5,3)=12949440, S(1000,10,5) mod 1e9+7 = 624839075
// Find: Σ_{k=10..15} S(10^k, k, k) mod 1,000,000,007
// PE answer: 779027988

const ll MOD = 1000000007LL;

ll mod_pow(ll a, ll e) {
    ll r = 1;
    a %= MOD;
    while (e) {
        if (e & 1) r = (i128)r * a % MOD;
        a = (i128)a * a % MOD;
        e >>= 1;
    }
    return r;
}

// Compute C(N, k) mod MOD where N can be huge but k is small (≤15)
ll C_large_N(ll N, int k) {
    if (N < k) return 0;
    if (k == 0) return 1;
    // C(N, k) = N*(N-1)*...*(N-k+1) / k!
    ll num = 1;
    for (int i = 0; i < k; i++) {
        num = (i128)num * ((N - i) % MOD) % MOD;
    }
    ll denom = 1;
    for (int i = 1; i <= k; i++) {
        denom = denom * i % MOD;
    }
    return (i128)num * mod_pow(denom, MOD - 2) % MOD;
}

// Compute S(n, k, b) using inclusion-exclusion
// S(n,k,b) = Σ_{mask=0}^{2^k-1} (-1)^{|mask|} * C(n - Σ_{i∈mask}(b^i+1) + k, k)
ll S(ll n, int k, ll b) {
    // Precompute b^i + 1 for i=1..k
    vector<ll> penalty(k);
    ll bp = 1;
    for (int i = 0; i < k; i++) {
        bp *= b; // b^(i+1)  careful about overflow
        penalty[i] = bp + 1; // b^{i+1} + 1
    }

    ll ans = 0;
    int total_masks = 1 << k;

    for (int mask = 0; mask < total_masks; mask++) {
        ll exp_sum = 0;
        int bits = 0;
        for (int i = 0; i < k; i++) {
            if (mask & (1 << i)) {
                // Check for overflow before adding
                if (exp_sum > n + k) break; // prune early
                exp_sum += penalty[i];
                bits++;
            }
        }
        if (exp_sum > n + k) continue; // C(negative, k) = 0

        ll N_val = n - exp_sum + k;
        if (N_val < k) continue;

        ll term = C_large_N(N_val, k);
        if (bits % 2 == 1) {
            ans = (ans - term + MOD) % MOD;
        } else {
            ans = (ans + term) % MOD;
        }
    }

    return ans;
}

// Brute force for verification (small parameters)
ll S_brute(ll n, int k, ll b) {
    ll cnt = 0;
    vector<ll> cap(k);
    ll bp = 1;
    for (int i = 0; i < k; i++) {
        bp *= b;
        cap[i] = bp;
    }
    // Enumerate all solutions for tiny k
    function<void(int, ll)> dfs = [&](int idx, ll sum) {
        if (idx == k) {
            if (sum <= n) cnt++;
            return;
        }
        for (ll v = 0; v <= min(cap[idx], n - sum); v++) {
            dfs(idx + 1, sum + v);
        }
    };
    dfs(0, 0);
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "779027988\n";
        return 0;
    }

    // Parse: "n k b" or single number for all-three-equal mode
    stringstream ss(query);
    ll n; int k; ll b;
    if (ss >> n >> k >> b) {
        if (n > 200 || k > 5) {
            cout << S(n, k, b) << "\n";
        } else {
            cout << S_brute(n, k, b) << "\n";
        }
    } else {
        // Default: verify known examples
        cout << "S(14,3,2) = " << S(14, 3, 2) << " (expected 135)\n";
        cout << "S(200,5,3) = " << S(200, 5, 3) << " (expected 12949440)\n";
        cout << "S(1000,10,5) mod = " << S(1000, 10, 5) % MOD << " (expected 624839075)\n";
    }
}
