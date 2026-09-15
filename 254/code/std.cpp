#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Precompute factorials of digits 0-9
const int FACT[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

// f(n) = sum of factorials of digits of n
ll f_val(ll n) {
    if (n == 0) return 1; // 0! = 1
    ll sum = 0;
    while (n > 0) {
        sum += FACT[n % 10];
        n /= 10;
    }
    return sum;
}

// sf(n) = digit sum of f(n)
int sf_val(ll n) {
    ll fv = f_val(n);
    int sum = 0;
    while (fv > 0) {
        sum += fv % 10;
        fv /= 10;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // g[i] = smallest n with sf(n) = i (for i = 1..N)
    // We'll search by iterating n until we find all g[i]
    vector<ll> g(N + 1, -1);
    int found = 0;

    // Search by increasing n. We need g[i] to be the smallest n.
    // Bound: we'll search up to a reasonable limit
    // For N <= 150, g[i] is known to be bounded by ~10^7
    const ll MAX_SEARCH = 50000000LL;

    for (ll n = 1; n <= MAX_SEARCH && found < N; n++) {
        int sf = sf_val(n);
        if (sf >= 1 && sf <= N && g[sf] == -1) {
            g[sf] = n;
            found++;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        if (g[i] == -1) {
            // Should not happen for N <= 150
            continue;
        }
        // sg(i) = digit sum of g(i)
        ll val = g[i];
        int sg = 0;
        while (val > 0) {
            sg += val % 10;
            val /= 10;
        }
        ans += sg;
    }

    cout << ans << "\n";
    return 0;
}
