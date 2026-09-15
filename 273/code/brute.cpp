#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE 273
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int plim; cin >> plim;
    vector<int> pr;
    vector<bool> isp(plim+1, true);
    for (int i = 2; i <= plim; i++) {
        if (isp[i]) {
            for (int j = i*2; j <= plim; j += i) isp[j] = false;
            if (i % 4 == 1) pr.push_back(i);
        }
    }
    int k = pr.size();
    ll total = 0;
    for (int mask = 1; mask < (1<<k); mask++) {
        ll N = 1;
        for (int i = 0; i < k; i++)
            if (mask & (1<<i)) N *= pr[i];
        ll sum_a = 0;
        for (ll a = 0; a*a <= N; a++) {
            ll b2 = N - a*a;
            ll b = sqrt(b2);
            if (b*b == b2 && a <= b) sum_a += a;
        }
        total += sum_a;
    }
    cout << total << "\n";
    return 0;
}
