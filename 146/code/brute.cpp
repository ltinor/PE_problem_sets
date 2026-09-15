#include<bits/stdc++.h>
using namespace std;

#define ll long long

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

bool check(ll n) {
    ll n2 = n * n;
    if (!is_prime(n2 + 1)) return false;
    if (!is_prime(n2 + 3)) return false;
    if (!is_prime(n2 + 7)) return false;
    if (!is_prime(n2 + 9)) return false;
    if (!is_prime(n2 + 13)) return false;
    if (!is_prime(n2 + 27)) return false;
    if (is_prime(n2 + 5)) return false;
    if (is_prime(n2 + 11)) return false;
    if (is_prime(n2 + 15)) return false;
    if (is_prime(n2 + 17)) return false;
    if (is_prime(n2 + 19)) return false;
    if (is_prime(n2 + 21)) return false;
    if (is_prime(n2 + 23)) return false;
    if (is_prime(n2 + 25)) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;

    ll ans = 0;
    for (ll n = 10; n < M; n += 10) {
        if (check(n)) ans += n;
    }

    cout << ans << "\n";
    return 0;
}
