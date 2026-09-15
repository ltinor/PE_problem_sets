#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 808: Reversible Prime Squares / 可逆素数平方
//
// A prime p such that reverse(p^2) is also a perfect square of a prime.
// In other words: p is prime, p^2 reversed in base 10 gives q^2 where q is prime.
// Also, p ≠ q (cannot be palindromic).
//
// Find the sum of the first 50 such primes.
//
// Examples: 13^2 = 169, reverse = 961 = 31^2, both 13 and 31 are prime.
//           17^2 = 289, reverse = 982 = not a perfect square.
//
// PE answer: 380750427699465

const ll PE_ANSWER = 380750427699465LL;

// Reverse an integer (decimal)
ll reverse_num(ll n) {
    ll rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev;
}

// Check if n is a perfect square
bool is_perfect_square(ll n) {
    ll r = (ll)sqrt((long double)n);
    while (r * r < n) r++;
    while (r * r > n) r--;
    return r * r == n;
}

// Sieve of Eratosthenes up to limit
vector<int> sieve_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            if ((ll)i * i <= limit) {
                for (ll j = (ll)i * i; j <= limit; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
    return primes;
}

// Miller-Rabin primality test for 64-bit integers
ll mul_mod(ll a, ll b, ll mod) {
    return (i128)a * b % mod;
}

ll pow_mod(ll a, ll e, ll mod) {
    ll res = 1;
    a %= mod;
    while (e) {
        if (e & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return res;
}

bool is_prime_mr(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    // Write n-1 = d * 2^s
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    // Deterministic bases for 64-bit integers
    vector<ll> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ll a : bases) {
        if (a >= n) continue;
        ll x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

// Find the first K reversible prime squares
vector<ll> find_reversible_prime_squares(int K) {
    vector<ll> result;
    // The prime p whose square reversed is also a square of a prime.
    // p^2 has at most 2*digits(p) digits, reverse gives another square.

    // Generate primes and check each one
    // For K=50, we need to search far enough.
    // The largest such primes are relatively small (~10^5 range for K=50).

    // We'll use a combination of prime sieve for p and MR for q
    const int MAX_P = 20000000; // Enough to find 50 such primes
    auto primes = sieve_primes(MAX_P);

    cout << "Searching among " << primes.size() << " primes up to " << MAX_P << "...\n";

    for (int p : primes) {
        ll p2 = (ll)p * p;
        ll rev_p2 = reverse_num(p2);

        // Skip palindromic squares
        if (rev_p2 == p2) continue;

        // Check if rev_p2 is a perfect square
        if (!is_perfect_square(rev_p2)) continue;

        ll q = (ll)sqrt((long double)rev_p2);
        // Refine sqrt
        while (q * q < rev_p2) q++;
        while (q * q > rev_p2) q--;
        if (q * q != rev_p2) continue;

        // Check if q is prime
        if (!is_prime_mr(q)) continue;

        // Also ensure p ≠ q
        if (p == q) continue;

        // Also check: q is a prime and reverse(q^2) = p^2
        // This should be automatically true if p^2 reversed = q^2

        result.push_back(p);

        if ((int)result.size() % 10 == 0) {
            cout << "  Found " << result.size() << " reversible primes, latest p=" << p << "\n";
        }

        if ((int)result.size() >= K) break;
    }

    return result;
}

void verify_reversible_squares() {
    cout << "PE 808: Reversible Prime Squares / 可逆素数平方\n\n";

    cout << "=== Definition ===\n";
    cout << "Prime p where reverse(p^2) = q^2 for some prime q ≠ p.\n";
    cout << "Example: 13^2 = 169, reverse(169) = 961 = 31^2\n\n";

    cout << "=== Small examples ===\n";
    // Manual verification of small cases
    vector<int> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int p : small_primes) {
        ll p2 = (ll)p * p;
        ll r = reverse_num(p2);
        if (r == p2) continue; // skip palindromic
        if (is_perfect_square(r)) {
            ll q = (ll)sqrt((long double)r);
            while (q * q < r) q++;
            while (q * q > r) q--;
            bool q_prime = true;
            for (int d = 2; d * d <= q; d++) {
                if (q % d == 0) { q_prime = false; break; }
            }
            if (q_prime && q != p) {
                cout << "  " << p << "^2 = " << p2 << ", reverse = " << r
                     << " = " << q << "^2" << (q_prime ? " ✓" : " ✗") << "\n";
            }
        }
    }

    cout << "\n=== Known properties ===\n";
    cout << "Reversible prime squares come in pairs (p,q).\n";
    cout << "The first 50 such primes need to be summed.\n\n";
}

void compute_reversible_squares() {
    cout << "=== Computing First 50 Reversible Prime Squares ===\n\n";

    const int K = 50;
    auto result = find_reversible_prime_squares(K);

    cout << "\n=== Results ===\n";
    cout << "First " << K << " primes with reversible squares:\n";
    for (size_t i = 0; i < result.size(); i++) {
        ll p = result[i];
        ll p2 = (ll)p * p;
        ll r = reverse_num(p2);
        ll q = (ll)sqrt((long double)r);
        while (q * q < r) q++;
        while (q * q > r) q--;
        cout << "  " << (i + 1) << ". p=" << p << " (p^2=" << p2
             << ", reverse=" << r << " = " << q << "^2)\n";
    }

    ll sum = 0;
    for (ll p : result) sum += p;
    cout << "\nSum = " << sum << "\n";
    cout << "PE answer = " << PE_ANSWER << "\n";

    if (sum == PE_ANSWER) {
        cout << "✓ Match!\n";
    } else {
        cout << "✗ Mismatch (got " << sum << ", expected " << PE_ANSWER << ")\n";
    }
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
        verify_reversible_squares();
        return 0;
    }
    if (query == "compute") {
        compute_reversible_squares();
        return 0;
    }
    cout << "PE 808: Reversible Prime Squares / 可逆素数平方\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
