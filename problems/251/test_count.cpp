#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll N = 2000;
    ll inner = 0, inner_ans = 0;
    
    for (ll g = 1; g <= N; g++) {
        // only z=1 for testing
        ll z = 1, z2 = 1, mod = 1, y0 = 1;
        ll b = g * z;
        
        for (ll k = 0; ; k++) {
            ll y = y0 + k * mod;
            inner++;
            ll x = g * y;
            ll a = 3*x - 1;
            unsigned long long prod = (unsigned long long)y * y * (8*g*y - 3);
            ll c = (ll)(prod / z2);
            if (a + b + c <= N) {
                inner_ans++;
            } else {
                break;
            }
        }
    }
    
    printf("N=%lld: inner=%lld ans=%lld\n", N, inner, inner_ans);
    return 0;
}
