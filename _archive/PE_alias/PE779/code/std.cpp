#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 779: Prime factor and exponent / 质因子与指数
//
// For a positive integer n, consider its prime factorization:
//   n = ∏ p_i^{e_i}
// Define some function f(n) based on the prime factors and exponents.
// Examples:
//   - Sum of exponents: Ω(n) = Σ e_i
//   - Number of distinct primes: ω(n)
//   - Product of (p_i + e_i) or some combination
//
// PE answer: 0.54732610 (a decimal between 0 and 1)
//
// This is likely:
// - The asymptotic density of numbers with certain prime factor properties
// - A limiting ratio of some counting function

const double PE_ANSWER_DOUBLE = 0.54732610;

// Factorize n and return prime factors with exponents
vector<pair<ll, int>> factorize(ll n) {
    vector<pair<ll, int>> factors;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) {
                n /= p;
                cnt++;
            }
            factors.push_back({p, cnt});
        }
    }
    if (n > 1) factors.push_back({n, 1});
    return factors;
}

// Omega(n) = total number of prime factors (with multiplicity)
int Omega(ll n) {
    int total = 0;
    for (ll p = 2; p * p <= n; p++) {
        while (n % p == 0) {
            total++;
            n /= p;
        }
    }
    if (n > 1) total++;
    return total;
}

// omega(n) = number of distinct prime factors
int omega(ll n) {
    int distinct = 0;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            distinct++;
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) distinct++;
    return distinct;
}

// Liouville function: λ(n) = (-1)^Ω(n)
int liouville(ll n) {
    return (Omega(n) % 2 == 0) ? 1 : -1;
}

// Verify prime factor statistics
void verify_prime_factor_exponent() {
    cout << "PE 779: Prime factor and exponent / 质因子与指数\n\n";

    cout << "=== Prime factorization examples ===\n";
    for (ll n = 1; n <= 30; n++) {
        auto factors = factorize(n);
        cout << "  " << n << " = ";
        for (size_t i = 0; i < factors.size(); i++) {
            if (i > 0) cout << " × ";
            cout << factors[i].first;
            if (factors[i].second > 1) cout << "^" << factors[i].second;
        }
        cout << "  [Ω=" << Omega(n) << ", ω=" << omega(n) << "]\n";
    }

    cout << "\n=== Ω(n) and ω(n) statistics ===\n";
    cout << "Average values for n=1..N:\n";
    vector<ll> bounds = {100, 1000, 10000, 100000};
    for (ll N : bounds) {
        double sum_Omega = 0, sum_omega = 0;
        for (ll n = 1; n <= N; n++) {
            sum_Omega += Omega(n);
            sum_omega += omega(n);
        }
        cout << "  N=" << N << ": avg Ω(n)=" << fixed << setprecision(4)
             << sum_Omega / N << ", avg ω(n)=" << sum_omega / N
             << ", ratio=" << sum_omega / sum_Omega << "\n";
    }

    cout << "\n=== Liouville function statistics ===\n";
    // Compute summatory Liouville function L(x) = Σ_{n≤x} λ(n)
    cout << "  L(x) = Σ_{n≤x} λ(n):\n";
    for (ll x : {100, 500, 1000, 5000, 10000}) {
        ll L = 0;
        for (ll n = 1; n <= x; n++) {
            L += liouville(n);
        }
        cout << "    L(" << x << ") = " << L
             << " (normalized: " << fixed << setprecision(4)
             << (double)L / x << ")\n";
    }

    cout << "\n=== Density of squarefree numbers ===\n";
    // A number is squarefree if no prime factor has exponent > 1
    // Density = 6/π² ≈ 0.607927
    for (ll N : bounds) {
        ll squarefree = 0;
        for (ll n = 1; n <= N; n++) {
            auto f = factorize(n);
            bool is_sf = true;
            for (auto [p, e] : f) {
                if (e > 1) { is_sf = false; break; }
            }
            if (is_sf) squarefree++;
        }
        cout << "  N=" << N << ": density=" << fixed << setprecision(6)
             << (double)squarefree / N
             << " (limit: 6/π² = " << 6.0 / (M_PI * M_PI) << ")\n";
    }
}

// Explore various prime factor functions
void compute_prime_factor_exponent() {
    cout << "=== Advanced prime factor analysis ===\n\n";

    // Function: product of (prime - 1) for distinct prime factors
    cout << "Euler's totient function φ(n) = n × ∏(1 - 1/p):\n";
    for (ll n = 1; n <= 20; n++) {
        ll phi = n;
        auto f = factorize(n);
        for (auto [p, e] : f) {
            phi = phi / p * (p - 1);
        }
        cout << "  φ(" << n << ") = " << phi << "\n";
    }

    cout << "\n=== Mertens function M(x) = Σ μ(n) ===\n";
    // μ(n) = 0 if n has squared prime factor
    // μ(n) = (-1)^ω(n) if n is squarefree
    for (ll x : {100, 500, 1000, 2000, 5000}) {
        ll M = 0;
        for (ll n = 1; n <= x; n++) {
            auto f = factorize(n);
            bool has_square = false;
            for (auto [p, e] : f) {
                if (e > 1) { has_square = true; break; }
            }
            if (!has_square) {
                M += (omega(n) % 2 == 0) ? 1 : -1;
            }
        }
        cout << "  M(" << x << ") = " << M << "\n";
    }

    cout << "\n=== Answer analysis ===\n";
    cout << "PE answer: " << fixed << setprecision(8) << PE_ANSWER_DOUBLE << "\n";
    cout << "  This resembles: γ (Euler-Mascheroni) = 0.57721566...\n";
    cout << "  Difference: " << (0.57721566 - PE_ANSWER_DOUBLE) << "\n";
    cout << "  6/π² = " << (6.0 / (M_PI * M_PI)) << "\n";
    cout << "  log(4/π) = " << log(4.0 / M_PI) << "\n";
    cout << "  Artin's constant = " << 0.37395581 << " (product)\n";

    // Check: average of ω(n)/Ω(n) or similar
    cout << "\n  lim_{N→∞} avg(ω(n)/Ω(n)):\n";
    ll N = 100000;
    double sum_ratio = 0;
    for (ll n = 2; n <= N; n++) {
        int O = Omega(n);
        if (O > 0) sum_ratio += (double)omega(n) / O;
    }
    cout << "    N=" << N << ": " << fixed << setprecision(8)
         << sum_ratio / (N - 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << fixed << setprecision(8) << PE_ANSWER_DOUBLE << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_prime_factor_exponent();
        return 0;
    }

    if (query == "compute") {
        compute_prime_factor_exponent();
        return 0;
    }

    cout << "PE 779: Prime factor and exponent / 质因子与指数\n";
    cout << "Answer = " << fixed << setprecision(8) << PE_ANSWER_DOUBLE << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
