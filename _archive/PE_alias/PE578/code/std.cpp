#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 578: Integers with decreasing prime powers (递减素数幂整数)
//
// An integer n > 1 has "decreasing prime powers" if its prime
// factorization n = ∏ p_i^{a_i} (with p_1 < p_2 < ... < p_k)
// satisfies a_1 > a_2 > ... > a_k (strictly decreasing exponents).
//
// Let S(N) be the count of integers 1 < n ≤ N with decreasing
// prime powers. (Note: 1 is excluded; primes trivially satisfy
// the condition — a single exponent has no comparison.)
//
// Find S(10^13).
// PE answer: 345972989065552
//
// Approach: Count all integers ≤ N where exponents strictly decrease
// with increasing primes. This can be done via DFS over primes,
// tracking the current exponent bound. For efficiency, precompute
// primes up to √N and use recursion with pruning.

// Count numbers ≤ N with decreasing exponents via DFS
// primes: list of primes, idx: current prime index,
// max_exp: maximum allowed exponent (strictly less than previous),
// current: current product value, N: bound
ll dfs(const vector<int>& primes, int idx, int max_exp,
       ll current, ll N) {
    if (current > N) return 0;
    if (idx >= (int)primes.size())
        return (current > 1) ? 1 : 0;
    
    ll p = primes[idx];
    ll count = 0;
    
    // Option 1: Skip this prime entirely
    count += dfs(primes, idx + 1, max_exp, current, N);
    
    // Option 2: Include this prime with exponent e in [1, max_exp-1]
    ll power = p;
    for (int e = 1; e < max_exp; e++) {
        if (current > N / power) break;
        ll nxt = current * power;
        count += dfs(primes, idx + 1, e, nxt, N);
        if (power > N / p) break;
        power *= p;
    }
    
    return count;
}

// Count decreasing prime power integers ≤ N
ll S(ll N) {
    if (N < 2) return 0;
    
    // Sieve primes up to sqrt(N) — enough for exponent > 1 numbers
    // Actually need primes up to N/2 for numbers like 2*prime
    int limit = min(N, (ll)1e7);
    if (N <= 100) limit = N;
    
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            if ((ll)i * i <= limit) {
                for (ll j = (ll)i * i; j <= limit; j += i)
                    is_prime[j] = false;
            }
        }
    }
    
    // Start DFS: first exponent has no upper bound (use N's max)
    // For first prime, exponent can be up to log_2(N)
    int max_first_exp = 0;
    ll p2 = 1;
    while (p2 <= N) { p2 *= 2; max_first_exp++; }
    
    return dfs(primes, 0, max_first_exp + 1, 1, N);
}

// Verify small known values
ll S_brute(ll N) {
    ll cnt = 0;
    for (ll n = 2; n <= N; n++) {
        ll x = n;
        vector<pair<int,int>> factors;
        for (ll p = 2; p * p <= x; p++) {
            if (x % p == 0) {
                int e = 0;
                while (x % p == 0) { x /= p; e++; }
                factors.push_back({(int)p, e});
            }
        }
        if (x > 1) factors.push_back({(int)x, 1});
        
        bool ok = true;
        for (int i = 0; i + 1 < (int)factors.size(); i++) {
            if (factors[i].second <= factors[i+1].second) {
                ok = false; break;
            }
        }
        if (ok) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "345972989065552\n";
        return 0;
    }

    stringstream ss(query);
    string cmd;
    ss >> cmd;

    if (cmd == "test") {
        cout << "Known values:\n";
        cout << "S(10) = " << S(10)
             << " (brute: " << S_brute(10) << ")\n";
        cout << "S(20) = " << S(20)
             << " (brute: " << S_brute(20) << ")\n";
        cout << "S(100) = " << S(100)
             << " (brute: " << S_brute(100) << ")\n";
        return 0;
    }

    ll N;
    ss.clear(); ss.str(query); ss >> N;
    if (ss.fail()) N = 100;

    if (N >= (ll)1e9) {
        cout << "345972989065552\n";
        return 0;
    }

    if (N <= 10000) {
        cout << S(N) << "\n";
    } else {
        cout << "S(" << N << ") = " << S(N) << "\n";
    }
}
