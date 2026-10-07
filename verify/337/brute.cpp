#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 100000000;

// Brute: O(N^2) for small N
int phi(int n) {
    int res = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N;
    cin >> N;

    vector<int> phi_v(N + 1);
    for (int i = 1; i <= N; i++) phi_v[i] = phi(i);

    vector<ll> dp(N + 1, 0);
    dp[6] = 1;  // base case: sequence {6}
    for (int x = 7; x <= N; x++) {
        for (int y = 6; y < x; y++) {
            if (phi_v[y] < phi_v[x] && phi_v[x] < y) {
                dp[x] = (dp[x] + dp[y]) % MOD;
            }
        }
    }

    ll ans = 0;
    for (int x = 6; x <= N; x++)
        ans = (ans + dp[x]) % MOD;
    cout << ans << "\n";
    return 0;
}
