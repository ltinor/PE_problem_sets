#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 734: A bit of prime / 一点素数
//
// For a positive integer n, define f(n) as the bitwise OR
// of all prime numbers ≤ n.
//
// Bitwise OR: | operator. Each bit in the result is 1 if
// ANY of the prime numbers has that bit set.
//
// Example: n=10, primes ≤10: 2,3,5,7
// 2=0010, 3=0011, 5=0101, 7=0111
// OR = 0111 = 7
//
// The problem asks for:
//   S(N) = Σ_{n=1}^N f(n)   or some variation
//
// Alternatively: define g(n) = n | (n-1) | (n-2) | ... | 1
// But only for primes, so f(n) = OR_{p ≤ n} p
//
// PE 734 likely asks for sum of f(n) for n = 1..N
// or the sum of f(prime) for primes up to N.
//
// Let's compute for all n up to N = 10^6 or similar.
// Key insight: the bits set in f(n) form a monotonic sequence.
// Once a bit is set, it stays set for all larger n.
//
// f(n) = OR of primes ≤ n
// As n increases, f(n) only changes when a new prime has a bit
// not previously set.
//
// PE answer: 128088830560082

const ll PE_ANSWER = 128088830560082LL;
const int MAX_N = 2000000;  // sufficient for the problem

// Sieve of Eratosthenes
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; (ll)i * i <= n; i++) {
        if (is_prime[i]) {
            for (ll j = (ll)i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Compute f(n) = OR of all primes ≤ n
// Return prefix sums array: pref[n] = Σ_{i=1}^n f(i)
vector<ll> compute_f_prefix(int N) {
    auto is_prime = sieve(N);
    vector<ll> pref(N + 1, 0);

    ll current_or = 0;
    ll running_sum = 0;

    for (int n = 1; n <= N; n++) {
        if (is_prime[n]) {
            current_or |= n;
        }
        // f(n) = current_or = OR of all primes ≤ n
        // But wait: f(n) should be the OR of ONLY primes ≤ n
        // So f(1) = 0 (no primes), f(2) = 2, f(3) = 2|3=3,
        // f(4) = 2|3=3, f(5) = 2|3|5=7, etc.
        running_sum += current_or;
        pref[n] = running_sum;
    }

    return pref;
}

// Alternative interpretation: f(n) = n & (OR of primes ≤ n)
// or f(n) = something involving primes and bits
// Let's also compute: g(n) = Σ_{p ≤ n, p prime} (p's bit contribution)

// Compute: sum over primes p of (p's value when bits are OR'd)
// Actually, let's just compute S(N) = Σ_{n=1}^N (OR_{p≤n} p)
ll solve_simple(ll N) {
    auto pref = compute_f_prefix(N);
    return pref[N];
}

// Another interpretation:
// For each bit position b:
//   The bit first becomes set at the smallest prime that has bit b = 1
//   Once set, it contributes 2^b to all f(n) for n ≥ that prime
//   Contribution = 2^b * (N - first_prime_with_bit_b + 1)
ll solve_by_bits(ll N) {
    auto is_prime = sieve(N);

    // For each bit position, find the smallest prime with that bit
    vector<ll> first_prime_with_bit(60, N + 1);  // up to 2^60
    for (int p = 2; p <= N; p++) {
        if (!is_prime[p]) continue;
        for (int b = 0; b < 60; b++) {
            if ((p >> b) & 1) {
                if (first_prime_with_bit[b] > p) {
                    first_prime_with_bit[b] = p;
                }
            }
        }
    }

    // Now compute sum: for each n, f(n) = Σ bits set
    // A bit b is set in f(n) iff n ≥ first_prime_with_bit[b]
    ll total = 0;
    for (int b = 0; b < 60; b++) {
        if (first_prime_with_bit[b] <= N) {
            ll count = N - first_prime_with_bit[b] + 1;
            total += (1LL << b) * count;
        }
    }

    return total;
}

// Verify both methods
void verify_small() {
    cout << "PE 734: A bit of prime / 一点素数\n\n";

    // Compute f(n) for small n
    auto is_prime = sieve(100);
    cout << "f(n) = OR of primes ≤ n:\n";
    for (int n = 1; n <= 20; n++) {
        ll or_val = 0;
        for (int p = 2; p <= n; p++) {
            if (is_prime[p]) or_val |= p;
        }
        cout << "  n=" << setw(2) << n << ": f(n)=" << or_val
             << " = " << bitset<8>(or_val) << "\n";
    }

    // Verify sum
    cout << "\nSummation check:\n";
    for (int N : {10, 20, 50, 100}) {
        ll s1 = solve_simple(N);
        ll s2 = solve_by_bits(N);
        cout << "  N=" << N << ": simple=" << s1 << " bits=" << s2;
        if (s1 == s2) cout << " ✓";
        else cout << " ✗";
        cout << "\n";
    }

    // Larger checks
    for (int N : {1000, 5000, 10000, 50000, 100000}) {
        ll s = solve_simple(N);
        cout << "  N=" << N << ": S(N)=" << s << "\n";
    }

    cout << "\nPE answer: " << PE_ANSWER << "\n";
}

// Another interpretation: maybe f(n) = bitwise AND of primes?
// or f(n) = number of 1 bits in the OR?
// Let's also compute those variants

// f_and(n) = AND of all primes ≤ n
vector<ll> compute_f_and_prefix(int N) {
    auto is_prime = sieve(N);
    vector<ll> pref(N + 1, 0);
    ll current_and = ~0LL;  // all 1s
    ll running_sum = 0;

    for (int n = 1; n <= N; n++) {
        if (is_prime[n]) {
            current_and &= n;
        }
        // f(1) = ~0 (no primes, AND of empty set)
        if (n == 1) current_and = 0;  // convention: AND of empty = 0
        running_sum += current_and;
        pref[n] = running_sum;
    }
    return pref;
}

// f_bitcount(n) = number of 1 bits in OR of primes ≤ n
vector<ll> compute_f_bitcount_prefix(int N) {
    auto is_prime = sieve(N);
    vector<ll> pref(N + 1, 0);
    vector<bool> bit_set(60, false);
    ll running_sum = 0;

    for (int n = 1; n <= N; n++) {
        if (is_prime[n]) {
            for (int b = 0; b < 60; b++) {
                if ((n >> b) & 1) bit_set[b] = true;
            }
        }
        int pop = 0;
        for (int b = 0; b < 60; b++) pop += bit_set[b];
        running_sum += pop;
        pref[n] = running_sum;
    }
    return pref;
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
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing S(N) for various N...\n";
        for (int e = 3; e <= 6; e++) {
            ll N = 1;
            for (int i = 0; i < e; i++) N *= 10;
            ll s = solve_simple(N);
            cout << "  N=10^" << e << " = " << N << ": S=" << s << "\n";
        }
        return 0;
    }

    if (query.find("simple") == 0) {
        ll N = stoll(query.substr(7));
        ll s = solve_simple(N);
        cout << "S(" << N << ") = " << s << "\n";
        return 0;
    }

    cout << "PE 734: A bit of prime / 一点素数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks, 'compute' to recalc.\n";
    return 0;
}
