#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rev_num(ll n) {
    ll r = 0;
    while (n) {
        r = r * 10 + n % 10;
        n /= 10;
    }
    return r;
}

bool all_odd(ll n) {
    while (n) {
        if ((n % 10) % 2 == 0) return false;
        n /= 10;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    ll limit = 1;
    for (int i = 0; i < D; i++) limit *= 10;

    ll ans = 0;
    for (ll n = 1; n < limit; n++) {
        if (n % 10 == 0) continue; // rev would have leading zero
        ll r = rev_num(n);
        ll sum = n + r;
        if (all_odd(sum)) ans++;
    }

    cout << ans << "\n";
    return 0;
}
