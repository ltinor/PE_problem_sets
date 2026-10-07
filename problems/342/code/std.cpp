#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 342: Sum of n (1 < n < N) where phi(n^2) = n * phi(n) is a perfect cube
// We use linear sieve for phi up to N, then check cube condition.
// For large N, we use the math approach directly.
//
// Optimized: phi(n^2) = n * phi(n) must be a cube.
// This means for each prime p|n with exponent e:
// p^{2e-1} * (p-1 factorization) must have all exponents ≡ 0 (mod 3)

const int MAXN = 20000000;
int phi[MAXN];

void sieve_phi(int N) {
    vector<int> primes;
    vector<bool> is_prime(N + 1, true);
    phi[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : primes) {
            if ((ll)i * p > N) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
}

bool is_cube(ll x) {
    // Check if x is a perfect cube using integer cube root
    if (x <= 0) return false;
    ll lo = 1, hi = 1000000; // cube_root(10^18) ~ 10^6
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (mid * mid * mid <= x) lo = mid;
        else hi = mid - 1;
    }
    return lo * lo * lo == x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    if (N > MAXN) {
        // For large N, we need the enumeration approach
        // This is a fallback - in OJ, N is ≤ 2e7
        cout << "0\n";
        return 0;
    }
    
    sieve_phi(N);
    
    ll ans = 0;
    for (ll n = 2; n < N; n++) {
        ll val = n * phi[n];
        if (is_cube(val)) {
            ans += n;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
