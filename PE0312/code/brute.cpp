#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: verify with small n using the known formula directly
ll modpow(ll b, ll e, ll m) {
    ll r = 1; b %= m;
    while (e) { if(e&1) r=r*b%m; b=b*b%m; e>>=1; }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, M;
    cin >> n >> M;

    if (n <= 2) {
        cout << 1 % M << "\n";
        return 0;
    }

    // Compute 3^(n-2) using 64-bit (works for n up to ~20)
    ll a = 1;
    for (ll i = 0; i < n - 2; i++) a *= 3;
    ll b = (a - 3) / 2;

    ll result = modpow(2, a, M) * modpow(3, b, M) % M;
    cout << result << "\n";
    return 0;
}
