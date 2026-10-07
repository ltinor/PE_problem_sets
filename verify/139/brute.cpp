#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll mygcd(ll a, ll b) {
    return b == 0 ? a : mygcd(b, a % b);
}

// Brute force: same algorithm as std

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;

    ll ans = 0;

    for (ll m = 2; m * m < M; m++) {
        for (ll n = 1; n < m; n++) {
            if ((m - n) % 2 == 0) continue;
            if (mygcd(m, n) != 1) continue;

            ll a = m * m - n * n;
            ll b = 2 * m * n;
            ll c = m * m + n * n;

            if (a > b) swap(a, b);

            ll perim = a + b + c;
            if (perim >= M) break;

            if (c % (b - a) == 0) {
                ans += (M - 1) / perim;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
