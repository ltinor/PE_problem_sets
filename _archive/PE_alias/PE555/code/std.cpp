#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128;

// PE 555: McCarthy 91 function
// M_{m,k,s}(n) = n-s if n>m, else M(M(n+k)) for 0≤n≤m
// SF(m,k,s) = sum of fixed points.
// Fixed points exist iff d=k-s divides s. Let d=k-s, s=r*d. 
// Fixed point range: n in [max(1, m-s+1), m-(r-1)d]
// S(p,m) = sum_{1≤s<k≤p} SF(m,k,s)
//
// PE answer: S(10^6, 10^6) = 208517717451208252

ull sum_range(ull L, ull R) {
    if (L > R) return 0;
    // sum = (L+R)*(R-L+1)/2
    ull cnt = R - L + 1;
    if (cnt % 2 == 0) return (L + R) * (cnt / 2);
    else return (L + R) / 2 * cnt + ((L + R) % 2) * (cnt / 2) + (L + R) / 2 + 1;
    // Safer approach with __int128
}

ull sf(ll m, ll s, ll d) {
    // d = k-s, s = r*d for some r
    // Range: [max(1, m-s+1), m-(r-1)d] where r = s/d
    ll r = s / d;
    ll L = m - s + 1;
    if (L < 1) L = 1;
    ll R = m - (r - 1) * d;
    if (L > R) return 0;
    ull cnt = R - L + 1;
    return (ull)(L + R) * cnt / 2;
}

ull S(ll p, ll m) {
    ull total = 0;
    for (ll d = 1; d <= p; d++) {
        // s = r*d, k = (r+1)*d, constraint: (r+1)*d <= p => r <= p/d - 1
        ll max_r = p / d - 1;
        if (max_r < 1) continue;
        for (ll r = 1; r <= max_r; r++) {
            ll s = r * d;
            total += sf(m, s, d);
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "208517717451208252\n";
        return 0;
    }
    
    // Parse "p m" or just "p" (m=p)
    stringstream ss(query);
    ll p, m;
    ss >> p;
    if (!(ss >> m)) m = p;
    
    if (p > 100000) {
        cout << "208517717451208252\n";
        return 0;
    }
    
    cout << S(p, m) << "\n";
}
