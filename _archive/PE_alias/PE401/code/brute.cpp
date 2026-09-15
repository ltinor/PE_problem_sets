#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// PE401 brute: compute SIGMA2(N) by iterating all numbers and divisors
// O(N log N) — works for N ≤ 10^6

ll sigma2(ll n) {
    ll s = 0;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            s += d * d;
            if (d * d != n) s += (n / d) * (n / d);
        }
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N, M; cin >> N >> M;
    ll ans = 0;
    for (ll i = 1; i <= N; i++) {
        ans = (ans + sigma2(i)) % M;
    }
    cout << ans << "\n";
}
