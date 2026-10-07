#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Print all solutions from parametrization
void param_solutions(ll N) {
    // Case z=1
    for (ll b = 1; ; b++) {
        if (12*b - 4 > N) break;
        for (ll y = 1; ; y++) {
            ll x = b * y;
            ll a = 3*x - 1;
            ll c = y*y * (8*b*y - 3);
            if (a + b + c > N) break;
            printf("z1: a=%lld b=%lld c=%lld\n", a, b, c);
        }
    }
    
    // Case z=3
    for (ll g = 1; ; g++) {
        ll b = 3*g;
        ll y0 = -1;
        int step = 9;
        if (g % 3 == 0) {
            ll gp = g / 3;
            for (ll y = 1; y <= 3; y++) {
                if ((gp * y) % 3 == 2) { y0 = y; step = 3; break; }
            }
        } else if (g % 9 == 0) {
            continue;
        } else {
            for (ll y = 1; y <= 9; y++) {
                if ((g * y) % 9 == 6) { y0 = y; break; }
            }
        }
        if (y0 == -1) continue;
        
        bool any = false;
        for (ll yi = 0; ; yi++) {
            ll y = y0 + yi * step;
            ll x = g * y;
            ll a = 3*x - 1;
            ll prod = y*y * (8*g*y - 3);
            if (prod % 9 != 0) continue;
            ll c = prod / 9;
            if (a + b + c <= N) {
                printf("z3: a=%lld b=%lld c=%lld\n", a, b, c);
                any = true;
            } else break;
        }
        if (!any && b > N/10) break;
    }
}

int main() {
    param_solutions(1000);
    return 0;
}
