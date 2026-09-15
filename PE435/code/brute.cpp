#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE435 brute: direct computation of F_n(x) for small n

const ll MOD = 1307674368000LL;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    ll n, max_x;
    
    if (mode == "pe") {
        cout << "0\n";
        return 0;
    }
    
    cin >> n >> max_x;
    
    ll total = 0;
    for (ll x = 0; x <= max_x; x++) {
        ll f0 = 0, f1 = 1;
        ll ans = 0, xp = 1;
        for (ll i = 0; i <= n; i++) {
            ll fi;
            if (i == 0) fi = f0;
            else if (i == 1) fi = f1;
            else {
                ll t = f0;
                f0 = f1;
                f1 = (t + f1) % MOD;
                fi = f1;
            }
            ans = (ans + (__int128)fi * xp) % MOD;
            xp = (__int128)xp * x % MOD;
        }
        total = (total + ans) % MOD;
    }
    cout << total << "\n";
}
