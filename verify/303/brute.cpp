#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// For small n, brute: try multiples 1*n, 2*n, ... and check digits
bool digits_ok(ll x) {
    while (x > 0) {
        if (x % 10 > 2) return false;
        x /= 10;
    }
    return true;
}

ll f_brute(ll n) {
    for (ll k = 1; ; k++) {
        ll m = k * n;
        if (digits_ok(m)) return k; // return f(n)/n
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll sum = 0;
    for (ll n = 1; n <= N; n++) {
        sum += f_brute(n);
    }

    cout << sum << "\n";
    return 0;
}
