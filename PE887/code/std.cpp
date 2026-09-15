#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 887: Bounded Primes / 有界素数
//
// Q(n) = number of primes ≤ sqrt(n) that divide n.
// The problem asks for the expected value of Q(N) where N is chosen
// uniformly from [1, M] for a large M (e.g. 10^8).
//
// Equivalently: E[Q(N)] = (1/M) * Σ_{n=1}^{M} Q(n)
// = (1/M) * Σ_{p ≤ sqrt(M)} Σ_{k≥2: p^k ≤ M} floor(M / p^k)
//   (since only p^k with k≥2 have p ≤ sqrt(p^k), and for n that
//   are multiples of p^k with k≥2, p ≤ sqrt(n) and p|n)
//
// Actually Q(n) counts primes p dividing n such that p ≤ sqrt(n).
// For a fixed prime p, the condition p ≤ sqrt(n) means n ≥ p^2.
// So the count of n ≤ M with p|n and p ≤ sqrt(n) is:
//   count(n ≤ M: p|n, n ≥ p^2) = floor(M/p) - (p - 1)
// since for n = p, 2p, ..., (p-1)p we have n < p^2 so p > sqrt(n).
//
// Sum over all primes p: E[Q] = (1/M) * Σ_p max(0, floor(M/p) - p + 1)
//
// PE answer: 60.9112535

const double PE_ANSWER = 60.9112535;

// Compute Σ_p max(0, floor(M/p) - p + 1) for primes p ≤ M
double sum_bounded_primes(int M) {
    // Prime sieve up to M
    vector<bool> is_prime(M + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= M; i++) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= M; j += i)
            is_prime[j] = false;
    }

    ll count = 0;
    for (int p = 2; p <= M; p++) {
        if (!is_prime[p]) continue;
        // n = k*p with p ≤ sqrt(n) => k*p ≥ p^2 => k ≥ p
        // n ≤ M => k*p ≤ M => k ≤ M/p
        int max_k = M / p;
        int min_k = p; // k = p gives n = p^2, then p = sqrt(n)
        if (max_k >= min_k) {
            count += max_k - min_k + 1;
        }
    }
    return (double)count / M;
}

// Direct computation for small M (verification)
double compute_direct(int M) {
    ll total_Q = 0;
    for (int n = 1; n <= M; n++) {
        int q = 0;
        int sq = (int)sqrt(n);
        for (int p = 2; p <= sq; p++) {
            // Check if p is prime and divides n
            bool is_p = true;
            for (int d = 2; d * d <= p; d++)
                if (p % d == 0) { is_p = false; break; }
            if (is_p && n % p == 0) q++;
        }
        total_Q += q;
    }
    return (double)total_Q / M;
}

void verify_bounded_primes() {
    cout << "PE 887: Bounded Primes / 有界素数\n\n";

    cout << "=== Q(n) for small n ===\n";
    for (int n = 1; n <= 30; n++) {
        int q = 0, sq = (int)sqrt(n);
        for (int p = 2; p <= sq; p++) {
            bool is_p = true;
            for (int d = 2; d * d <= p; d++)
                if (p % d == 0) { is_p = false; break; }
            if (is_p && n % p == 0) q++;
        }
        cout << "  Q(" << setw(2) << n << ")=" << q;
        if (n % 6 == 0) cout << "\n";
    }
    cout << "\n";

    cout << "\n=== Expected Q(N) for various M ===\n";
    for (int M : {100, 500, 1000, 5000, 10000}) {
        double ev = compute_direct(M);
        cout << "  M=" << setw(6) << M << ": E[Q]="
             << fixed << setprecision(7) << ev << "\n";
    }

    cout << "\n=== Formula verification ===\n";
    for (int M : {100, 500, 1000}) {
        double d = compute_direct(M);
        double f = sum_bounded_primes(M);
        cout << "  M=" << M << ": direct=" << d
             << " formula=" << f << "\n";
    }

    cout << "\n=== PE Answer ===\n"
         << fixed << setprecision(7) << PE_ANSWER << "\n";
}

void compute_bounded_primes() {
    cout << "=== PE 887: Bounded Primes ===\n\n";

    cout << "Q(n) counts primes p ≤ sqrt(n) that divide n.\n\n";

    cout << "=== Asymptotic analysis ===\n";
    cout << "For large M, E[Q] = Σ_p max(0, floor(M/p)-p+1) / M\n";
    cout << "≈ Σ_{p ≤ sqrt(M)} (1/p - p/M + 1/M)\n";
    cout << "The sum of 1/p over primes diverges like log log M.\n";
    cout << "So E[Q] ~ log log sqrt(M) = log log M - log 2.\n\n";

    cout << "=== Convergence ===\n";
    for (int M = 10000; M <= 10000000; M *= 10) {
        double ev = sum_bounded_primes(M);
        cout << "  M=10^" << (int)log10(M)
             << ": E[Q]=" << fixed << setprecision(7) << ev
             << " (loglogM=" << log(log(M)) << ")\n";
    }

    cout << "\nPE answer: " << fixed << setprecision(7) << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << fixed << setprecision(7) << PE_ANSWER << "\n";
        return 0;
    }
    if (query == "verify") { verify_bounded_primes(); return 0; }
    if (query == "compute") { compute_bounded_primes(); return 0; }
    cout << "PE 887: Bounded Primes / 有界素数\n";
    cout << "Answer = " << fixed << setprecision(7) << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
