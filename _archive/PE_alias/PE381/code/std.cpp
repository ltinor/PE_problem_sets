#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE381: sum of S(p) for primes 5 <= p < n
// S(p) = ((p-1)! + (p-2)! + (p-3)! + (p-4)! + (p-5)!) mod p
// By Wilson: (p-1)! ≡ -1, (p-2)! ≡ 1
// (p-k)! ≡ (-1)^k * inv((k-1)!)  mod p
// S(p) = -inv(2) + inv(6) - inv(24) mod p
// where inv(2)=(p+1)/2, inv(6)=inv(2)*inv(3), inv(24)=inv(2)^2*inv(6)

ll modinv(ll a, ll p) {
    // a small, p prime, p > a
    // Use: (kp+1)/a for small a
    for (ll k = 1; k < a; k++) {
        if ((k * p + 1) % a == 0) return (k * p + 1) / a;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    cin >> n;
    
    // Sieve primes up to n
    vector<bool> isp(n + 1, true);
    isp[0] = isp[1] = false;
    for (ll i = 2; i * i <= n; i++) {
        if (isp[i]) {
            for (ll j = i * i; j <= n; j += i) isp[j] = false;
        }
    }
    
    ll ans = 0;
    for (ll p = 5; p < n; p++) {
        if (!isp[p]) continue;
        
        // inv(2) mod p
        ll inv2 = (p + 1) / 2;
        // inv(3) mod p
        ll inv3 = modinv(3, p);
        // inv(6) = inv(2) * inv(3) mod p
        ll inv6 = (inv2 * inv3) % p;
        // inv(4) = inv(2) * inv(2) mod p
        ll inv4 = (inv2 * inv2) % p;
        // inv(24) = inv(4) * inv(6) mod p
        ll inv24 = (inv4 * inv6) % p;
        
        // S(p) = -inv2 + inv6 - inv24 mod p
        ll sp = (p - inv2 + inv6 + p - inv24) % p;
        ans += sp;
    }
    
    cout << ans << "\n";
    return 0;
}
