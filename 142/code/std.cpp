#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll mygcd(ll a, ll b) {
    return b == 0 ? a : mygcd(b, a % b);
}

bool is_square(ll n) {
    ll r = (ll)sqrt((long double)n);
    while ((r + 1) * (r + 1) <= n) r++;
    while (r * r > n) r--;
    return r * r == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // We need x > y > z > 0 such that:
    // x+y = a^2, x-y = b^2  => x = (a^2+b^2)/2, y = (a^2-b^2)/2
    // x+z = c^2, x-z = d^2  => x = (c^2+d^2)/2, z = (c^2-d^2)/2
    // y+z = e^2, y-z = f^2  => y = (e^2+f^2)/2, z = (e^2-f^2)/2
    //
    // All a,b,c,d,e,f positive integers, a>b, c>d, e>f.
    // a and b same parity, c and d same parity, e and f same parity.
    //
    // Strategy: enumerate a>b, compute x,y. Then for each x, find c>d yielding same x.
    // Then check y>z and y+z,y-z are squares.

    // We need to find the MINIMUM x+y+z.

    // Known answer: x=434657, y=420968, z=150568, x+y+z=1006193

    for (ll a = 2; ; a++) {
        for (ll b = a % 2 == 0 ? 2 : 1; b < a; b += 2) {
            ll a2 = a * a, b2 = b * b;
            if ((a2 + b2) % 2 != 0) continue;
            ll x = (a2 + b2) / 2;
            ll y = (a2 - b2) / 2;
            if (y <= 0) continue;

            // Now find c>d such that (c^2+d^2)/2 = x
            // c^2 + d^2 = 2x, c>d, same parity
            for (ll c = 2; c * c < 2 * x; c++) {
                ll d2 = 2 * x - c * c;
                if (d2 <= 0) continue;
                ll d = (ll)sqrt((long double)d2);
                if (d * d != d2) continue;
                if (d >= c) continue;
                // same parity
                if ((c % 2) != (d % 2)) continue;

                ll z = (c * c - d * d) / 2;
                if (z <= 0 || z >= y) continue;

                // verify y+z and y-z are squares
                if (is_square(y + z) && is_square(y - z)) {
                    cout << x + y + z << "\n";
                    return 0;
                }
            }
        }
    }

    return 0;
}
