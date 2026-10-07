#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 274: sum of divisibility multipliers for primes coprime to 10 less than limit
// For prime p: multiplier m = 10^{-1} mod p (0 < m < p)

ll mod_inv(ll a, ll m) {
    ll m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        ll q = a / m, t = m;
        m = a % m; a = t; t = y;
        y = x - q * y; x = t;
    }
    if (x < 0) x += m0;
    return x;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll L; cin >> L;
    vector<bool> p(L+1, true);
    p[0]=p[1]=false;
    ll s=0;
    for(ll i=2;i<=L;i++){
        if(p[i]){
            for(ll j=i*i;j<=L;j+=i) p[j]=false;
            if(i!=2&&i!=5) s+=mod_inv(10,i);
        }
    }
    cout<<s<<"\n";
}
