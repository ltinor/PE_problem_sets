#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll mygcd(ll a, ll b) {
    return b == 0 ? a : mygcd(b, a % b);
}

bool check_120(ll a, ll b, ll &side) {
    ll val = a * a + b * b + a * b;
    ll r = (ll)sqrt((long double)val);
    while ((r + 1) * (r + 1) <= val) r++;
    while (r * r > val) r--;
    if (r * r == val) {
        side = r;
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;

    unordered_set<ll> sums;

    for (ll p = 1; p <= M; p++) {
        for (ll q = p; q <= M - p; q++) {
            ll a;
            if (!check_120(p, q, a)) continue;

            ll max_r = M - p - q;
            if (max_r < q) break;

            for (ll r = q; r <= max_r; r++) {
                ll b, c;
                if (check_120(q, r, b) && check_120(r, p, c)) {
                    ll sum = p + q + r;
                    if (sums.find(sum) == sums.end()) {
                        sums.insert(sum);
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (ll s : sums) ans += s;
    cout << ans << "\n";

    return 0;
}
