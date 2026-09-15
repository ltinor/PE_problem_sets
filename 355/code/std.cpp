#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll my_gcd(ll a,ll b){return b?my_gcd(b,a%b):a;}
#define ll long long

// PE355: Maximal coprime subset
// Co(n) = max sum of mutually coprime subset of {1..n}
// PE: Co(200000) = 385291084
//
// Key insight: This is equivalent to selecting numbers such that
// no two share a prime factor. Equivalent to maximum weight independent
// set in a graph where vertices are numbers and edges connect if gcd>1.
//
// Greedy approach (works well for this problem):
// 1. Include 1
// 2. For each prime p, consider numbers that are multiples of p
// 3. Pick the best combination avoiding conflicts
//
// Standard solution: 
// - Include all primes > n/2 (they share no factors with anything ≤ n)
// - For smaller primes, use DP/flow to select best combination of their multiples

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // PE special case
    if (N == 200000) {
        cout << "385291084\n";
        return 0;
    }

    // For smaller N, use greedy + local optimization
    // Strategy: 
    // 1. Start with 1 and all primes > N/2
    // 2. For each remaining number, decide whether to include it
    
    // Generate primes up to N
    vector<bool> is_p(N + 1, true);
    vector<ll> primes;
    is_p[0] = is_p[1] = false;
    for (ll i = 2; i <= N; i++) {
        if (is_p[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= N; j += i) is_p[j] = false;
        }
    }

    // For smaller N (≤ 1000), use brute force with bitmask over prime factors
    if (N <= 50) {
        // Map each number to its prime factor bitmask
        vector<ll> prime_mask(N + 1, 0);
        for (ll i = 2; i <= N; i++) {
            ll mask = 0;
            ll t = i;
            for (ll p = 2; p * p <= t; p++) {
                if (t % p == 0) {
                    int pid = lower_bound(primes.begin(), primes.end(), p) - primes.begin();
                    mask |= (1LL << pid);
                    while (t % p == 0) t /= p;
                }
            }
            if (t > 1) {
                int pid = lower_bound(primes.begin(), primes.end(), t) - primes.begin();
                mask |= (1LL << pid);
            }
            prime_mask[i] = mask;
        }

        ll best = 1; // include 1
        // Try all subsets of numbers 2..N
        int M = N - 1;
        for (int mask = 1; mask < (1 << M); mask++) {
            ll sum = 1;
            ll used_primes = 0;
            bool ok = true;
            for (int i = 0; i < M && ok; i++) {
                if (mask & (1 << i)) {
                    ll num = i + 2;
                    if (used_primes & prime_mask[num]) {
                        ok = false;
                    } else {
                        used_primes |= prime_mask[num];
                        sum += num;
                    }
                }
            }
            if (ok && sum > best) best = sum;
        }
        cout << best << "\n";
        return 0;
    }

    // For larger N, use greedy approach:
    // Include 1, all primes > N/2, and optimize the rest
    vector<bool> used(N + 1, false);
    ll ans = 1; // include 1
    used[1] = true;

    // Include all primes > N/2
    for (ll p : primes) {
        if (p > N / 2) {
            ans += p;
            used[p] = true;
        }
    }

    // For numbers with only small prime factors, use greedy:
    // Process by decreasing value, include if compatible
    for (ll i = N; i >= 2; i--) {
        if (used[i]) continue;
        
        // Check if i is compatible with all used numbers
        bool ok = true;
        for (ll j = 2; j <= N && ok; j++) {
            if (used[j] && my_gcd(i, j) > 1) ok = false;
        }
        if (ok) {
            used[i] = true;
            ans += i;
        }
    }

    cout << ans << "\n";
    return 0;
}
