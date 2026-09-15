// PE 632: Square prime factors
// C_k(N) = count of integers 1..N with exactly k square prime factors
// (p is a square prime factor of n if p^2 | n)
// Compute product of all non-zero C_k(10^16) modulo 1,000,000,007.
//
// Algorithm:
// - A number n has square prime factor p iff p^2 | n.
// - max number of distinct square prime factors for n <= 10^16:
//   First 8 primes product = 2*3*5*7*11*13*17*19 = 9,699,690; square = 9.4e13 <= 1e16
//   First 9 primes product = 223,092,870; square = 4.98e16 > 1e16
//   So max k = 8. (C_9 = 0)
// - Let T_j = sum_{p1<...<pj} floor(N / (p1*...*pj)^2)
// - Then C_k = sum_{j=k}^{8} (-1)^{j-k} * C(j,k) * T_j   (inclusion-exclusion)
// - Compute T_j by enumerating j-tuples of primes with product <= sqrt(N) = 10^8.
// - For j=1: sum over all primes p <= 10^8
// - For j=2: iterate pairs p<q with pq <= 10^8
// - For j>=3: recursive enumeration (few tuples)
//
// Answer: 728378714

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const ll MOD = 1000000007;
const ll N = 10000000000000000LL; // 10^16
const ll SQRT_N = 100000000LL;    // 10^8
const int MAX_K = 8;

// Segmented sieve to get primes up to SQRT_N
vector<int> get_primes(ll limit) {
    // Use a simple byte-sieve (bitset) for up to 10^8
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    vector<int> primes;
    primes.reserve(5761455); // pi(10^8)
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
    return primes;
}

// Binomial coefficients up to MAX_K
ll C[10][10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute binomial
    for (int i = 0; i <= MAX_K; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }

    // Generate primes up to SQRT_N
    auto primes = get_primes(SQRT_N);
    int P = primes.size();

    // T[j] = sum over j-tuples of floor(N / (prod^2))
    vector<ll> T(MAX_K + 1, 0);
    T[0] = N;

    // T[1] = sum over primes p: floor(N / p^2)
    for (int i = 0; i < P; i++) {
        ll p = primes[i];
        ll p2 = p * p;
        if (p2 > N) break;
        T[1] += N / p2;
    }

    // T[2] = sum over p<q, pq <= SQRT_N: floor(N / (p^2 * q^2))
    // Iterate p, then q > p with q <= SQRT_N / p
    for (int i = 0; i < P; i++) {
        ll p = primes[i];
        if (p * primes[i+1] > SQRT_N) break; // no more pairs needed? actually we still need to check
        ll max_q_val = SQRT_N / p;
        if (max_q_val < primes[i+1]) continue;
        // Binary search for the last q <= max_q_val
        // We iterate q directly since count is manageable
        ll p2 = p * p;
        for (int j = i + 1; j < P; j++) {
            ll q = primes[j];
            if (q > max_q_val) break;
            ll prod2 = p2 * q * q;
            if (prod2 > N) break;
            T[2] += N / prod2;
        }
    }

    // T[3]..T[8]: recursive enumeration of tuples
    // Only add when we reach the target depth
    function<void(int, int, ll, int)> dfs = [&](int idx, int depth, ll prod, int target) {
        if (depth == target) {
            ll prod2 = prod * prod;
            if (prod2 <= N) {
                T[target] += N / prod2;
            }
            return;
        }
        for (int i = idx; i < P; i++) {
            ll p = primes[i];
            if (p > SQRT_N / prod) break;
            ll new_prod = prod * p;
            ll new_prod2 = new_prod * new_prod;
            if (new_prod2 > N) break;
            dfs(i + 1, depth + 1, new_prod, target);
        }
    };

    for (int target = 3; target <= MAX_K; target++) {
        dfs(0, 0, 1, target);
    }

    // Now compute C_k from T_j via inclusion-exclusion
    vector<ll> Ck(MAX_K + 1, 0);
    for (int k = 0; k <= MAX_K; k++) {
        ll val = 0;
        for (int j = k; j <= MAX_K; j++) {
            ll term = C[j][k] * T[j];
            if ((j - k) % 2 == 1) val -= term;
            else val += term;
        }
        Ck[k] = val;
    }

    // Product of non-zero C_k mod MOD
    ll ans = 1;
    for (int k = 0; k <= MAX_K; k++) {
        if (Ck[k] > 0) {
            ans = (ans % MOD) * (Ck[k] % MOD) % MOD;
        }
    }

    cout << ans << "\n";
    return 0;
}
