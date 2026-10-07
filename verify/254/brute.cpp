#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int FACT[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

ll f_val(ll n) {
    if (n == 0) return 1;
    ll sum = 0;
    while (n > 0) {
        sum += FACT[n % 10];
        n /= 10;
    }
    return sum;
}

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

    // Brute force: search up to a smaller bound for verification
    // For small N, this should match std
    vector<ll> g(N + 1, -1);
    int found = 0;
    const ll MAX_SEARCH = 20000000LL;

    for (ll n = 1; n <= MAX_SEARCH && found < N; n++) {
        int sf = sf_val(n);
        if (sf >= 1 && sf <= N && g[sf] == -1) {
            g[sf] = n;
            found++;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        if (g[i] == -1) continue;
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
