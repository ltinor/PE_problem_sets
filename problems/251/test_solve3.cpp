#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll N = 2000;
    ll ans = 0;
    ll t0 = clock();
    
    for (ll g = 1; g <= N; g++) {
        for (ll z = 1; z <= N/g; z++) {
            // skip gcd checks - just count pairs
            if (z == 1) {
                // z=1 always works
                for (ll y = 1; ; y++) {
                    ll x = g * y;
                    ll a = 3*x - 1;
                    ll c = y*y * (8*g*y - 3);
                    if (a + g + c <= N) ans++;
                    else break;
                }
            } else {
                // z>1: do the full check (simplified)
                ll gz = (unsigned long long)gcd((unsigned long long)g, (unsigned long long)(z*z));
                if (gz < 1 || gz > 3) continue;
                
                ll z2 = z * z;
                ll d = (unsigned long long)gcd((unsigned long long)((8*g)%z2), (unsigned long long)z2);
                if (3 % d != 0) continue;
                
                // simplified: just try y=1
                ll y = 1;
                ll x = g;
                unsigned long long prod = (unsigned long long)y * y * (8*g*y - 3);
                if (prod % (unsigned long long)z2 == 0) {
                    ll c = (ll)(prod / z2);
                    if (3*x - 1 + g*z + c <= N) ans++;
                }
            }
        }
    }
    
    ll t1 = clock();
    printf("ans=%lld time=%.6f\n", ans, (double)(t1-t0)/CLOCKS_PER_SEC);
    return 0;
}
