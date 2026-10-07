#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rects(ll m, ll n) {
    return m * (m + 1) * n * (n + 1) / 4;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    cin >> T;

    ll best_diff = LLONG_MAX;
    ll best_area = 0;

    // Brute force: enumerate m, n up to reasonable bound
    ll limit = (ll)sqrt(2.0 * T) + 10;

    for (ll m = 1; m <= limit; m++) {
        for (ll n = 1; n <= limit; n++) {
            ll r = rects(m, n);
            ll diff = llabs(r - T);
            if (diff < best_diff || (diff == best_diff && m * n < best_area)) {
                best_diff = diff;
                best_area = m * n;
            }
        }
    }

    cout << best_area << "\n";
    return 0;
}
