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

    ll M;
    cin >> M;

    unordered_set<ll> seen;
    ll ans = 0;

    // Type A: n = k * b * (k * a^3 + b)
    // where a > b, gcd(a,b) = 1, r = k*b^2, d = k*a*b, q = k*a^2
    // Condition: r < d (always true since b < a)
    // n must be a perfect square

    for (ll a = 2; ; a++) {
        ll a3 = a * a * a;
        if (a3 >= M) break;
        for (ll b = 1; b < a; b++) {
            if (mygcd(a, b) != 1) continue;

            ll max_k = (ll)sqrt((long double)M / (a3 * b)) + 2;
            for (ll k = 1; k <= max_k; k++) {
                ll n = k * b * (k * a3 + b);
                if (n >= M) break;
                if (is_square(n) && seen.find(n) == seen.end()) {
                    seen.insert(n);
                    ans += n;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
