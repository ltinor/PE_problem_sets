#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Independent implementation using unordered_set for condition 1
bool check_condition2(const vector<int>& a) {
    int n = a.size();
    // Check: smallest k+1 sum > largest k sum for all k
    for (int k = 1; k <= (n-1)/2; k++) {
        ll small_sum = 0, large_sum = 0;
        for (int i = 0; i <= k; i++) small_sum += a[i];       // k+1 smallest
        for (int i = n-k; i < n; i++) large_sum += a[i];       // k largest
        if (small_sum <= large_sum) return false;
    }
    return true;
}

bool check_condition1(const vector<int>& a) {
    int n = a.size();
    unordered_set<int> sums;
    sums.insert(0);
    for (int x : a) {
        vector<int> new_sums;
        for (int s : sums) {
            int ns = s + x;
            if (sums.count(ns)) return false;
            new_sums.push_back(ns);
        }
        for (int s : new_sums) sums.insert(s);
    }
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
