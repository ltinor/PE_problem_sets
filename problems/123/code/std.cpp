#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// Generate primes up to some limit using sieve
vector<int> gen_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (long long j = 1LL * i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ull T;
    cin >> T;

    // Need primes for T up to 1e12: n ~ 210000, p_n ~ 3e6
    // Generate primes up to 5000000 for safety
    vector<int> primes = gen_primes(5000000);

    // Check odd n only: r = 2 * n * p_n mod p_n^2
    // For the range we care about, 2*n*p_n < p_n^2 for all relevant n
    // Actually we need 2*n*p_n > p_n^2 for some n, then r = 2*n*p_n
    // For large enough n, 2*n*p_n mod p_n^2 = 2*n*p_n (since 2*n < p_n)
    // Actually r = 2*n*p_n mod p_n^2. If 2*n*p_n < p_n^2, then r = 2*n*p_n.
    // For p_n ~ n log n, p_n^2 ~ n^2 log^2 n, 2*n*p_n ~ 2 n^2 log n
    // So p_n^2 / (2*n*p_n) = p_n/(2n) ~ log n / 2
    // For n = 7000, log n ≈ 8.85, ratio ≈ 4.4 > 1, so r = 2*n*p_n
    // For n = 21035, log n ≈ 9.95, ratio ≈ 5.0, so r = 2*n*p_n still < p_n^2
    // Actually, p_n for n=21035 is ~ 237673 (since 21035th prime ≈ 237k)
    // 2*n*p_n = 2*21035*237673 ≈ 1e10 exactly
    // p_n^2 ≈ 5.65e10, so ratio ≈ 5.65, r = 2*n*p_n

    for (int n = 1; n <= (int)primes.size(); n++) {
        if (n % 2 == 0) continue; // even n: r = 2 (always ≤ 2, never > T for T > 2)
        ull p = primes[n - 1]; // p_n (0-indexed)
        ull r = 2ULL * n * p;
        // Check if r >= p*p. If so, r = 2*n*p mod p^2 = 2*n*p - p^2
        ull p2 = p * p;
        if (r >= p2) {
            r = r % p2;
        }
        if (r > T) {
            cout << n << "\n";
            return 0;
        }
    }

    return 0;
}
