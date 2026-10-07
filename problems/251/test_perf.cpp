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

int main() {
    ll N = 2000;
    ll t0 = clock();
    ll pair_count = 0, y_count = 0, skip_gcd = 0;
    
    for (ll g = 1; g <= N; g++) {
        ll z_max = N / g;
        if (z_max == 0) continue;
        
        for (ll z = 1; z <= z_max; z++) {
            pair_count++;
            
            // Faster gcd check
            ll zz = z * z;
            ll gz;
            {
                unsigned long long a2 = (unsigned long long)g;
                unsigned long long b2 = (unsigned long long)zz;
                while (b2) { unsigned long long t2 = b2; b2 = a2 % b2; a2 = t2; }
                gz = (ll)a2;
            }
            if (gz < 1 || gz > 3) { skip_gcd++; continue; }
            
            y_count++;
            
            // Check congruence
            ll a_coef = (8 * g) % zz;
            // ... rest simplified
        }
    }
    
    ll t1 = clock();
    printf("Pairs: %lld, skip: %lld, y: %lld, time: %.3f\n", 
           pair_count, skip_gcd, y_count, (double)(t1-t0)/CLOCKS_PER_SEC);
    return 0;
}
