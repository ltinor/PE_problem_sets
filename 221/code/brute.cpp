#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: enumerate p,q,r for small values
// pq + pr + qr = 1 => find all triples with small |p|,|q|,|r|

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    const ll LIMIT = 100; // small brute force range
    set<ll> alex;

    for(ll p = -LIMIT; p <= LIMIT; p++) {
        if(p == 0) continue;
        for(ll q = -LIMIT; q <= LIMIT; q++) {
            if(q == 0) continue;
            // From pq + pr + qr = 1 => r(p+q) = 1 - pq
            // r = (1 - pq) / (p+q) if p+q != 0
            if(p + q == 0) continue;
            ll num = 1 - p*q;
            ll den = p + q;
            if(num % den != 0) continue;
            ll r = num / den;
            if(r == 0) continue;
            if(abs(r) > LIMIT) continue;
            ll A = p * q * r;
            if(A > 0) alex.insert(A);
        }
    }

    vector<ll> v(alex.begin(), alex.end());
    if(K <= (ll)v.size()) {
        cout << v[K-1] << "\n";
    }
    return 0;
}
