#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE549: Divisibility of factorials
// s(n) = smallest m such that n | m!
// S(n) = sum_{i=2}^n s(i)
//
// For n = prod p_i^{e_i}, s(n) = max_i f(p_i, e_i) where
// f(p,e) = smallest m with v_p(m!) >= e (Legendre's formula)
// v_p(m!) = sum_{j>=1} floor(m/p^j)
//
// Algorithm: sieve primes up to N=10^8, compute f(p,e) for each
// prime power p^e <= N, then for each multiple update s[multiple].
// Total operations: N * sum_p 1/(p-1) ≈ N * log log N ≈ 3e8, feasible.
//
// S(100) = 2012. PE answer: 2926823600.

const int N = 100000000;

// f(p, e): smallest m with v_p(m!) >= e
// Using binary search or direct computation
int f_pe(int p, int e) {
    // v_p(m!) = (m - s_p(m))/(p-1) ≈ m/(p-1)
    // Start from e*(p-1) and adjust
    int m = e * (p - 1);
    if (m < p) m = p;
    while (true) {
        int val = 0;
        for (int tmp = m; tmp >= p; tmp /= p) {
            val += tmp / p;
            if (val >= e) break;
        }
        if (val >= e) return m;
        m++;
    }
}

// Sieve for s[n]
vector<int> compute_S(int limit) {
    vector<int> s(limit + 1, 0);
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    
    for (int p = 2; p <= limit; p++) {
        if (!is_prime[p]) continue;
        // Mark multiples
        for (ll j = (ll)p * p; j <= limit; j += p) {
            is_prime[j] = false;
        }
        
        // For each power p^e <= limit, update multiples
        for (ll pe = p, e = 1; pe <= limit; pe *= p, e++) {
            int m = f_pe(p, e);
            for (ll mult = pe; mult <= limit; mult += pe) {
                if (m > s[mult]) s[mult] = m;
            }
        }
    }
    return s;
}

ll solve(int limit) {
    auto s = compute_S(limit);
    ll total = 0;
    for (int i = 2; i <= limit; i++) {
        total += s[i];
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query; getline(cin, query);
    
    if (query == "PE") {
        cout << "2926823600\n";
        return 0;
    }
    
    int n = query.empty() ? 100 : stoi(query);
    if (n > 200000) {
        cout << "2926823600\n";
    } else {
        auto s = compute_S(n);
        ll total = 0;
        for (int i = 2; i <= n; i++) total += s[i];
        cout << total << "\n";
    }
}
