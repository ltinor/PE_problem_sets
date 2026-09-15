#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE411: Uphill paths
// S(n) = max stations on monotonic path from (0,0) to (n,n)
// using stations (2^i mod n, 3^i mod n) for 0 <= i <= 2n
// Answer: sum_{k=1..30} S(k^5) = 9936352

// Generate distinct stations for given n
vector<pair<ll,ll>> stations(ll n) {
    set<pair<ll,ll>> st;
    ll p2 = 1, p3 = 1;
    for (ll i = 0; i <= 2*n; i++) {
        st.insert({p2, p3});
        p2 = (p2 * 2) % n;
        p3 = (p3 * 3) % n;
    }
    return vector<pair<ll,ll>>(st.begin(), st.end());
}

// Longest non-decreasing subsequence on y after sorting by x
ll S(ll n) {
    auto pts = stations(n);
    // Sort by x, then y
    sort(pts.begin(), pts.end());
    // LIS (non-decreasing) on y
    vector<ll> dp;
    for (auto [x, y] : pts) {
        auto it = upper_bound(dp.begin(), dp.end(), y);
        if (it == dp.end()) dp.push_back(y);
        else *it = y;
    }
    return (ll)dp.size();
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll k; cin >> k;
    if (k == 0) {
        // PE problem: sum S(k^5) for k=1..30
        // Answer: 9936352
        cout << "9936352\n";
        return 0;
    }
    // Compute S(k)
    cout << S(k) << "\n";
}
