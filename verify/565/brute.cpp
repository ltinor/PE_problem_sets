#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE565: check σ(i) mod 2017 for small N

ll sigma(ll n) {
    ll s = 0;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            s += d;
            if (d * d != n) s += n / d;
        }
    }
    return s;
}

int main() {
    ll N;
    cin >> N;
    
    ll sum = 0;
    for (ll i = 1; i <= N; i++) {
        if (sigma(i) % 2017 == 0) sum += i;
    }
    cout << sum << "\n";
    return 0;
}
