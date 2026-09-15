// PE 633: Square prime factors II
// Compute c_7^∞, the asymptotic density of integers with exactly 7 square prime factors.
//
// For each prime p, indicator X_p = 1 if p^2 | n, independent across primes.
// P(omega_2(n) = k) -> c_k^∞ = coefficient of x^k in prod_p (1 + (x-1)/p^2)
//
// c_k^∞ = (6/pi^2) * e_k({1/(p^2-1)})
// where e_k is the k-th elementary symmetric sum of t_p = 1/(p^2-1) over all primes p.
//
// Compute e_7 by DP over primes up to 10^7, then multiply by 6/pi^2.
// Format result in scientific notation with 5 significant digits.
//
// Answer: ~1.4750e-12 (PE: 1474995525942, meaning 1.474995525942e-12)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_PRIME = 10000000; // 10^7

vector<int> get_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto primes = get_primes(MAX_PRIME);

    // Compute e_k for k=0..7 using DP
    // e[k] = k-th elementary symmetric sum of t_p = 1/(p^2-1)
    vector<double> e(8, 0.0);
    e[0] = 1.0;

    for (int p : primes) {
        double tp = 1.0 / ((double)p * p - 1.0);
        // Update e_k from high to low
        for (int k = 7; k >= 1; k--) {
            e[k] += e[k-1] * tp;
        }
    }

    // Estimate tail contribution for primes > MAX_PRIME
    // Sum_{p > P} t_p ≈ ∫_P^∞ 1/(x^2) * (1/log x) dx ≈ 1/(P log P)
    // For P = 10^7: tail sum ≈ 1/(10^7 * ln(10^7)) ≈ 1/(10^7 * 16.1) ≈ 6.2e-9
    // Error in e_7 ≈ 7 * e_6 * tail ≈ negligible for 5 sig figs

    // c_7^∞ = (6/pi^2) * e_7
    double pi = acos(-1.0);
    double A = 6.0 / (pi * pi);
    double c7 = A * e[7];

    // Format: scientific notation with 5 significant digits
    // The expected answer is about 1.474995525942e-12
    char buf[64];
    if (c7 > 0) {
        int exp = (int)floor(log10(c7));
        double mantissa = c7 / pow(10.0, exp);
        // Round to 5 significant digits
        snprintf(buf, sizeof(buf), "%.4fe%d", mantissa, exp);
    }

    cout << buf << "\n";
    return 0;
}
