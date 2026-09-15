#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE421 brute: sum of distinct prime factors of n^15+1 <= m

ll s_small(ll n, ll m) {
    // n^15+1 factors
    ll f1 = n + 1;
    ll f2 = n*n*n*n - n*n*n + n*n - n + 1;
    ll f3 = 1;
    for (int i = 0; i < 10; i++) {
        ll t = 1;
        for (int j = 0; j < 5; j++) t *= n;
        f3 = 1;
        for (int j = 0; j < 10; j++) f3 *= n;
        f3 = f3;
    }
    // n^10 - n^5 + 1
    ll n5 = 1; for (int i = 0; i < 5; i++) n5 *= n;
    ll n10 = n5 * n5;
    f3 = n10 - n5 + 1;

    set<ll> primes;
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
    ll sum = 0;
    for (ll p : primes) sum += p;
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N, M;
    cin >> N >> M;
    ll ans = 0;
    for (ll n = 1; n <= N && n <= 100; n++) ans += s_small(n, M);
    cout << ans << "\n";
}
