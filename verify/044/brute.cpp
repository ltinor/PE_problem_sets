#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll P(ll n) {
    return n * (3LL * n - 1) / 2;
}

bool is_pentagonal(ll x) {
    // solve n(3n-1)/2 = x => 3n^2 - n - 2x = 0
    // n = (1 + sqrt(1 + 24x)) / 6
    ll disc = 1 + 24 * x;
    ll sq = (ll)sqrt(disc);
    if (sq * sq != disc) return false;
    return (1 + sq) % 6 == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    vector<ll> pent(M + 1);
    for (int i = 1; i <= M; i++) {
        pent[i] = P(i);
    }

    ll min_diff = LLONG_MAX;

    for (int j = 2; j <= M; j++) {
        for (int k = 1; k < j; k++) {
            ll sum = pent[j] + pent[k];
            ll diff = pent[j] - pent[k];
            if (is_pentagonal(sum) && is_pentagonal(diff)) {
                min_diff = min(min_diff, diff);
            }
        }
    }

    cout << min_diff << "\n";
}
