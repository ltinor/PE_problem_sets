#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 100000000;

// Fenwick tree for range sum queries
struct BIT {
    int n;
    vector<ll> tree;
    BIT(int n_) : n(n_), tree(n_ + 2, 0) {}
    void add(int idx, ll val) {
        for (++idx; idx <= n; idx += idx & -idx)
            tree[idx] = (tree[idx] + val) % MOD;
    }
    ll sum(int idx) { // sum in [0, idx)
        ll s = 0;
        for (; idx > 0; idx -= idx & -idx)
            s = (s + tree[idx]) % MOD;
        return s;
    }
    ll range(int l, int r) { // sum in [l, r)
        if (l >= r) return 0;
        return (sum(r) - sum(l) + MOD) % MOD;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Sieve phi
    vector<int> phi(N + 1);
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= N; i++) {
        if (phi[i] == i) { // prime
            for (int j = i; j <= N; j += i)
                phi[j] -= phi[j] / i;
        }
    }

    // Group numbers by phi value
    vector<vector<int>> groups(N + 1);
    for (int x = 1; x <= N; x++) {
        groups[phi[x]].push_back(x);
    }

    BIT bit(N);
    vector<ll> dp(N + 1, 0);

    // Process phi values in increasing order
    for (int v = 1; v <= N; v++) {
        if (groups[v].empty()) continue;

        // For each x with phi(x) = v
        for (int x : groups[v]) {
            // Need sum of dp[y] for y where:
            // y > v (phi(x)), y < x, phi(y) < v, and y >= 6 (a1=6)
            // Since we process in phi order, all y with phi < v are already in BIT
            // Query range (v, x)
            ll sum_prev = 0;
            if (v < x) {
                ll lo = max((ll)v + 1, 6LL);
                if (lo < x) {
                    sum_prev = bit.range(lo, x);
                }
            }
            // Base case: a1=6, so {6} is a valid sequence of length 1
            // For x=6, dp[6]=1. For x>6, dp[x] = sum_prev (no standalone {x})
            dp[x] = (x == 6 ? 1 : 0) + sum_prev;
            dp[x] %= MOD;
        }

        // After processing all x with phi = v, add them to BIT
        for (int x : groups[v]) {
            bit.add(x, dp[x]);
        }
    }

    // S(N) = sum of dp[x] for all x <= N
    ll ans = 0;
    for (int x = 6; x <= N; x++) {
        ans = (ans + dp[x]) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
