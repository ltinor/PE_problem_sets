#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Möbius function via linear sieve
vector<int> mobius(int n) {
    vector<int> mu(n + 1, 0);
    vector<int> primes;
    vector<bool> is_composite(n + 1, false);
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (i * p > n) break;
            is_composite[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}

// Number of integer triangles (a<=b<=c) with perimeter exactly p
ll count_perimeter(ll p) {
    if (p % 2 == 0)
        return (p * p + 24) / 48;
    else {
        ll x = p + 3;
        return (x * x + 24) / 48;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    auto mu = mobius(N);

    // prefix[n] = number of integer triangles with perimeter <= n
    vector<ll> prefix(N + 1, 0);
    for (ll p = 3; p <= N; p++)
        prefix[p] = prefix[p - 1] + count_perimeter(p);

    ll ans = 0;
    for (ll d = 1; d <= N; d++) {
        if (mu[d] == 0) continue;
        ans += mu[d] * prefix[N / d];
    }

    cout << ans << "\n";
    return 0;
}
