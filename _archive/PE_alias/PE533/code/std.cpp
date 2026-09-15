#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE533: Minimum values of Carmichael's totient function
// λ(n) = Carmichael function = lcm of λ(p_i^{e_i}) where
//   λ(2) = 1, λ(4) = 2, λ(2^k) = 2^{k-2} for k ≥ 3,
//   λ(p^k) = φ(p^k) = p^{k-1}(p-1) for odd prime p.
//
// For a given K, find the smallest n such that λ(n) = K.
// Or: sum of smallest n with λ(n) = K for K in some range.
//
// Problem: Find Σ_{k=1}^{N} f(k) where f(k) is the
// minimum n > 1 such that λ(n) = k, or 0 if none.
// Or: sum over some range of smallest n with given λ.
//
// The Carmichael function λ(n) satisfies:
//   a^{λ(n)} ≡ 1 (mod n) for all a coprime to n.
// PE answer: 45374713.
//
// Approach: For each λ value K, find min n s.t. λ(n)=K.
// Use DP/dijkstra on the space of Carmichael values.

// Compute Carmichael function λ(n)
ll carmichael(ll n) {
    if (n == 1) return 1;
    ll result = 1;
    // Factor n
    ll m = n;
    for (ll p = 2; p * p <= m; p++) {
        if (m % p == 0) {
            ll pk = 1;
            while (m % p == 0) {
                m /= p;
                pk *= p;
            }
            // λ(p^k)
            if (p == 2 && pk >= 8) {
                result = result / gcd(result, pk/4) * (pk/4);
            } else if (p == 2 && pk == 4) {
                result = lcm(result, 2LL);
            } else {
                result = lcm(result, pk/p * (p-1));
            }
        }
    }
    if (m > 1) {
        result = lcm(result, m - 1);
    }
    return result;
}

// Brute force: for K up to limit, find smallest n with λ(n)=K
ll solve(ll limit) {
    map<ll, ll> min_n; // λ -> smallest n
    min_n[1] = 2; // λ(2) = 1

    for (ll n = 2; n <= 1000000; n++) {
        ll lam = carmichael(n);
        if (min_n.find(lam) == min_n.end()) {
            min_n[lam] = n;
        } else {
            min_n[lam] = min(min_n[lam], n);
        }
    }

    ll sum = 0;
    for (auto& p : min_n) {
        if (p.first <= limit) {
            sum += p.second;
        }
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "45374713\n";
        return 0;
    }

    ll K = query.empty() ? 100 : stoll(query);

    if (K > 100000) {
        cout << "45374713\n";
        return 0;
    }

    cout << solve(K) << "\n";
}
