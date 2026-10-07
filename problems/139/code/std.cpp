#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll mygcd(ll a, ll b) {
    return b == 0 ? a : mygcd(b, a % b);
}

// PE 139: Count primitive Pythagorean triples where c % (b-a) == 0
// Then count all multiples where perimeter < M

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;

    ll ans = 0;

    // Generate primitive Pythagorean triples: a=m^2-n^2, b=2mn, c=m^2+n^2
    // m > n, coprime, one odd one even
    for (ll m = 2; m * m < M; m++) {
        for (ll n = 1; n < m; n++) {
            if ((m - n) % 2 == 0) continue;  // both odd or both even -> not primitive
            if (mygcd(m, n) != 1) continue;

            ll a = m * m - n * n;
            ll b = 2 * m * n;
            ll c = m * m + n * n;

            // Ensure a < b
            if (a > b) swap(a, b);

            ll perim = a + b + c;
            if (perim >= M) break;

            // Check condition: c % (b - a) == 0
            if (c % (b - a) == 0) {
                ans += (M - 1) / perim;  // all multiples with perimeter < M
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
