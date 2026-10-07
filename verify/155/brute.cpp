#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll mygcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// Brute force: same DP as std but simpler
// For small N, verify results
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    if (N > 8) {
        cout << "0\n";
        return 0;
    }
    
    // Use pair<ll,ll> in set for simplicity
    auto normalize = [](ll n, ll d) -> pair<ll,ll> {
        ll g = mygcd(abs(n), d);
        return {n/g, d/g};
    };
    
    auto frac_less = [](const pair<ll,ll>& a, const pair<ll,ll>& b) {
        return (__int128_t)a.first * b.second < (__int128_t)b.first * a.second;
    };
    
    vector<set<pair<ll,ll>, decltype(frac_less)>> exact(N+1, 
        set<pair<ll,ll>, decltype(frac_less)>(frac_less));
    exact[1].insert({1, 1});
    
    for (int n = 2; n <= N; n++) {
        for (int k = 1; k <= n/2; k++) {
            int nk = n - k;
            for (auto [an, ad] : exact[k]) {
                for (auto [bn, bd] : exact[nk]) {
                    // Parallel
                    ll num = an * bd + bn * ad;
                    ll den = ad * bd;
                    exact[n].insert(normalize(num, den));
                    
                    // Series
                    num = an * bn;
                    den = ad * bn + bd * an;
                    if (den != 0) {
                        exact[n].insert(normalize(num, den));
                    }
                }
            }
        }
    }
    
    set<pair<ll,ll>, decltype(frac_less)> all(frac_less);
    for (int n = 1; n <= N; n++) {
        for (auto f : exact[n]) all.insert(f);
    }
    
    cout << all.size() << "\n";
    return 0;
}
