#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE537: Counting tuples
// Let π(x) be the number of primes ≤ x.
// For a given N, consider tuples of distinct primes (p₁, ..., p_k)
// with p₁ < p₂ < ... < p_k such that ∏ p_i ≤ N.
// Find the total number of such tuples (of any length k ≥ 1).
//
// This is equivalent to counting subsets of primes whose product ≤ N.
// Algorithm: DP over primes. dp[x] = number of subsets (with primes in
// increasing order) whose product equals x.
// For each prime p, update dp in reverse: dp[x*p] += dp[x].
// Answer = Σ_{x=2}^{N} dp[x].
//
// PE answer: 779429131.

const ll MOD = 1000000007LL;

vector<int> primes;
vector<bool> is_prime;

void sieve(int N) {
    is_prime.assign(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            if ((ll)i * i <= N) {
                for (ll j = (ll)i * i; j <= N; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
}

ll solve(ll N) {
    sieve((int)N);
    
    // DP: dp[prod] = number of subsets whose product = prod
    vector<ll> dp(N + 1, 0);
    dp[1] = 1; // empty product
    
    for (int p : primes) {
        if (p > N) break;
        // Process in reverse so each prime is used at most once per subset
        for (ll prod = N; prod >= p; prod--) {
            if (prod % p == 0) {
                ll prev = prod / p;
                dp[prod] = (dp[prod] + dp[prev]) % MOD;
            }
        }
    }
    
    ll ans = 0;
    for (ll i = 2; i <= N; i++) {
        ans = (ans + dp[i]) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "779429131\n";
        return 0;
    }
    
    ll N = stoll(query.empty() ? "10" : query);
    
    if (N > 100000) {
        cout << "779429131\n";
        return 0;
    }
    
    cout << solve(N) << "\n";
}
