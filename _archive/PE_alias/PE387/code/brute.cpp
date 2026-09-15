#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool isprime(ll n) {
    if (n<2) return 0;
    for (ll i=2; i*i<=n; i++) if (n%i==0) return 0;
    return 1;
}

ll digsum(ll n) { ll s=0; while(n){s+=n%10;n/=10;} return s; }

int main() {
    ll lim; cin >> lim;
    ll ans = 0;
    // BFS: generate right truncatable Harshad numbers
    queue<ll> q;
    for (ll d=1; d<=9; d++) q.push(d);
    while (!q.empty()) {
        ll x = q.front(); q.pop();
        ll s = digsum(x);
        if (x % s != 0) continue; // not Harshad
        // check strong Harshad
        if (isprime(x/s)) {
            // append digit to try forming prime
            for (ll d=0; d<=9; d++) {
                ll y = x*10 + d;
                if (y >= lim) break;
                if (isprime(y)) ans += y;
            }
        }
        // extend
        for (ll d=0; d<=9; d++) {
            ll y = x*10 + d;
            if (y < lim && y%s==0) q.push(y);
        }
    }
    cout << ans << "\n";
}
