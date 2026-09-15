#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll N = 1000;
    int total = 0, z1 = 0, z3 = 0, z_other = 0;
    for (ll a = 1; a <= N - 2; a++) {
        if (a % 3 != 2) continue;
        ll x = (a + 1) / 3;
        for (ll b = 1; a + b <= N - 1; b++) {
            ll M = x*x * (8*x - 3);
            if (M % (b*b) != 0) continue;
            ll c = M / (b*b);
            if (c >= 1 && a + b + c <= N) {
                total++;
                ll g = gcd((unsigned long long)x, (unsigned long long)b);
                ll z = b / g;
                if (z == 1) z1++;
                else if (z == 3) z3++;
                else { z_other++; printf("z=%lld: a=%lld b=%lld c=%lld g=%lld y=%lld\n", z, a, b, c, g, x/g); }
            }
        }
    }
    printf("N=%lld: total=%d z1=%d z3=%d z_other=%d\n", N, total, z1, z3, z_other);
    return 0;
}
