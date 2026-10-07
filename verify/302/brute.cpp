#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool is_perfect_power(ll n) {
    if (n <= 1) return true;
    for (int k = 2; k <= 60; k++) {
        ll lo = 1, hi = (ll)pow(n, 1.0/k) + 2;
        while (lo <= hi) {
            ll mid = lo + (hi - lo) / 2;
            ll p = 1;
            bool overflow = false;
            for (int i = 0; i < k; i++) {
                if (p > n / mid) { overflow = true; break; }
                p *= mid;
            }
            if (!overflow && p == n) return true;
            if (overflow || p > n) hi = mid - 1;
            else lo = mid + 1;
        }
    }
    return false;
}

bool is_powerful(ll n) {
    if (n <= 1) return false;
    ll m = n;
    for (ll p = 2; p * p <= m; p++) {
        if (m % p == 0) {
            int cnt = 0;
            while (m % p == 0) { m /= p; cnt++; }
            if (cnt < 2) return false;
        }
    }
    if (m > 1) return false;
    return true;
}

ll phi(ll n) {
    ll result = n;
    ll m = n;
    for (ll p = 2; p * p <= m; p++) {
        if (m % p == 0) {
            while (m % p == 0) m /= p;
            result -= result / p;
        }
    }
    if (m > 1) result -= result / m;
    return result;
}

bool is_achilles(ll n) {
    if (n <= 1) return false;
    if (!is_powerful(n)) return false;
    if (is_perfect_power(n)) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll n = 2; n < N; n++) {
        if (!is_achilles(n)) continue;
        if (is_achilles(phi(n))) ans++;
    }

    cout << ans << "\n";
    return 0;
}
