// PE 634: Numbers of the form a^2*b^3
// Count distinct integers x <= 9*10^18 that can be written as a^2*b^3 with a,b >= 2.
//
// Algorithm:
// 1. For each squarefree b >= 2 with b^3 <= N: count a >= 2 such that a^2*b^3 <= N.
//    This gives all numbers whose unique representation a^2*b^3 has b >= 2.
//    Uniqueness: every powerful number has a UNIQUE representation a^2*b^3 with b squarefree.
// 2. Add perfect squares a^2 where a is not cube-free AND a != p^3 for prime p.
//    These cannot be represented with b>=2 in the unique rep but have alt rep a,b>=2.
//
// Answer: 4019680944
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

// Integer square root (floor sqrt) for 64-bit
ll isqrt(ll n) {
    if (n <= 1) return n;
    ll x = (ll)sqrt((long double)n);
    while ((x+1)*(x+1) <= n) x++;
    while (x*x > n) x--;
    return x;
}

// Integer cube root (floor) for 64-bit
ll icbrt(ll n) {
    if (n <= 1) return n;
    ll x = (ll)cbrt((long double)n);
    while ((x+1)*(x+1)*(x+1) <= n) x++;
    while (x*x*x > n) x--;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N = 9000000000000000000LL; // 9 * 10^18
    ll N_cbrt = icbrt(N);

    // Generate squarefree numbers up to N_cbrt
    vector<bool> is_sqfree(N_cbrt + 1, true);
    is_sqfree[0] = false;
    for (ll i = 2; i * i <= N_cbrt; i++) {
        ll i2 = i * i;
        for (ll j = i2; j <= N_cbrt; j += i2)
            is_sqfree[j] = false;
    }

    // Step 1: count numbers with unique rep b>=2 (squarefree), a>=2
    ll ans = 0;
    for (ll b = 2; b <= N_cbrt; b++) {
        if (!is_sqfree[b]) continue;
        ll b3 = b * b * b;
        if (b3 > N) break;
        ll max_a = isqrt(N / b3);
        if (max_a >= 2)
            ans += max_a - 1;
    }

    // Step 2: add representable squares
    ll M = isqrt(N);
    ll M_cbrt = icbrt(M);

    // Count numbers a in [1, M] that are NOT cube-free using Möbius
    // cube-free count = sum_{k=1}^{M_cbrt} mu(k) * floor(M / k^3)
    vector<int> mu(M_cbrt + 1, 1);
    vector<bool> is_prime(M_cbrt + 1, true);
    vector<int> primes;
    mu[0] = 0;
    for (int i = 2; i <= M_cbrt; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if ((ll)i * p > M_cbrt) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }

    ll cubefree = 0;
    for (int k = 1; k <= M_cbrt; k++) {
        if (mu[k] == 0) continue;
        ll k3 = (ll)k * k * k;
        cubefree += mu[k] * (M / k3);
    }
    ll not_cubefree = M - cubefree; // count of a in [1,M] not cube-free

    // Count primes p with p^3 <= M
    ll prime_cubes = 0;
    for (int i = 2; i <= M_cbrt; i++) {
        if (is_prime[i]) prime_cubes++;
    }

    ans += (not_cubefree - prime_cubes);

    cout << ans << "\n";
    return 0;
}
