#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute: enumerate all numbers < 10^n, check conditions
// Only feasible for very small n (n <= 6)

int sum_digits(ll k) {
    int s = 0;
    while (k) { s += k % 10; k /= 10; }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    cin >> n;
    
    if (n > 7) {
        cout << "0\n"; // brute can't handle
        return 0;
    }
    
    ll limit = 1;
    for (ll i = 0; i < n; i++) limit *= 10;
    
    ll ans = 0;
    for (ll k = 0; k < limit; k++) {
        if (k % 23 == 0 && sum_digits(k) == 23) ans++;
    }
    
    cout << ans << "\n";
    return 0;
}
