#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE463 brute: compute f and S directly for small n

ll S_brute(ll N) {
    vector<ll> f(N + 1, 0);
    f[1] = 1;
    if (N >= 3) f[3] = 3;
    
    for (ll i = 2; i <= N; i++) {
        if (f[i] != 0) continue;
        if (i % 2 == 0) {
            f[i] = f[i / 2];
        } else if (i % 4 == 1) {
            ll n = (i - 1) / 4;
            f[i] = 2 * f[2*n + 1] - f[n];
        } else {
            ll n = (i - 3) / 4;
            f[i] = 3 * f[2*n + 1] - 2 * f[n];
        }
    }
    
    ll sum = 0;
    for (ll i = 1; i <= N; i++) sum += f[i];
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;
    if (n <= 10000000) {
        cout << S_brute(n) << "\n";
    } else {
        cout << "-1\n";
    }
}
