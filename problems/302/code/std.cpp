#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Check if n is a perfect power (n = m^k, k >= 2)
bool is_perfect_power(ll n) {
    if (n <= 1) return true;
    for (int k = 2; k <= 60; k++) {
        // binary search for m such that m^k = n
        ll lo = 1, hi = (ll)pow(n, 1.0/k) + 2;
        while (lo <= hi) {
            ll mid = lo + (hi - lo) / 2;
            // compute mid^k carefully
            ll p = 1;
            bool overflow = false;
            for (int i = 0; i < k; i++) {
                if (p > n / mid) { overflow = true; break; }
                p *= mid;
            }
            if (!overflow && p == n) return true;
            if (overflow || p > n) hi = mid - 1;
            else lo = mid + 1;
        }
    }
    return false;
}

// Check if n is powerful: for each prime p|n, p^2|n
bool is_powerful(ll n) {
    if (n <= 1) return false;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) { n /= p; cnt++; }
            if (cnt < 2) return false;
        }
    }
    if (n > 1) return false; // remaining prime factor has exponent 1
    return true;
}

// Compute phi(n) using factorization
ll phi(ll n) {
    ll result = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// Check if n is Achilles: powerful but not perfect power
bool is_achilles(ll n) {
    if (n <= 1) return false;
    if (!is_powerful(n)) return false;
    if (is_perfect_power(n)) return false;
    return true;
}

// Check if n is Strong Achilles: n and phi(n) both Achilles
bool is_strong_achilles(ll n) {
    if (!is_achilles(n)) return false;
    return is_achilles(phi(n));
}

// Generate all powerful numbers <= limit
vector<ll> generate_powerful(ll limit) {
    vector<ll> res;
    // Use a^2 * b^3 representation, b squarefree
    ll max_a = (ll)sqrt(limit) + 1;
    for (ll a = 1; a <= max_a; a++) {
        ll a2 = a * a;
        if (a2 > limit) break;
        // Determine max b such that a2 * b^3 <= limit
        ll max_b = (ll)cbrt((double)limit / a2) + 2;
        // Actually b should be squarefree, but for simplicity we generate all b
        // and use a set to deduplicate
        for (ll b = 1; b <= max_b; b++) {
            ll b3 = b * b * b;
            if (b3 > limit / a2) break;
            ll val = a2 * b3;
            if (val <= limit) res.push_back(val);
        }
    }
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Generate powerful numbers and check
    auto powerful = generate_powerful(N);

    ll ans = 0;
    for (ll n : powerful) {
        if (is_strong_achilles(n)) {
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
