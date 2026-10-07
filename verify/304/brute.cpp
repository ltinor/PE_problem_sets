#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

ll next_prime(ll n) {
    n++;
    while (!is_prime(n)) n++;
    return n;
}

ll fib(ll n, ll mod) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    ll a = 0, b = 1;
    for (ll i = 2; i <= n; i++) {
        ll c = (a + b) % mod;
        a = b; b = c;
    }
    return b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, MOD, START;
    cin >> N >> MOD >> START;

    ll sum = 0;
    ll p = next_prime(START);

    for (ll i = 1; i <= N; i++) {
        sum = (sum + fib(p, MOD)) % MOD;
        p = next_prime(p);
    }

    cout << sum << "\n";
    return 0;
}
