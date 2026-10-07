#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
    ll t_gcd1 = 0, t_gcd2 = 0, t_inv = 0, t_loop = 0;
    clock_t c1, c2;
    
    for (ll g = 1; g <= N; g++) {
        ll z_max = N / g;
        if (z_max == 0) continue;
        
        for (ll z = 1; z <= z_max; z++) {
            c1 = clock();
            ll gz = (unsigned long long)gcd((unsigned long long)g, (unsigned long long)(z*z));
            t_gcd1 += clock() - c1;
            if (gz < 1 || gz > 3) continue;
            
            ll z2 = z * z;
            ll a_coef = (8 * g) % z2;
            
            c1 = clock();
            ll d = (unsigned long long)gcd((unsigned long long)a_coef, (unsigned long long)z2);
            t_gcd2 += clock() - c1;
            if (3 % d != 0) continue;
            
            ll a1 = a_coef / d;
            ll rhs = 3 / d;
            ll mod = z2 / d;
            
            c1 = clock();
            ll y0;
            if (a1 == 1) {
                y0 = rhs % mod;
            } else {
                y0 = (rhs * modinv(a1 % mod, mod)) % mod;
            }
            t_inv += clock() - c1;
            if (y0 == 0) y0 = mod;
            
            if ((unsigned long long)gcd((unsigned long long)y0, (unsigned long long)z) != 1) {
                bool found = false;
                for (ll k2 = 0; k2 < d; k2++) {
                    ll yt = y0 + k2 * mod;
                    if ((unsigned long long)gcd((unsigned long long)yt, (unsigned long long)z) == 1) {
                        y0 = yt; found = true; break;
                    }
                }
                if (!found) continue;
            }
            
            ll b = g * z;
            
            c1 = clock();
            for (ll k = 0; ; k++) {
                ll y = y0 + k * mod;
                ll x = g * y;
                ll a = 3*x - 1;
                
                unsigned long long prod = (unsigned long long)y * y * (8*g*y - 3);
                if (prod % (unsigned long long)z2 != 0) continue;
                ll c = (ll)(prod / z2);
                
                if (a + b + c <= N) {
                    ans++;
                } else {
                    break;
                }
            }
            t_loop += clock() - c1;
        }
    }
    
    fprintf(stderr, "gcd1:%.6f gcd2:%.6f inv:%.6f loop:%.6f\n",
            (double)t_gcd1/CLOCKS_PER_SEC, (double)t_gcd2/CLOCKS_PER_SEC,
            (double)t_inv/CLOCKS_PER_SEC, (double)t_loop/CLOCKS_PER_SEC);
    return ans;
}

int main() {
    ll N = 2000;
    cout << solve(N) << endl;
    return 0;
}
