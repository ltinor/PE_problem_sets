#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll N = 1000;
    for (ll a = 1; a <= N - 2; a++) {
        // a must be ≡ 2 mod 3
        if (a % 3 != 2) continue;
        ll x = (a + 1) / 3;
        for (ll b = 1; a + b <= N - 1; b++) {
            // b²c = x²(8x-3)
            ll M = x*x * (8*x - 3);
            if (M % (b*b) != 0) continue;
            ll c = M / (b*b);
            if (c >= 1 && a + b + c <= N) {
                printf("a=%lld b=%lld c=%lld (%lld)\n", a, b, c, a+b+c);
            }
        }
    }
    return 0;
}
