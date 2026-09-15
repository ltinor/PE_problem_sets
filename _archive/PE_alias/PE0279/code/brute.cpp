#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool has_int_angle(ll a, ll b, ll c) {
    // Check 60°, 90°, 120° via law of cosines in integer form
    // Sort sides so c is largest
    vector<ll> s = {a, b, c};
    sort(s.begin(), s.end());
    ll x = s[0], y = s[1], z = s[2];

    // 90°: x² + y² == z²
    if (x * x + y * y == z * z) return true;

    // 60°: the cosine formula: z² = x² + y² - x*y  (angle opposite any side)
    // Check all three positions
    if (a * a + b * b - a * b == c * c) return true;
    if (a * a + c * c - a * c == b * b) return true;
    if (b * b + c * c - b * c == a * a) return true;

    // 120°: z² = x² + y² + x*y
    if (a * a + b * b + a * b == c * c) return true;
    if (a * a + c * c + a * c == b * b) return true;
    if (b * b + c * c + b * c == a * a) return true;

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = a; a + b <= N; b++) {
            for (ll c = b; a + b + c <= N; c++) {
                if (a + b > c && has_int_angle(a, b, c))
                    ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
