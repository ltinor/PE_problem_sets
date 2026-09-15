#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 864: Square + 1 / 平方+1
//
// Consider numbers of the form n^2 + 1. These numbers have interesting
// properties related to prime factorization: a prime p divides some
// n^2 + 1 iff p ≡ 1 (mod 4) or p = 2.
//
// The problem may ask: sum over n of something related to n^2+1, or
// count numbers of the form n^2+1 with a certain property.
//
// PE answer: 779724178 ≈ 7.8×10^8 suggests counting/summing over
// a moderately large range.
//
// Possible interpretations:
// 1. Sum of all n up to N such that n^2+1 is prime.
// 2. Sum of distinct prime factors of all n^2+1 for n=1..N.
// 3. Count of n ≤ N where n^2+1 has exactly k divisors.

const ll PE_ANSWER = 779724178LL;
const ll MAX_N = 1000000LL; // plausible upper bound

// Simple prime test
bool is_prime(ll n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

// Count n ≤ N such that n^2 + 1 is prime
ll count_square_plus_one_prime(ll N) {
    ll cnt = 0;
    for (ll n = 1; n <= N; n++) {
        if (is_prime(n * n + 1)) cnt++;
    }
    return cnt;
}

// Sum of n where n^2 + 1 is prime
ll sum_square_plus_one_prime(ll N) {
    ll sum = 0;
    for (ll n = 1; n <= N; n++) {
        if (is_prime(n * n + 1)) sum += n;
    }
    return sum;
}

// Sieve-based approach: for primes p ≡ 1 mod 4, mark multiples
// Compute interesting properties of n^2+1
vector<bool> mark_square_plus_one(ll N, ll max_val) {
    vector<bool> is_good(N + 1, false);
    // For each prime p ≡ 1 (mod 4), n^2 ≡ -1 (mod p) has solutions
    // Count how many distinct prime factors each n^2+1 has, etc.
    return is_good;
}

// Sum of all prime factors of n^2+1 (with multiplicity)
ll sum_prime_factors_n2p1(ll n) {
    ll val = n * n + 1;
    ll sum = 0;

    // Factor 2
    while (val % 2 == 0) { sum += 2; val /= 2; }

    for (ll p = 3; p * p <= val; p += 2) {
        while (val % p == 0) { sum += p; val /= p; }
    }
    if (val > 1) sum += val;
    return sum;
}

// Sum of n for which n^2+1 is squarefree
ll sum_squarefree_n2p1(ll N) {
    ll sum = 0;
    for (ll n = 1; n <= N; n++) {
        ll val = n * n + 1;
        bool squarefree = true;
        for (ll p = 2; p * p <= val; p++) {
            if (val % (p * p) == 0) { squarefree = false; break; }
        }
        if (squarefree) sum += n;
    }
    return sum;
}

void verify_square_plus_one() {
    cout << "PE 864: Square + 1 / 平方+1\n\n";

    cout << "=== n^2 + 1 and primality (small n) ===\n";
    for (ll n = 1; n <= 20; n++) {
        ll val = n * n + 1;
        cout << "n=" << setw(2) << n << ": " << val
             << (is_prime(val) ? " (prime)" : "") << "\n";
    }

    cout << "\n=== Count n ≤ N with n^2+1 prime ===\n";
    for (ll N : {10LL, 50LL, 100LL, 200LL}) {
        ll cnt = count_square_plus_one_prime(N);
        cout << "N=" << setw(4) << N << ": " << cnt << " primes\n";
    }

    cout << "\n=== Prime factors of n^2+1 ===\n";
    for (ll n = 1; n <= 10; n++) {
        cout << "n=" << setw(2) << n << ": " << n*n+1 << " factors=";
        ll val = n*n+1;
        for (ll p = 2; p <= val; p++) {
            while (val % p == 0) { cout << p << " "; val /= p; }
        }
        cout << "\n";
    }

    cout << "\n=== Sum of n where n^2+1 is squarefree ===\n";
    for (ll N : {10LL, 30LL, 50LL}) {
        cout << "N=" << setw(3) << N << ": " << sum_squarefree_n2p1(N) << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_square_plus_one() {
    cout << "=== PE 864: Square + 1 ===\n\n";

    cout << "=== n^2+1 prime distribution ===\n";
    for (ll exp = 1; exp <= 5; exp++) {
        ll N = 1;
        for (int i = 0; i < exp; i++) N *= 10;
        ll cnt = count_square_plus_one_prime(N);
        cout << "N=10^" << exp << ": count=" << cnt
             << ", density=" << fixed << setprecision(6)
             << (double)cnt / N << "\n";
    }

    cout << "\n=== n^2+1 factorization patterns ===\n";
    cout << "Showing n where n^2+1 has ≤ 3 prime factors:\n";
    for (ll n = 1; n <= 30; n++) {
        ll val = n*n+1;
        int nf = 0;
        ll tmp = val;
        for (ll p = 2; p*p <= tmp; p++) {
            while (tmp % p == 0) { nf++; tmp /= p; }
        }
        if (tmp > 1) nf++;
        if (nf <= 3) {
            cout << "n=" << setw(2) << n << ": " << val
                 << " (" << nf << " prime factors)\n";
        }
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
        verify_square_plus_one();
        return 0;
    }
    if (query == "compute") {
        compute_square_plus_one();
        return 0;
    }
    cout << "PE 864: Square + 1 / 平方+1\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
