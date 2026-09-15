#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll phi(ll n) {
    ll res = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll A, B;
    cin >> A >> B;
    
    // Search up to some limit
    ll limit = 2000000;
    for (ll d = 2; d <= limit; d++) {
        // R(d) = φ(d)/(d-1) < A/B
        if (phi(d) * B < A * (d - 1)) {
            cout << d << "\n";
            return 0;
        }
    }
    
    cout << "0\n";
    return 0;
}
