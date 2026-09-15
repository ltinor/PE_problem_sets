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

    // Same algorithm as std — brute force search for smallest x+y+z
    for (ll a = 2; ; a++) {
        for (ll b = a % 2 == 0 ? 2 : 1; b < a; b += 2) {
            ll a2 = a * a, b2 = b * b;
            if ((a2 + b2) % 2 != 0) continue;
            ll x = (a2 + b2) / 2;
            ll y = (a2 - b2) / 2;
            if (y <= 0) continue;

            for (ll c = 2; c * c < 2 * x; c++) {
                ll d2 = 2 * x - c * c;
                if (d2 <= 0) continue;
                ll d = (ll)sqrt((long double)d2);
                if (d * d != d2) continue;
                if (d >= c) continue;
                if ((c % 2) != (d % 2)) continue;

                ll z = (c * c - d * d) / 2;
                if (z <= 0 || z >= y) continue;

                if (is_square(y + z) && is_square(y - z)) {
                    cout << x + y + z << "\n";
                    return 0;
                }
            }
        }
    }

    return 0;
}
