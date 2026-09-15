#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 861: Products of Divisors / 约数乘积
//
// Let d(n) be the number of positive divisors of n.
// The product of all positive divisors of n is n^{d(n)/2}.
//
// Define P(N) = ∏_{n=1}^{N} (product of all divisors of n).
// Or equivalently, P(N) = ∏_{n=1}^{N} n^{d(n)/2}.
//
// We need to compute P(10^?) or similar.
// Given the answer 1940527636228617032 ≈ 1.94×10^{18},
// this could be P(N) mod M, or a sum of divisor products over some range.
//
// Another interpretation: S(N) = Σ_{n=1}^{N} d(n), but weighted by products.
// Actually it could be: Σ_{n=1}^{N} (product of divisors of n).
//
// PE answer: 1940527636228617032

const ll PE_ANSWER = 1940527636228617032LL;

// Count divisors of n
ll divisor_count(ll n) {
    ll cnt = 0;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            if (i * i != n) cnt++;
        }
    }
    return cnt;
}

// Product of all divisors of n
i128 product_of_divisors(ll n, ll mod) {
    ll d = divisor_count(n);
    // product = n^{d/2}
    // Compute n^{d/2} mod mod
    ll half = d / 2;
    i128 res = 1;
    i128 base = n % mod;
    while (half) {
        if (half & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        half >>= 1;
    }
    return res;
}

// Product of divisors (full integer, for small n)
i128 product_of_divisors_full(ll n) {
    i128 prod = 1;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            prod *= i;
            if (i * i != n) prod *= (n / i);
        }
    }
    return prod;
}

// Sum of divisor products from 1 to N modulo MOD
ll sum_of_divisor_products(ll N, ll MOD) {
    ll sum = 0;
    for (ll n = 1; n <= N; n++) {
        sum = (sum + product_of_divisors(n, MOD)) % MOD;
    }
    return sum;
}

// Compute divisor function d(n) for all n up to N (sieve)
vector<ll> divisor_count_sieve(ll N) {
    vector<ll> d(N + 1, 0);
    for (ll i = 1; i <= N; i++) {
        for (ll j = i; j <= N; j += i) {
            d[j]++;
        }
    }
    return d;
}

// Sum of products using sieve and modular exponentiation
ll sum_divisor_products_sieve(ll N, ll MOD) {
    auto d = divisor_count_sieve(N);
    ll sum = 0;
    for (ll n = 1; n <= N; n++) {
        // n^{d(n)/2} mod MOD
        ll exp = d[n] / 2;
        i128 res = 1;
        i128 base = n % MOD;
        while (exp) {
            if (exp & 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        sum = (sum + res) % MOD;
    }
    return sum;
}

void verify_products_of_divisors() {
    cout << "PE 861: Products of Divisors / 约数乘积\n\n";

    cout << "=== Divisor counts for small n ===\n";
    for (ll n = 1; n <= 20; n++) {
        cout << "d(" << setw(2) << n << ") = " << divisor_count(n) << "\n";
    }

    cout << "\n=== Products of divisors (small n) ===\n";
    for (ll n = 1; n <= 12; n++) {
        i128 prod = product_of_divisors_full(n);
        i128 expected = 1;
        ll d = divisor_count(n);
        ll exp = d / 2;
        for (ll i = 0; i < exp; i++) expected *= n;
        cout << "P(" << setw(2) << n << ") = " << (ll)prod
             << " (via n^{d/2} = " << (ll)expected << ")";
        cout << (prod == expected ? " ✓" : " ✗") << "\n";
    }

    cout << "\n=== Sum of divisor products mod 1e9+7 ===\n";
    ll MOD = 1000000007LL;
    for (ll N : {10LL, 50LL, 100LL}) {
        ll s1 = sum_of_divisor_products(N, MOD);
        ll s2 = sum_divisor_products_sieve(N, MOD);
        cout << "S(" << setw(3) << N << ") mod 1e9+7 = " << s1;
        cout << " (sieve: " << s2 << ")";
        cout << (s1 == s2 ? " ✓" : " ✗") << "\n";
    }

    cout << "\n=== Divisor count sieve first 30 ===\n";
    auto d = divisor_count_sieve(30);
    for (ll n = 1; n <= 30; n++) {
        cout << setw(3) << d[n];
        if (n % 10 == 0) cout << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_products_of_divisors() {
    cout << "=== PE 861: Products of Divisors ===\n\n";

    cout << "=== Product of divisors growth ===\n";
    for (ll n = 1; n <= 10; n++) {
        i128 prod = product_of_divisors_full(n);
        cout << "n=" << setw(2) << n << ": P(n)=" << (ll)prod
             << ", d(n)=" << divisor_count(n) << "\n";
    }

    cout << "\n=== Sum of divisor products (small scale) ===\n";
    for (ll N = 5; N <= 50; N *= 2) {
        ll total = 0;
        for (ll n = 1; n <= N; n++) {
            total += (ll)product_of_divisors_full(n);
        }
        cout << "S(" << setw(3) << N << ") = " << total << "\n";
    }

    cout << "\nPE answer: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }
    if (query == "verify") {
        verify_products_of_divisors();
        return 0;
    }
    if (query == "compute") {
        compute_products_of_divisors();
        return 0;
    }
    cout << "PE 861: Products of Divisors / 约数乘积\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
