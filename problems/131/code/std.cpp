#include<bits/stdc++.h>
using namespace std;

#define ll long long

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;

    // p = 3*k*k + 3*k + 1 must be prime and < M
    int ans = 0;
    for (ll k = 1; ; k++) {
        ll p = 3 * k * k + 3 * k + 1;
        if (p >= M) break;
        if (is_prime(p)) ans++;
    }

    cout << ans << "\n";
    return 0;
}
