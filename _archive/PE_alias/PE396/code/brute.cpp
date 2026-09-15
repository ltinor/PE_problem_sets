#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// Brute: generate weak Goodstein sequence for small n

ll to_base_up(ll num, ll base) {
    ll result = 0, p = 1;
    while (num) {
        result += (num % base) * p;
        num /= base;
        p *= (base + 1);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    ll total = 0;
    for (ll n = 1; n < N; n++) {
        ll cnt = 0, g = n, k = 2;
        while (g > 0) {
            cnt++;
            g = to_base_up(g, k) - 1;
            k++;
        }
        total += cnt;
    }
    cout << total << "\n";
}
