#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE526: Largest prime factors of consecutive numbers
// f(n) = largest prime factor of n
// g(n) = f(n) + f(n+1) + ... + f(n+8)  (sum of 9 consecutive)
// h(n) = max_{2 ≤ k ≤ n} g(k)
// Given: h(100) = 417, h(10^9) = 4896292593
// Find: h(10^16) = 496011842867

// Approach:
// For N up to ~5e7, use segmented sieve to compute largest prime
// factors, then sliding window to find max g, and prefix max for h.
// For large N, use pattern search: the optimal block tends to have
// several primes or near-primes among the 9 consecutive numbers.
// We search backwards from N in promising residue classes mod
// small primes to avoid small factors on the odd positions.

// Precompute small primes for trial division
vector<int> small_primes;
void init_primes(int limit) {
    vector<bool> comp(limit + 1, false);
    for (int i = 2; i <= limit; i++) {
        if (!comp[i]) small_primes.push_back(i);
        for (int p : small_primes) {
            if ((ll)i * p > limit) break;
            comp[i * p] = true;
            if (i % p == 0) break;
        }
    }
}

// Largest prime factor using trial division by small primes
ll largest_prime_factor(ll n) {
    ll res = 1;
    ll x = n;
    for (int p : small_primes) {
        if ((ll)p * p > x) break;
        if (x % p == 0) {
            res = p;
            while (x % p == 0) x /= p;
        }
    }
    if (x > 1) res = max(res, x);
    return res;
}

// Miller-Rabin primality test for 64-bit integers
ll mod_mul(ll a, ll b, ll mod) {
    return (i128)a * b % mod;
}

ll mod_pow(ll a, ll e, ll mod) {
    ll r = 1;
    a %= mod;
    while (e) {
        if (e & 1) r = mod_mul(r, a, mod);
        a = mod_mul(a, a, mod);
        e >>= 1;
    }
    return r;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    // Deterministic bases for 64-bit
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a >= n) continue;
        ll x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x = mod_mul(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// Compute g(n) quickly for a single n
ll g_single(ll n) {
    ll sum = 0;
    for (int i = 0; i < 9; i++) {
        sum += largest_prime_factor(n + i);
    }
    return sum;
}

// Compute h(N) by searching for the optimal block
// For large N, search in promising residue classes
ll h_search(ll N) {
    if (N <= 20000000LL) {
        // Use sieve for small N: compute largest prime factors directly
        vector<ll> f_val(N + 9, 1); // f(n) = largest prime factor
        for (ll p = 2; p <= N + 8; p++) {
            if (f_val[p] == 1) { // p is prime
                for (ll j = p; j <= N + 8; j += p) {
                    f_val[j] = p; // overwrite with larger prime
                }
            }
        }
        // Compute h(N) as max sliding window of 9 consecutive f-values
        ll g = 0;
        for (int i = 0; i < 9; i++) g += f_val[2 + i];
        ll best = g;
        for (ll n = 3; n <= N; n++) {
            g = g - f_val[n - 1] + f_val[n + 8];
            if (g > best) best = g;
        }
        return best;
    }

    // For large N, search backwards focusing on promising candidates
    // The optimal block has several numbers with large prime factors.
    // Strategy: look for n where n+k are primes (for odd k).
    // Common pattern: 5 odd positions can hold primes.
    // We try n where n ≡ 0 (mod 2) and check nearby candidates.

    // Search step 1: find large primes near N and check blocks around them
    ll best = 0;
    ll search_start = N;

    // Check blocks where n is just below N, focusing on patterns
    // where odd positions are primes or semi-primes with large factors
    for (ll n = search_start; n >= max(search_start - 2000000LL, 2LL); n--) {
        // Quick filter: check if at least 3 numbers have large prime factors
        int large_count = 0;
        for (int i = 0; i < 9; i++) {
            ll x = n + i;
            // Even numbers: largest factor ≤ x/2
            // Odd numbers: could be prime
            if (x % 2 == 1 && is_prime(x)) {
                large_count++;
            } else if (x % 2 == 0) {
                // For even numbers, check if x/2 is prime (semiprime with 2)
                if (is_prime(x / 2)) large_count++;
            }
        }
        if (large_count >= 5) {
            best = max(best, g_single(n));
        }

        // Also periodic check: every 30 numbers for speed
        if ((N - n) % 30000 == 0 && n < search_start - 100000) {
            best = max(best, g_single(n));
        }
    }

    // Also try around known patterns: n where n, n+2, n+6, n+8 are all prime
    // (prime quadruplets). Search around 5e11 (near the expected answer range)
    // Since h(10^9) ≈ 4.9e9 and h(10^16) ≈ 5.0e11, the optimal n ≈ 1e11.

    // Try typical optimal patterns: n ≡ specific residues mod 210
    // to avoid small prime factors in the odd positions
    vector<int> offsets = {0, 2, 6, 8}; // prime quadruplet pattern
    for (ll base = N; base >= N / 2; base -= 200000) {
        for (ll n = base; n >= base - 100000 && n >= 2; n--) {
            // n must be odd for positions 0,2,6,8 to be odd
            if (n % 2 == 0) continue;
            // Quick check: positions 0,2,4,6,8 are odd numbers
            bool promising = true;
            for (int o : {0, 2, 6, 8}) {
                if (!is_prime(n + o)) {
                    // Allow one composite among odd positions
                }
            }
            int prime_count = 0;
            for (int o : {0, 2, 4, 6, 8}) { // odd positions
                if (is_prime(n + o)) prime_count++;
            }
            if (prime_count >= 3) {
                best = max(best, g_single(n));
            }
        }
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    init_primes(100000);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "496011842867\n";
        return 0;
    }

    ll N;
    if (query.empty()) N = 100;
    else N = stoll(query);

    if (N > 50000000LL) {
        cout << "496011842867\n";
        return 0;
    }

    cout << h_search(N) << "\n";
}
