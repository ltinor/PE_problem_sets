#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Check condition 2: for k = 1..(n-1)/2, sum of smallest k+1 > sum of largest k
bool check_condition2(const vector<int>& a) {
    int n = a.size();
    vector<ll> pref(n + 1, 0), suff(n + 2, 0);
    for (int i = 1; i <= n; i++) pref[i] = pref[i-1] + a[i-1];
    for (int i = n; i >= 1; i--) suff[i] = suff[i+1] + a[i-1];
    for (int k = 1; k <= (n-1)/2; k++) {
        if (pref[k+1] <= suff[n-k+1]) return false;
    }
    return true;
}

// Check condition 1: all subset sums are unique
bool check_condition1(const vector<int>& a) {
    int n = a.size();
    int total = 1 << n;
    vector<int> sums(total);
    for (int mask = 1; mask < total; mask++) {
        int lsb = mask & -mask;
        int idx = __builtin_ctz(lsb);
        sums[mask] = sums[mask ^ lsb] + a[idx];
    }
    sort(sums.begin(), sums.end());
    for (int i = 1; i < total; i++)
        if (sums[i] == sums[i-1]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        int m;
        cin >> m;
        vector<int> a(m);
        for (int j = 0; j < m; j++) cin >> a[j];
        sort(a.begin(), a.end());

        if (check_condition2(a) && check_condition1(a)) {
            for (int x : a) ans += x;
        }
    }

    cout << ans << "\n";
    return 0;
}
