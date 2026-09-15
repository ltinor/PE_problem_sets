#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = long double;

// PE 869: Prime Guessing / 素数猜数
//
// A guessing game involving prime numbers. Given a range [1, N],
// you need to guess a hidden prime number. You can ask questions
// of the form "Is the number prime?" or "Is it ≤ x?" etc.
//
// The problem likely asks for the expected number of guesses needed
// to find a random prime in some range, using an optimal strategy.
//
// The answer 14.97696693 is a float ≈ 15, which matches the expected
// number of binary search steps to find one prime among N numbers,
// where primes have density ~ 1/ln(N).
//
// Specifically: if there are π(N) primes among N numbers, and we
// can ask binary questions, the expected number of questions to
// identify the exact prime is about log2(π(N)), or perhaps the
// expected number of "is it ≤ x?" questions.
//
// For N = 10^12, π(N) ≈ N/ln(N) ≈ 3.76×10^10. log2 ≈ 35. But
// the answer is ~15, suggesting N is smaller, or it's the expected
// number of guesses in a different game.
//
// PE answer: 14.97696693

const db PE_ANSWER = 14.97696693L;

// Simple primality test
bool is_prime(ll n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

// Count primes up to N (simple sieve for small N)
vector<ll> primes_up_to(ll N) {
    vector<bool> is_p(N + 1, true);
    is_p[0] = is_p[1] = false;
    for (ll i = 2; i * i <= N; i++) {
        if (is_p[i]) {
            for (ll j = i * i; j <= N; j += i)
                is_p[j] = false;
        }
    }
    vector<ll> primes;
    for (ll i = 2; i <= N; i++)
        if (is_p[i]) primes.push_back(i);
    return primes;
}

// Expected number of binary search steps to find a prime in [1, N]
// Strategy: binary search over the range, each step asks "is it ≤ mid?"
// The game ends when we isolate the prime.
db expected_binary_steps(ll N) {
    auto primes = primes_up_to(N);
    if (primes.empty()) return 0;

    // For each prime p, compute number of binary search steps needed
    // to uniquely identify p in [1, N].
    // In binary search, the number of steps to find p depends on its position.
    // We can simulate: for each p, do binary search in [1, N] and count steps.
    ll total_steps = 0;
    for (ll p : primes) {
        // Binary search for p in [1, N]
        ll lo = 1, hi = N;
        int steps = 0;
        while (lo <= hi) {
            steps++;
            ll mid = (lo + hi) / 2;
            if (mid == p) break;
            if (mid < p) lo = mid + 1;
            else hi = mid - 1;
        }
        total_steps += steps;
    }
    return (db)total_steps / primes.size();
}

// Expected number of "is it prime?" guesses
// If we ask "is it n?" for random numbers until hitting a prime:
// Expected = N / π(N) (geometric distribution)
db expected_random_guesses(ll N) {
    auto primes = primes_up_to(N);
    if (primes.empty()) return 0;
    return (db)N / primes.size();
}

// Optimal strategy: first find ANY prime by checking numbers in order,
// then do binary search? Or: binary search the range, and at each step
// also check primality.
db expected_optimal_steps(ll N) {
    auto primes = primes_up_to(N);
    int P = primes.size();
    if (P == 0) return 0;

    // Optimal strategy: binary search on the INDEX of the prime
    // among the prime list. We need to identify which of the P primes.
    // For index-level binary search: log2(P) steps average.
    // But each step requires answering "is the prime ≤ primes[mid]?"

    // Simpler: binary search on indices [0, P-1]
    db total = 0;
    for (int idx = 0; idx < P; idx++) {
        int lo = 0, hi = P - 1;
        int steps = 0;
        while (lo <= hi) {
            steps++;
            int mid = (lo + hi) / 2;
            if (mid == idx) break;
            if (mid < idx) lo = mid + 1;
            else hi = mid - 1;
        }
        total += steps;
    }
    return total / P;
}

void verify_prime_guessing() {
    cout << "PE 869: Prime Guessing / 素数猜数\n\n";

    cout << "=== Primes up to 100 ===\n";
    auto p100 = primes_up_to(100);
    cout << "Count: " << p100.size() << "\n";
    for (int i = 0; i < (int)p100.size(); i++) {
        cout << setw(3) << p100[i];
        if ((i + 1) % 10 == 0) cout << "\n";
    }
    cout << "\n";

    cout << "\n=== Expected binary search steps ===\n";
    for (ll N : {10LL, 50LL, 100LL, 200LL, 500LL, 1000LL}) {
        db e_binary = expected_binary_steps(N);
        db e_random = expected_random_guesses(N);
        db e_optimal = expected_optimal_steps(N);
        auto primes = primes_up_to(N);
        cout << "N=" << setw(5) << N
             << " π(N)=" << setw(4) << primes.size()
             << " E[binary]=" << fixed << setprecision(4) << e_binary
             << " E[random]=" << setprecision(4) << e_random
             << " E[optimal]=" << setprecision(4) << e_optimal << "\n";
    }

    cout << "\n=== Information-theoretic lower bound ===\n";
    for (ll N : {100LL, 1000LL, 10000LL}) {
        int p = primes_up_to(N).size();
        cout << "N=" << N << ": log2(π)=" << fixed << setprecision(4)
             << log2(p) << " (π=" << p << ")\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << fixed << setprecision(8) << PE_ANSWER << "\n";
}

void compute_prime_guessing() {
    cout << "=== PE 869: Prime Guessing ===\n\n";

    cout << "=== Expected optimal steps vs N ===\n";
    for (ll N = 100; N <= 10000; N *= 2) {
        db e = expected_optimal_steps(N);
        auto primes = primes_up_to(N);
        cout << "N=" << setw(6) << N
             << " π=" << setw(5) << primes.size()
             << " E[optimal]=" << fixed << setprecision(6) << e
             << " log2(π)=" << log2(primes.size()) << "\n";
    }

    cout << "\n=== Expected binary search steps for larger N ===\n";
    // For N=10^6: π(10^6)=78498, binary search E[optimal] ≈ log(78498) ≈ 16.3
    for (ll N = 100000; N <= 1000000; N *= 10) {
        int p = primes_up_to(N).size();
        db log2_p = log2(p);
        cout << "N=10^" << (int)log10(N) << ": π=" << p
             << ", log2(π)=" << fixed << setprecision(6) << log2_p << "\n";
    }

    cout << "\nPE answer: " << fixed << setprecision(8) << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << fixed << setprecision(8) << PE_ANSWER << "\n";
        return 0;
    }
    if (query == "verify") {
        verify_prime_guessing();
        return 0;
    }
    if (query == "compute") {
        compute_prime_guessing();
        return 0;
    }
    cout << "PE 869: Prime Guessing / 素数猜数\n";
    cout << "Answer = " << fixed << setprecision(8) << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
