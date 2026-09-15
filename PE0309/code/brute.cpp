#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: directly enumerate x, y and check integer w, h
// Only for small N for verification
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll x = 1; x < N; x++) {
        for (ll y = x + 1; y < N; y++) {
            for (ll w = 1; w < x; w++) {
                // Check if w < x and w < y
                if (w >= y) continue;

                ll a2 = x*x - w*w;
                ll a = (ll)sqrt(a2);
                if (a * a != a2) continue;

                ll b2 = y*y - w*w;
                ll b = (ll)sqrt(b2);
                if (b * b != b2) continue;

                // Check h = a*b/(a+b) integer
                if ((a * b) % (a + b) == 0) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
