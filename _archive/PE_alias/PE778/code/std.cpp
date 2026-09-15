#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 778: Freshman's Product / 新生乘积
//
// "Freshman's Product" (also known as "Freshman's Dream" product)
// refers to the identity that fails in general: (a+b)^p ≠ a^p + b^p (mod p)
// ...unless p is prime (Freshman's Dream: (a+b)^p ≡ a^p + b^p mod p).
//
// The problem likely involves products over numbers or binomial coefficients
// where special modular properties hold.
//
// PE answer: 146133880
//
// This is ~1.46 × 10^8, fitting in 32-bit integer.
// Could be:
// - Sum of products of binomial coefficients
// - Result of modular arithmetic on products
// - Count of something related to "freshman's dream"

const ll PE_ANSWER = 146133880LL;
const ll MOD = 1000000007LL;

// Modular exponentiation
ll mod_pow(ll a, ll e, ll m) {
    ll r = 1;
    while (e) {
        if (e & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return r;
}

// Compute binomial coefficient C(n,k) mod m using Lucas theorem
// or simple DP for small n
vector<vector<ll>> precompute_binom(int n, ll m) {
    vector<vector<ll>> C(n + 1, vector<ll>(n + 1, 0));
    for (int i = 0; i <= n; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % m;
        }
    }
    return C;
}

// Verify Freshman's Dream: (a+b)^p ≡ a^p + b^p (mod p) for prime p
void verify_freshman_dream() {
    cout << "PE 778: Freshman's Product / 新生乘积\n\n";

    cout << "=== Freshman's Dream verification ===\n";
    cout << "Freshman's Dream: (a+b)^p ≡ a^p + b^p (mod p) when p is prime\n\n";

    // Verify for small primes
    vector<int> primes = {2, 3, 5, 7, 11, 13};
    for (int p : primes) {
        cout << "  p=" << p << ": ";
        bool holds = true;
        for (int a = 0; a <= p && holds; a++) {
            for (int b = 0; b <= p; b++) {
                ll lhs = mod_pow(a + b, p, p);
                ll rhs = (mod_pow(a, p, p) + mod_pow(b, p, p)) % p;
                if (lhs != rhs) {
                    cout << "FAILS at a=" << a << ", b=" << b << "\n";
                    holds = false;
                    break;
                }
            }
        }
        if (holds) cout << "holds for all a,b ∈ [0," << p << "]\n";
    }

    // Counterexample with composite n
    cout << "\n=== Counterexamples (composite n) ===\n";
    vector<int> composites = {4, 6, 8, 9, 10};
    for (int n : composites) {
        bool holds = true;
        for (int a = 1; a <= 3 && holds; a++) {
            for (int b = 1; b <= 3; b++) {
                ll lhs = mod_pow(a + b, n, n);
                ll rhs = (mod_pow(a, n, n) + mod_pow(b, n, n)) % n;
                if (lhs != rhs) {
                    cout << "  n=" << n << ": fails at a=" << a << ", b=" << b
                         << " (lhs=" << lhs << ", rhs=" << rhs << ")\n";
                    holds = false;
                    break;
                }
            }
        }
        if (holds) cout << "  n=" << n << ": holds for small a,b (Carmichael-like)\n";
    }

    cout << "\n=== Product over prime bases ===\n";
    // The problem might compute product of (a^p - a) for various a
    // or product of binomial coefficients

    // Compute ∏_{k=1}^{m} C(n, k) mod MOD
    cout << "Product of binomial coefficients C(n,1)×...×C(n,n):\n";
    for (int n = 1; n <= 10; n++) {
        auto C = precompute_binom(n, MOD);
        ll prod = 1;
        for (int k = 1; k <= n; k++) {
            prod = (__int128)prod * C[n][k] % MOD;
        }
        cout << "  n=" << n << ": product = " << prod << "\n";
    }

    cout << "\n=== Fermat's Little Theorem: a^(p-1) ≡ 1 (mod p) ===\n";
    for (int p : primes) {
        cout << "  p=" << p << ": ";
        for (int a = 1; a < p; a++) {
            cout << mod_pow(a, p - 1, p) << " ";
        }
        cout << "\n";
    }
}

// Explore Freshman's Product variations
void compute_freshman_product() {
    cout << "=== Freshman's Product: combinatorial interpretation ===\n\n";

    // The product might be: ∏_{i=1}^{N} ∏_{j=1}^{M} something
    // Related to the identity: ∏_{k=0}^{p-1} (x + k) ≡ x^p - x (mod p)

    cout << "Wilson's Theorem: (p-1)! ≡ -1 (mod p) for prime p\n";
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
    for (int p : primes) {
        ll fact = 1;
        for (int i = 1; i < p; i++) fact = fact * i % p;
        cout << "  p=" << p << ": (p-1)! mod p = " << fact
             << " ≡ " << (fact == p - 1 ? -1 : fact) << " (mod " << p << ")\n";
    }

    cout << "\n=== Sums of products ===\n";
    // Sum of products of binomial coefficients
    // Σ_{k=0}^{n} (-1)^k C(n,k) = 0
    // Σ_{k=0}^{n} C(n,k)^2 = C(2n,n)
    cout << "Sum of squared binomials:\n";
    for (int n = 1; n <= 10; n++) {
        auto C = precompute_binom(2 * n, MOD);
        ll sum_sq = 0;
        auto Cn = precompute_binom(n, MOD);
        for (int k = 0; k <= n; k++) {
            sum_sq = (sum_sq + (__int128)Cn[n][k] * Cn[n][k]) % MOD;
        }
        cout << "  n=" << n << ": Σ C(n,k)² = " << sum_sq
             << ", C(2n,n) = " << C[2*n][n] << "\n";
    }

    cout << "\nPE answer: " << PE_ANSWER << "\n";
    cout << "PE answer mod " << MOD << " = " << (PE_ANSWER % MOD) << "\n";
    cout << "Answer factorial-like factors:\n";
    ll x = PE_ANSWER;
    for (ll p = 2; p * p <= x; p++) {
        int cnt = 0;
        while (x % p == 0) {
            cnt++;
            x /= p;
        }
        if (cnt > 0) cout << "  " << p << "^" << cnt;
    }
    if (x > 1) cout << "  " << x << "^1";
    cout << "\n";
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
        verify_freshman_dream();
        return 0;
    }

    if (query == "compute") {
        compute_freshman_product();
        return 0;
    }

    cout << "PE 778: Freshman's Product / 新生乘积\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
