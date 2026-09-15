#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 233: Lattice points on circle through (0,0),(N,0),(0,N),(N,N)
// Circle center: (N/2, N/2), radius: N/√2
// Condition: (2x-N)² + (2y-N)² = 2N²
// Let u = 2x-N, v = 2y-N: u²+v² = 2N²
// f(N) = r_2(2N²) = 4 * ∏_{p|N, p≡1(mod 4)} (2e_p+1)
// where e_p is exponent of p in N.
// PE answer: 271204031455541309 (sum of N≤10^11 with f(N)=420)
// This adaptation: given N, compute f(N).

// Factorize N, count primes ≡ 1 (mod 4)
ll compute_f(ll N) {
    ll ans = 4;
    ll tmp = N;

    // Factor 2
    while (tmp % 2 == 0) tmp /= 2;

    // Factor odd primes
    for (ll p = 3; p * p <= tmp; p += 2) {
        if (tmp % p == 0) {
            ll cnt = 0;
            while (tmp % p == 0) {
                tmp /= p;
                cnt++;
            }
            if (p % 4 == 1) {
                ans *= (2 * cnt + 1);
            }
        }
    }
    if (tmp > 1 && tmp % 4 == 1) {
        ans *= (2 * 1 + 1); // exponent = 1
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = compute_f(N);
    cout << ans << "\n";

    return 0;
}
