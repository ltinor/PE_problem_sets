#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll sigma(ll n) {
    ll s = 0;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            s += i;
            if (i * i != n) s += n / i;
        }
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll n = 1; n <= N; n++) {
        ll s = sigma(n);
        // Check if s/n is half-integer: 2*s % n == 0 and (2*s/n) is odd
        if ((2 * s) % n == 0) {
            ll q = (2 * s) / n;
            if (q % 2 == 1) {
                ans += n;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
