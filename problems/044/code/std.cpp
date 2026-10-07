#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll P(ll n) {
    return n * (3LL * n - 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    // precompute pentagonal numbers
    vector<ll> pent(M + 1);
    unordered_set<ll> pent_set;
    for (int i = 1; i <= M; i++) {
        pent[i] = P(i);
        pent_set.insert(pent[i]);
    }

    ll min_diff = LLONG_MAX;

    for (int j = 2; j <= M; j++) {
        for (int k = 1; k < j; k++) {
            ll sum = pent[j] + pent[k];
            ll diff = pent[j] - pent[k];
            if (pent_set.count(sum) && pent_set.count(diff)) {
                min_diff = min(min_diff, diff);
            }
        }
    }

    cout << min_diff << "\n";
}
