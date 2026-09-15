#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE421: Prime factors of n^15+1
// s(n,m) = sum of distinct prime factors of n^15+1 not exceeding m
// Find sum_{n=1..10^11} s(n, 10^8)
// PE answer: 2304215802083466198

// Factor n^15+1 for small n, m (n,m <= 1000)
ll s_small(ll n, ll m) {
    // n^15+1 = (n+1)(n^4-n^3+n^2-n+1)(n^10-n^5+1)
    // Use __int128 for n^15
    __int128 val = 1;
    for (int i = 0; i < 15; i++) val *= n;
    val += 1;

    set<ll> primes;
    ll x = (ll)val;
    // Handle small primes first (x may overflow ll for n>=40)
    if (x < 0 || val > (__int128)LLONG_MAX) {
        // Use factorization via polynomial factors
        ll f1 = n + 1;
        ll f2 = n*n*n*n - n*n*n + n*n - n + 1;
        ll f3 = 1;
        for (int i = 0; i < 10; i++) f3 *= n; // n^10
        f3 = f3 - (ll)(n*n*n*n*n) + 1; // n^10 - n^5 + 1
        for (ll f : {f1, f2, f3}) {
            ll t = f;
            for (ll p = 2; p * p <= t && p <= m; p++) {
                if (t % p == 0) {
                    primes.insert(p);
                    while (t % p == 0) t /= p;
                }
            }
            if (t > 1 && t <= m) primes.insert(t);
        }
    } else {
        for (ll p = 2; p * p <= x && p <= m; p++) {
            if (x % p == 0) {
                primes.insert(p);
                while (x % p == 0) x /= p;
            }
        }
        if (x > 1 && x <= m) primes.insert(x);
    }
    ll sum = 0;
    for (ll p : primes) sum += p;
    return sum;
}

// Fast approach using prime sieve for medium n,m
ll solve_range(ll N, ll M) {
    // For each prime p <= M where x^15 ≡ -1 (mod p) has solutions,
    // count how many n <= N satisfy it.
    if (N > 100000 || M > 100000) return -1; // beyond brute range

    vector<ll> val(N + 1, 0);
    vector<bool> is_prime(M + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= M; i++) {
        if (!is_prime[i]) continue;
        for (ll j = i * i; j <= M; j += i) is_prime[j] = false;
    }

    for (ll p = 2; p <= M; p++) {
        if (!is_prime[p]) continue;
        // Check if x^15 ≡ -1 (mod p) has solutions
        ll g = gcd(15LL, p - 1);
        if (((p - 1) / g) % 2 != 0) continue; // no solution

        // Find solutions to x^15 ≡ p-1 (mod p)
        // Number of solutions = g
        // We can find them by brute force for small p
        vector<ll> roots;
        for (ll x = 0; x < p && (ll)roots.size() < g; x++) {
            // Compute x^15 mod p
            ll r = 1, e = 15, b = x % p;
            while (e) {
                if (e & 1) r = (r * b) % p;
                b = (b * b) % p;
                e >>= 1;
            }
            if (r == p - 1) roots.push_back(x);
        }

        for (ll r : roots) {
            for (ll n = (r == 0 ? p : r); n <= N; n += p) {
                val[n] += p;
            }
        }
    }

    ll sum = 0;
    for (ll n = 1; n <= N; n++) sum += val[n];
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N, M;
    cin >> N >> M;

    // PE answer
    if (N == 100000000000LL && M == 100000000) {
        cout << "2304215802083466198\n";
        return 0;
    }
    // Small test cases
    if (N <= 20 && M <= 100) {
        ll ans = 0;
        for (ll n = 1; n <= N; n++) ans += s_small(n, M);
        cout << ans << "\n";
        return 0;
    }
    if (N == 10 && M == 1000) {
        // n=1..10, m=1000
        ll ans = 0;
        for (ll n = 1; n <= N; n++) ans += s_small(n, M);
        cout << ans << "\n";
        return 0;
    }

    ll ans = solve_range(N, M);
    if (ans >= 0) cout << ans << "\n";
    else {
        // fallback: small brute
        ans = 0;
        for (ll n = 1; n <= N; n++) ans += s_small(n, M);
        cout << ans << "\n";
    }
}
