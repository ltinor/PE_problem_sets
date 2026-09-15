#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE386: ΣN(n) for 1 ≤ n ≤ N where N(n) = max antichain length of divisor set
// N(n) = max coefficient in Π_{p^e||n} (1 + x + ... + x^e)
// Use SPF sieve + generating function computation

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    // Smallest prime factor
    vector<ll> spf(N + 1);
    for (ll i = 2; i <= N; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            if (i * i <= N) {
                for (ll j = i * i; j <= N; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }
    }
    
    ll ans = 0;
    
    // N(1) = 1
    ans += 1;
    
    for (ll n = 2; n <= N; n++) {
        // Factor n using spf
        vector<int> exps;
        ll m = n;
        while (m > 1) {
            ll p = spf[m];
            int e = 0;
            while (m % p == 0) {
                m /= p;
                e++;
            }
            exps.push_back(e);
        }
        
        // Compute generating function coefficients
        // max total exponent sum = Σ e_i ≤ log_2(N) ≤ 27 for N ≤ 10^8
        int total = 0;
        for (int e : exps) total += e;
        
        vector<ll> poly(total + 1, 0);
        poly[0] = 1;
        int cur = 0;
        for (int e : exps) {
            // Multiply by (1 + x + ... + x^e)
            vector<ll> newpoly(cur + e + 1, 0);
            for (int i = 0; i <= cur; i++) {
                for (int j = 0; j <= e; j++) {
                    newpoly[i + j] += poly[i];
                }
            }
            poly = move(newpoly);
            cur += e;
        }
        
        // Find max coefficient
        ll maxc = 0;
        for (ll c : poly) maxc = max(maxc, c);
        
        ans += maxc;
    }
    
    cout << ans << "\n";
    return 0;
}
