#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE454 brute: count solutions by iterating x, y directly
ll F_brute(ll L) {
    ll cnt = 0;
    for (ll x = 1; x <= L; x++) {
        for (ll y = x + 1; y <= L; y++) {
            // 1/x + 1/y = 1/n → n = xy/(x+y)
            // Check if xy % (x+y) == 0
            ll sum = x + y;
            ll prod = (__int128)x * y;
            if (prod % sum == 0) {
                ll n = prod / sum;
                if (n > 0 && n < x) cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll L; cin >> L;
    if (L <= 200) {
        cout << F_brute(L) << "\n";
    } else {
        cout << "-1\n";
    }
}
