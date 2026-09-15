#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: enumerate all (x,y) in [0,N]×[0,N]
// Check if (2x-N)² + (2y-N)² == 2N²
// Works for N ≤ 5000

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll target = 2 * N * N;
    ll ans = 0;

    for (ll x = 0; x <= N; x++) {
        for (ll y = 0; y <= N; y++) {
            ll u = 2 * x - N;
            ll v = 2 * y - N;
            if (u * u + v * v == target) {
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
