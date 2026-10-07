#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Extended Euclidean for modular inverse
ll modinv(ll a, ll m) {
    ll m0 = m, y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        ll q = a / m;
        ll t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

ll solve(ll N) {
    ll ans = 0;
    
    for (ll g = 1; g <= N; g++) {
        ll z_max = N / g;
        
        for (ll z = 1; z <= z_max; z += 2) { // z must be odd (even z never works)
            // Check gcd(g, z²) | 3
            ll z2 = z * z;
            ll gz = (unsigned long long)gcd((unsigned long long)g, (unsigned long long)z2);
            if (gz != 1 && gz != 3) continue;
            
            ll d = gz; // gcd(8g, z²) = gcd(g, z²) for odd z
            // 3 % d == 0 always since d ∈ {1,3}
            
            ll a1 = ((8LL * g) % z2) / d;
            ll rhs = 3 / d;
            ll mod_val = z2 / d;
            
            ll y0;
            if (mod_val == 1) {
                y0 = 1;
            } else if (a1 == 1) {
                y0 = rhs % mod_val;
            } else {
                y0 = (rhs * modinv(a1 % mod_val, mod_val)) % mod_val;
            }
            if (y0 == 0) y0 = mod_val;
            
            // Ensure gcd(y0, z) = 1
            if ((unsigned long long)gcd((unsigned long long)y0, (unsigned long long)z) != 1) {
                bool found = false;
                for (ll k2 = 1; k2 < d; k2++) {
                    ll yt = y0 + k2 * mod_val;
                    if ((unsigned long long)gcd((unsigned long long)yt, (unsigned long long)z) == 1) {
                        y0 = yt; found = true; break;
                    }
                }
                if (!found) continue;
            }
            
            ll b = g * z;
            
            for (ll k = 0; ; k++) {
                ll y = y0 + k * mod_val;
                ll x = g * y;
                ll a = 3LL * x - 1;
                
                __int128 prod = (__int128)y * y * (8LL * g * y - 3);
                ll c = (ll)(prod / z2);
                
                if (a + b + c <= N) {
                    ans++;
                } else {
                    break;
                }
            }
        }
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N;
    cin >> N;
    cout << solve(N) << "\n";
    return 0;
}
