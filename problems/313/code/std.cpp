#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll P;
    cin >> P;

    // sieve primes < P
    vector<bool> is_prime(P, true);
    if (P > 0) is_prime[0] = false;
    if (P > 1) is_prime[1] = false;
    for (ll i = 2; i * i < P; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j < P; j += i)
                is_prime[j] = false;
        }
    }

    ll ans = 0;
    for (ll p = 2; p < P; p++) {
        if (!is_prime[p]) continue;
        if (p == 2) continue; // p=2: 4+11=15 not divisible by 4

        if (p == 3) {
            // m=2 case: S(2,3)=9=3^2
            ans += 1;
        }

        // m,n >= 3: S = 4(m+n)-11 = p^2
        // m+n = (p^2 + 11) / 4
        ll S = (p * p + 11) / 4; // integer for all odd p
        // count pairs (m,n) with 3 <= m <= n
        // m ranges from 3 to floor(S/2)
        ll max_m = S / 2;
        if (max_m >= 3) {
            ans += max_m - 2; // = floor(S/2) - 2
        }
    }

    cout << ans << "\n";
    return 0;
}
