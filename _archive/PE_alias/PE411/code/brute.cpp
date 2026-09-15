#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE411 brute: S(n) using O(m^2) DP LIS for verification

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

ll S(ll n) {
    auto pts = stations(n);
    sort(pts.begin(), pts.end());
    ll m = pts.size();
    vector<ll> dp(m, 1);
    for (ll i = 0; i < m; i++) {
        for (ll j = 0; j < i; j++) {
            if (pts[j].second <= pts[i].second) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    return m == 0 ? 0 : *max_element(dp.begin(), dp.end());
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll k; cin >> k;
    cout << S(k) << "\n";
}
