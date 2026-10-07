#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_prime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll n = 1; ; n++) {
        ll p = 2 * n * n + 2 * n + 1;
        if (p >= N) break;
        if (is_prime(p)) ans++;
    }

    cout << ans << "\n";
    return 0;
}
